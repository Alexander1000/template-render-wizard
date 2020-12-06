#include <io-buffer.h>
#include <memory.h>
#include <iostream>
#include <list>
#include <trw.h>

#define TRW_RENDER_MEMORY_BLOCK_SIZE 4096
#define TRW_RENDER_BUFFER_SIZE 1024

namespace TemplateRenderWizard
{
    Render::Render(std::string* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(srcTemplateFile->c_str());
        IOBuffer::CharStream* charStream;
        charStream = new IOBuffer::CharStream(fileReader);
        this->stream = new TemplateRenderWizard::Stream(charStream);
        this->tree = tree;
    }

    Render::Render(const char* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(srcTemplateFile);
        IOBuffer::CharStream* charStream;
        charStream = new IOBuffer::CharStream(fileReader);
        this->stream = new TemplateRenderWizard::Stream(charStream);
        this->tree = tree;
    }

    Render::Render(TemplateRenderWizard::Stream* stream, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->stream = stream;
        this->tree = tree;
    }

    IOBuffer::IOMemoryBuffer* Render::toBuffer()
    {
        IOBuffer::IOMemoryBuffer* buffer;
        buffer = new IOBuffer::IOMemoryBuffer(TRW_RENDER_MEMORY_BLOCK_SIZE);
        char* tBuffer = (char*) malloc(sizeof(char) * TRW_RENDER_BUFFER_SIZE);

        TemplateRenderWizard::Token::Token* token;
        token = this->stream->getNextToken();

        while (token != nullptr) {
            switch (token->getType()) {
                case TemplateRenderWizard::Token::Type::PlainTextType: {
                    IOBuffer::IOReader* reader = token->getReader();
                    int nSizeRead = 0;
                    do {
                        memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                        nSizeRead = reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                        buffer->write(tBuffer, nSizeRead);
                    } while (nSizeRead == TRW_RENDER_BUFFER_SIZE);
                    break;
                }
                case TemplateRenderWizard::Token::Type::PlainValueType: {
                    IOBuffer::IOReader* reader = token->getReader();
                    memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                    reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                    TemplateRenderWizard::Tree::LeafElement* leafElement = this->tree->get(tBuffer);
                    if (leafElement != nullptr) {
                        switch (leafElement->getType()) {
                            case TemplateRenderWizard::Tree::LeafElementType::LeafElementText: {
                                std::string* tbValue = (std::string*) leafElement->getData();
                                buffer->write((char*) tbValue->c_str(), strlen(tbValue->c_str()));
                                break;
                            }
                        }
                    }
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::CloseTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenControlTagType: {
                    this->renderControlExpression();
                }
            }

            token = this->stream->getNextToken();
        }

        free(tBuffer);

        return buffer;
    }

    void Render::renderControlExpression()
    {
        TemplateRenderWizard::Token::Token* token;
        token = this->stream->getNextToken();

        if (token->getType() != TemplateRenderWizard::Token::Type::KeywordType) {
            throw new UnexpectedToken;
        }

        char* keyword = new char[32];
        memset(keyword, 0, sizeof(char) * 32);
        token->getReader()->read(keyword, 32);

        if (strcmp(keyword, "if") == 0) {
            // calculate condition
            this->ifExpressionControlTag();
        }
    }

    bool Render::ifExpressionControlTag() {
        std::list<TemplateRenderWizard::Token::Token*> tokens;

        TemplateRenderWizard::Token::Token* token;
        token = this->stream->getNextToken();

        while (token->getType() != TemplateRenderWizard::Token::Type::CloseControlTagType) {
            tokens.push_back(token);
            token = this->stream->getNextToken();
        }

        bool leftSide = true;
        std::list<TemplateRenderWizard::Token::Token*> lTokens, rTokens;
        TemplateRenderWizard::Token::Token* cmpToken;

        for (auto it = tokens.begin(); it != tokens.end(); it++) {
            if (leftSide) {
                if ((*it)->getType() == TemplateRenderWizard::Token::Type::CompareType) {
                    leftSide = false;
                    cmpToken = *it;
                    continue;
                }
                lTokens.push_back(*it);
            } else {
                rTokens.push_back(*it);
            }
        }

        this->compare_value(this->get_value(&lTokens), this->get_value(&rTokens), cmpToken);

        return true;
    }

    Value* Render::get_value(std::list<Token::Token*> *tokens) {
        Token::Token* token = nullptr;
        int count = 0;
        for (auto it = tokens->begin(); it != tokens->end(); it++) {
            token = *it;
            count++;
        }

        if (count == 1) {
            return this->getValueFromToken(token);
        }

        std::list<SyntaxElement*> lElement;
        for (auto it = tokens->begin(); it != tokens->end(); it++) {
            lElement.push_back(new SyntaxElement(*it));
        }

        // do analyze and separate by expressions

        return nullptr;
    }

    Value* Render::getValueFromToken(Token::Token *token) {
        if (token->getType() != TemplateRenderWizard::Token::Type::ExpressionValueType) {
            throw new UnexpectedToken;
        }

        char* tokenValue = (char*) malloc(sizeof(char) * 128);
        memset(tokenValue, 0, sizeof(char) * 128);
        token->getReader()->read(tokenValue, 128);

        auto leafValue = this->tree->get(tokenValue);
        if (leafValue != nullptr) {
            leafValue->getType();
        } else {
            Value* v = new Value;
            int length = strlen(tokenValue) + 1;
            char* strValue = (char*) malloc(length * sizeof(char));
            memset(strValue, 0, sizeof(char) * length);
            memcpy(strValue, tokenValue, sizeof(char) * length);
            v->setData(strValue);
            return v;
        }

        return nullptr;
    }

    int Render::compare_value(Value *v1, Value *v2, Token::Token *token) {
        return 0;
    }
}

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

        // todo: compare(get_value(tokens), get_value(tokens), condition_token)

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

        // do analyze and separate by expressions

        return nullptr;
    }

    Value* Render::getValueFromToken(Token::Token *token) {
        if (token->getType() != TemplateRenderWizard::Token::Type::ExpressionValueType) {
            throw new UnexpectedToken;
        }

        return nullptr;
    }
}

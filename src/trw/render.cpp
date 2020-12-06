#include <trw/render.h>
#include <io-buffer.h>
#include <memory.h>
#include <iostream>
#include <trw/exceptions.h>

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
    }
}

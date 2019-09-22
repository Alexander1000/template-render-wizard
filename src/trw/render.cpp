#include <trw/render.h>
#include <io-buffer.h>
#include <memory.h>
#include <iostream>

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
                    IOBuffer::IOReader *reader = token->getReader();
                    int nSizeRead = 0;
                    do {
                        memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
                        nSizeRead = reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
                        buffer->write(tBuffer, nSizeRead);
                    } while (nSizeRead == TRW_RENDER_BUFFER_SIZE);
                    break;
                }
                case TemplateRenderWizard::Token::Type::PlainValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::OpenTagValueType: {
                    break;
                }
                case TemplateRenderWizard::Token::Type::CloseTagValueType: {
                    break;
                }
            }

            token = this->stream->getNextToken();
        }

        free(tBuffer);

        return buffer;
    }
}

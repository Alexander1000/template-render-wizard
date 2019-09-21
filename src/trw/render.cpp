#include <trw/render.h>
#include <io-buffer.h>
#include <memory.h>
#include <iostream>

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
        buffer = new IOBuffer::IOMemoryBuffer(4096);
        char* tBuffer = (char*) malloc(sizeof(char) * 1024);

        TemplateRenderWizard::Token::Token* token;
        token = this->stream->getNextToken();
        if (token != nullptr && token->getType() == TemplateRenderWizard::Token::Type::PlainTextType) {
            IOBuffer::IOReader* reader = token->getReader();
            int nSizeRead = 0;
            do {
                memset(tBuffer, 0, sizeof(char) * 1024);
                nSizeRead = reader->read(tBuffer, 1024);
                buffer->write(tBuffer, nSizeRead);
            } while(nSizeRead == 1024);
        }

        free(tBuffer);

        return buffer;
    }
}

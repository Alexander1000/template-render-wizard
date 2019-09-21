#include <trw/render.h>
#include <io-buffer.h>
#include <memory.h>
#include <iostream>

namespace TemplateRenderWizard
{
    Render::Render(std::string* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        IOBuffer::IOFileReader fileReader(srcTemplateFile->c_str());
        IOBuffer::CharStream charStream(&fileReader);
        this->stream = new TemplateRenderWizard::Stream(&charStream);
        this->tree = tree;
    }

    Render::Render(const char* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        IOBuffer::IOFileReader fileReader(srcTemplateFile);
        IOBuffer::CharStream charStream(&fileReader);
        this->stream = new TemplateRenderWizard::Stream(&charStream);
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

        std::cout << "Before get token" << std::endl;

        TemplateRenderWizard::Token::Token* token;
        token = this->stream->getNextToken();
        std::cout << "Before if" << std::endl;
        if (token != nullptr && token->getType() == TemplateRenderWizard::Token::Type::PlainTextType) {
            IOBuffer::IOReader* reader = token->getReader();
            int nSizeRead = 0;
            std::cout << "Before loop" << std::endl;
            do {
                memset(tBuffer, 0, sizeof(char) * 1024);
                nSizeRead = reader->read(tBuffer, 1024);
                buffer->write(tBuffer, nSizeRead);
                std::cout << "Size:" << nSizeRead << std::endl;
            } while(nSizeRead == 1024);
        }

        free(tBuffer);

        return buffer;
    }
}

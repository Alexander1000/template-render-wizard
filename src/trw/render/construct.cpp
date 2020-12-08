#include <trw.h>
#include <stack>
#include <io-buffer.h>
#include <string>

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
        this->tokenStack = new std::stack<Token::Token*>;
    }

    Render::Render(const char* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(srcTemplateFile);
        IOBuffer::CharStream* charStream;
        charStream = new IOBuffer::CharStream(fileReader);
        this->stream = new TemplateRenderWizard::Stream(charStream);
        this->tree = tree;
        this->tokenStack = new std::stack<Token::Token*>;
    }

    Render::Render(TemplateRenderWizard::Stream* stream, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->stream = stream;
        this->tree = tree;
        this->tokenStack = new std::stack<Token::Token*>;
    }
}

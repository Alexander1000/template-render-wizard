#include <trw.h>
#include <stack>
#include <io-buffer.h>
#include <string>

namespace TemplateRenderWizard
{
    Render::Render(std::string* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->tplFile = (const char*) malloc(sizeof(char) * (srcTemplateFile->length() + 1));
        memset((char*) this->tplFile, 0, sizeof(char) * (srcTemplateFile->length() + 1));
        memcpy((char*) this->tplFile, srcTemplateFile->c_str(), sizeof(char) * srcTemplateFile->length());

        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(srcTemplateFile->c_str());
        IOBuffer::CharStream* charStream;
        charStream = new IOBuffer::CharStream(fileReader);
        this->stream = new TemplateRenderWizard::Lexer::Lexer(charStream);
        this->tree = tree;
    }

    Render::Render(const char* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->tplFile = (const char*) malloc(sizeof(char) * (strlen(srcTemplateFile) + 1));
        memset((char*) this->tplFile, 0, sizeof(char) * (strlen(srcTemplateFile) + 1));
        memcpy((char*) this->tplFile, srcTemplateFile, sizeof(char) * strlen(srcTemplateFile));

        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(srcTemplateFile);
        IOBuffer::CharStream* charStream;
        charStream = new IOBuffer::CharStream(fileReader);
        this->stream = new TemplateRenderWizard::Lexer::Lexer(charStream);
        this->tree = tree;
    }

    Render::Render(TemplateRenderWizard::Lexer::Lexer* stream, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->tplFile = nullptr;
        this->stream = stream;
        this->tree = tree;
    }
}

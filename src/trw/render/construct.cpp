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

        this->fileReader = new IOBuffer::IOFileReader(srcTemplateFile->c_str());
        this->charStream = new IOBuffer::CharStream(this->fileReader);
        this->stream = new TemplateRenderWizard::Lexer::Lexer(this->charStream);
        this->tree = tree;
    }

    Render::Render(const char* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->tplFile = (const char*) malloc(sizeof(char) * (strlen(srcTemplateFile) + 1));
        memset((char*) this->tplFile, 0, sizeof(char) * (strlen(srcTemplateFile) + 1));
        memcpy((char*) this->tplFile, srcTemplateFile, sizeof(char) * strlen(srcTemplateFile));

        this->fileReader = new IOBuffer::IOFileReader(srcTemplateFile);
        this->charStream = new IOBuffer::CharStream(this->fileReader);
        this->stream = new TemplateRenderWizard::Lexer::Lexer(this->charStream);
        this->tree = tree;
    }

    Render::Render(TemplateRenderWizard::Lexer::Lexer* stream, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->fileReader = nullptr;
        this->charStream = nullptr;
        this->tplFile = nullptr;
        this->stream = stream;
        this->tree = tree;
    }

    Render::~Render() {
        delete this->stream;
        if (this->charStream != nullptr) {
            delete this->charStream;
        }
        if (this->fileReader != nullptr) {
            delete this->fileReader;
        }
        if (this->tplFile != nullptr) {
            free((char*) this->tplFile);
        }
    }
}

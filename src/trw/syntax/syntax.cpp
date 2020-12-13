#include <trw.h>

namespace TemplateRenderWizard
{
    TokenFile::TokenFile(const char *tokenFile)
    {
        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(tokenFile);
        this->charStream = new IOBuffer::CharStream(fileReader);
    }
}

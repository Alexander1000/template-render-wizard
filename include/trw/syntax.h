#ifndef H_TRW_SYNTAX_INCLUDED
#define H_TRW_SYNTAX_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <map>
#include <string>

namespace TemplateRenderWizard
{
    class UnknownToken
    {};

    class TokenFile
    {
    public:
        TokenFile(const char* tokenFile);
        TemplateRenderWizard::Token::Type getNextTokenType();
        TemplateRenderWizard::Token::Type getTokenTypeByName(const char*);

    private:
        IOBuffer::CharStream* charStream;
        std::map<std::string, TemplateRenderWizard::Token::Type>* tokenMap;

        bool isEmptyChar(char*);
    };
}

#endif

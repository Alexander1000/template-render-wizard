#ifndef H_TRW_SYNTAX_INCLUDED
#define H_TRW_SYNTAX_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <list>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard
{
    class TokenFile
    {
    public:
        TokenFile(const char* tokenFile);
        TemplateRenderWizard::Token::Type getNextTokenType();
        TemplateRenderWizard::Token::Type getTokenTypeByName(const char*);

    private:
        IOBuffer::CharStream* charStream;
        TemplateRenderWizard::Token::TokenMap* tokenMap;

        bool isEmptyChar(char*);
    };

    namespace Syntax
    {
        class Tree : public SyntaxTree::Syntax::Tree
        {
        public:
            Tree();

        protected:
            void initializeDefaults();
        };
    }
}

#endif

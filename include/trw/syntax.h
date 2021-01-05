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
        int getNextTokenType();
        int getTokenTypeByName(const char*);

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
            void initializeDefaults() override;

        protected:
            std::list<SyntaxTree::Syntax::Rule*>* mathRules;

            SyntaxTree::Syntax::SyntaxElement* beforeParse(std::list<SyntaxTree::Syntax::SyntaxElement*>*) override;

        private:
            SyntaxTree::Syntax::SyntaxElement* parseBrackets(std::list<SyntaxTree::Syntax::SyntaxElement*>*);
        };
    }
}

#endif

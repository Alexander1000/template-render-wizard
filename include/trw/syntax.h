#ifndef H_TRW_SYNTAX_INCLUDED
#define H_TRW_SYNTAX_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <list>

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
        enum RuleMatchType {
            RuleMatchTokenType,
            RuleMatchName,
        };

        class Tree
        {
        public:
            Tree();
        };

        class RuleMatch
        {
        public:
            explicit RuleMatch(TemplateRenderWizard::Token::Type);
            explicit RuleMatch(const char*);
        private:
            RuleMatchType type;
            union {
                TemplateRenderWizard::Token::Type tokenType;
                const char* ruleName;
            } value{};
        };

        class Rule
        {
        public:
            Rule();

        private:
            char* name;
            std::list<RuleMatch*> matches;
        };

        class SyntaxRuleElement
        {
        public:
            SyntaxRuleElement();
        };
    }
}

#endif

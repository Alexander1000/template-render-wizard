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

        enum SyntaxElementType {
            SyntaxType,
            TokenType,
        };

        class RuleMatch
        {
        public:
            explicit RuleMatch(TemplateRenderWizard::Token::Type);
            explicit RuleMatch(const char*);
            RuleMatchType getType();
            TemplateRenderWizard::Token::Type getTokenType();
            const char* getRuleName();
        private:
            RuleMatchType type;
            union {
                TemplateRenderWizard::Token::Type tokenType;
                const char* ruleName;
            } value;
        };

        class Rule
        {
        public:
            Rule(const char*);
            void addMatch(RuleMatch*);
            std::list<RuleMatch*>* getMatches();
            const char* getName();
        private:
            const char* name;
            std::list<RuleMatch*>* matches;
        };

        class SyntaxElement
        {
        public:
            SyntaxElement(TemplateRenderWizard::Token::Token*);
            SyntaxElement(SyntaxElement*);
            Rule* getRule();
            SyntaxElementType getType();
            TemplateRenderWizard::Token::Token* getToken();
            SyntaxElement* getElement();

        private:
            Rule* rule;
            SyntaxElementType type;
            union {
                TemplateRenderWizard::Token::Token* token;
                SyntaxElement* syntaxElement;
            } data;
        };

        class Tree
        {
        public:
            Tree();
            SyntaxElement* parse(std::list<TemplateRenderWizard::Token::Token*>*);

        private:
            std::list<Rule*>* rules;
            TemplateRenderWizard::Token::TokenMap* tokenMap;

            void initializeDefaults();

            SyntaxElement* parse(std::list<SyntaxElement*>*);

            std::list<SyntaxElement*>* run_rule(Rule*, std::list<SyntaxElement*>*);
        };
    }
}

#endif

#ifndef H_TRW_STREAM_INCLUDED
#define H_TRW_STREAM_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <stack>
#include <trw/position.h>
#include <list>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Lexer
{
    enum StreamMode{
        PlainText,
        ValueMode,
        ControlModeExpression,
        ControlModeForExpression,
        ControlModeIncludeExpression,
        ControlModeIncludeWithExpression,
        ControlModeIncludeWithValueExpression,
    };

    class Lexer
    {
    public:
        Lexer(IOBuffer::CharStream* charStream);
        SyntaxTree::Token::Token* getNextToken();
        ~Lexer();

    private:
        IOBuffer::CharStream* charStream;
        StreamMode mode;
        std::stack<char*>* charStack;
        std::stack<Position*>* positionStack;
        std::stack<StreamMode>* modeStack;
        std::list<std::string>* keywords;

        Position *position;

        SyntaxTree::Token::Token* getNextTokenIncludeMode();
        SyntaxTree::Token::Token* getNextTokenIncludeWithMode();
        SyntaxTree::Token::Token* getNextTokenIncludeWithValueMode();

        void switchToMode(StreamMode);
        void switchToPreviousMode();

        char* getNextChar();
        void pushStackChar(char*);

        static bool isWord(const char* symbol);
        static bool isDigit(const char* symbol);

        bool isKeyword(std::string*);
        bool isKeyword(const char*);
    };
}

#endif

#ifndef H_TRW_STREAM_INCLUDED
#define H_TRW_STREAM_INCLUDED

#include <io-buffer.h>
#include <trw/token.h>
#include <stack>
#include <trw/position.h>

namespace TemplateRenderWizard
{
    enum StreamMode{
        PlainText,
        ValueMode,
        ControlMode,
        ControlModeExpression,
        ControlModeForExpression,
    };

    class Stream
    {
    public:
        Stream(IOBuffer::CharStream* charStream);
        Token::Token* getNextToken();

    private:
        IOBuffer::CharStream* charStream;
        StreamMode mode;
        std::stack<char*>* charStack;
        std::stack<Position*>* positionStack;
        std::stack<StreamMode>* modeStack;

        Position *position;

        void switchToMode(StreamMode);
        void switchToPreviousMode();

        char* getNextChar();
        void pushStackChar(char*);

        static bool isWord(const char* symbol);
    };
}

#endif

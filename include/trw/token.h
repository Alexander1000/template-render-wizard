#ifndef H_TOKEN_INCLUDED
#define H_TOKEN_INCLUDED

namespace TemplateRenderWizard::Token
{
    enum Type {
        PlainTextType,
        OpenTagValueType
    };

    class Token
    {
    public:
        Token();
        virtual Type getType() = 0;
    };

    class OpenTagValue : public Token
    {
    public:
        OpenTagValue();
        Type getType();
    };

    class PlainText : public Token
    {
    public:
        PlainText();
        Type getType();
    };
}

#endif

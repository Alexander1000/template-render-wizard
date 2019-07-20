#ifndef H_TOKEN_INCLUDED
#define H_TOKEN_INCLUDED

namespace TemplateRenderWizard::Token
{
    class Token
    {
    public:
        Token();
    };

    class OpenTagValue : public Token
    {
    public:
        OpenTagValue();
    };

    class PlainText : public Token
    {
    public:
        PlainText();
    };
}

#endif

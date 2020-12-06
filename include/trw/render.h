#ifndef H_TRW_RENDER_INCLUDED
#define H_TRW_RENDER_INCLUDED

#include <string>
#include <trw/stream.h>
#include <trw/tree_parameters.h>
#include <io-buffer.h>

namespace TemplateRenderWizard
{
    class Render
    {
        TemplateRenderWizard::Tree::Tree* tree;
        TemplateRenderWizard::Stream* stream;

        void renderControlExpression();
        bool ifExpressionControlTag();

    public:
        Render(const char*, TemplateRenderWizard::Tree::Tree*);
        Render(std::string*, TemplateRenderWizard::Tree::Tree*);
        Render(TemplateRenderWizard::Stream*, TemplateRenderWizard::Tree::Tree*);
        IOBuffer::IOMemoryBuffer* toBuffer();
    };
}

#endif

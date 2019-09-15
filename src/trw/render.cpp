#include <trw/render.h>
#include <io-buffer.h>

namespace TemplateRenderWizard
{
    Render::Render(std::string* srcTemplateFile, TemplateRenderWizard::Tree::Tree* tree)
    {
        IOBuffer::IOFileReader fileReader(srcTemplateFile->c_str());
        IOBuffer::CharStream charStream(&fileReader);
        this->stream = new TemplateRenderWizard::Stream(&charStream);
        this->tree = tree;
    }

    Render::Render(TemplateRenderWizard::Stream* stream, TemplateRenderWizard::Tree::Tree* tree)
    {
        this->stream = stream;
        this->tree = tree;
    }

    void Render::save()
    {
        // do render
    }
}

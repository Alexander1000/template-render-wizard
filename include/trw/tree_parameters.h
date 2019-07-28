#ifndef H_TRW_TREE_PARAMETERS
#define H_TRW_TREE_PARAMETERS

namespace TemplateRenderWizard::Tree
{
    class LeafElement
    {
    public:
        LeafElement();
    };

    class Tree
    {
    public:
        Tree();

    private:
        LeafElement* root;
    };
}

#endif

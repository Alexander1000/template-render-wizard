#ifndef H_TRW_TREE_PARAMETERS
#define H_TRW_TREE_PARAMETERS

#include <string>

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
        void scan(std::string*);

    private:
        LeafElement* root;
    };
}

#endif

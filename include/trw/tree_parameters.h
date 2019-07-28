#ifndef H_TRW_TREE_PARAMETERS
#define H_TRW_TREE_PARAMETERS

#include <string>

namespace TemplateRenderWizard::Tree
{
    enum LeafElementType {
        LeafElementObject,
        LeafElementArray,
        LeafElementText
    };

    class LeafElement
    {
    public:
        LeafElement(LeafElementType, void*);
        LeafElementType getType();
        void* getData();
    private:
        LeafElementType type;
        void* data;
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

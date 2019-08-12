#ifndef H_TRW_TREE_PARAMETERS
#define H_TRW_TREE_PARAMETERS

#include <string>
#include <yaml-parser.h>

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
        void scan(const char*);

    private:
        LeafElement* root;

        void merge(LeafElement*, YamlParser::Element*);
        LeafElement* convert(YamlParser::Element*);
    };

    class UnexpectedLeafElementException
    {
    };
}

#endif

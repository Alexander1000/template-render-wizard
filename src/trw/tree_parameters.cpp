#include <trw/tree_parameters.h>
#include <string>
#include <io-buffer.h>
#include <yaml-parser.h>
#include <map>

typedef std::map<std::string, YamlParser::Element*> YamlObject;

namespace TemplateRenderWizard::Tree
{
    Tree::Tree() {
        std::map<std::string, LeafElement*>* rootObject = nullptr;
        rootObject = new std::map<std::string, LeafElement*>;
        this->root = new LeafElement(LeafElementType::LeafElementObject, rootObject);
    }

    void Tree::scan(std::string* fileName)
    {
        IOBuffer::IOFileReader fileReader(fileName->c_str());
        IOBuffer::CharStream charStream(&fileReader);
        YamlParser::Stream yamlStream(&charStream);
        YamlParser::Decoder decoder(&yamlStream);

        YamlParser::Element* valuesObject = decoder.parse();
        this->merge(this->root, valuesObject);
    }

    void Tree::merge(LeafElement* leaf, YamlParser::Element* yamlElement)
    {
        switch (yamlElement->getType()) {
            case YamlParser::ElementType::ObjectType: {
                YamlObject* yamlObject = (YamlObject*) yamlElement->getData();
                YamlObject::iterator itYamlObject;
                for (itYamlObject = yamlObject->begin(); itYamlObject != yamlObject->end(); itYamlObject++) {
                    // itYamlObject->first;
                    // itYamlObject->second;
                }
                break;
            }
        }
    }
}

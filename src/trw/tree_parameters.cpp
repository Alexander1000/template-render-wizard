#include <trw/tree_parameters.h>
#include <string>
#include <io-buffer.h>
#include <yaml-parser.h>
#include <map>
#include <list>

typedef std::map<std::string, YamlParser::Element*> YamlObject;
typedef std::map<std::string, TemplateRenderWizard::Tree::LeafElement*> LeafObject;
typedef std::list<YamlParser::Element*> YamlArray;
typedef std::list<TemplateRenderWizard::Tree::LeafElement*> LeafArray;

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
                LeafObject* leafObject = (LeafObject*) leaf->getData();
                YamlObject* yamlObject = (YamlObject*) yamlElement->getData();
                YamlObject::iterator itYamlObject;
                for (itYamlObject = yamlObject->begin(); itYamlObject != yamlObject->end(); itYamlObject++) {
                    (*leafObject)[itYamlObject->first] = this->convert(itYamlObject->second);
                }
                break;
            }
        }
    }

    LeafElement* Tree::convert(YamlParser::Element* yamlElement) {
        switch (yamlElement->getType())  {
            case YamlParser::ElementType::PlainTextType: {
                return new LeafElement(LeafElementType::LeafElementText, yamlElement->getData());
            }
            case YamlParser::ElementType::ListType: {

                break;
            }
            case YamlParser::ElementType::ObjectType: {
                break;
            }
        }
        return nullptr;
    }
}

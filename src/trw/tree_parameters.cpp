#include <trw.h>
#include <string>
#include <io-buffer.h>
#include <yaml-parser.h>
#include <map>
#include <list>
#include <cstring>

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
        this->scan(fileName->c_str());
    }

    void Tree::scan(const char* fileName)
    {
        IOBuffer::IOFileReader fileReader(fileName);
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
                if (leaf->getType() != LeafElementType::LeafElementObject) {
                    throw new UnexpectedLeafElementException;
                }
                LeafObject* leafObject = (LeafObject*) leaf->getData();
                YamlObject* yamlObject = (YamlObject*) yamlElement->getData();
                YamlObject::iterator itYamlObject;
                for (itYamlObject = yamlObject->begin(); itYamlObject != yamlObject->end(); itYamlObject++) {
                    (*leafObject)[itYamlObject->first] = this->convert(itYamlObject->second);
                }
                break;
            }
            case YamlParser::ElementType::ListType: {
                break;
            }
            case YamlParser::ElementType::PlainTextType: {
                break;
            }
        }
    }

    LeafElement* Tree::convert(YamlParser::Element* yamlElement)
    {
        switch (yamlElement->getType())  {
            case YamlParser::ElementType::PlainTextType: {
                return new LeafElement(LeafElementType::LeafElementText, yamlElement->getData());
            }
            case YamlParser::ElementType::ListType: {
                LeafArray* lArray;
                lArray = new LeafArray;
                YamlArray* yArray = (YamlArray*) yamlElement->getData();
                YamlArray::iterator it;
                for (it = yArray->begin(); it != yArray->end(); it++) {
                    lArray->push_back(this->convert(*it));
                }
                return new LeafElement(TemplateRenderWizard::Tree::LeafElementType::LeafElementArray, lArray);
            }
            case YamlParser::ElementType::ObjectType: {
                LeafObject* leafObject;
                leafObject = new LeafObject;
                YamlObject* yamlObject = (YamlObject*) yamlElement->getData();
                YamlObject::iterator itYamlObject;
                for (itYamlObject = yamlObject->begin(); itYamlObject != yamlObject->end(); itYamlObject++) {
                    (*leafObject)[itYamlObject->first] = this->convert(itYamlObject->second);
                }
                return new LeafElement(TemplateRenderWizard::Tree::LeafElementType::LeafElementObject, leafObject);
            }
        }
        return nullptr;
    }

    LeafElement* Tree::get(const char* path)
    {
        if (path == nullptr) {
            return this->root;
        }

        LeafElement* foundElement = nullptr;
        LeafElement* relativeElement = this->root;

        auto pathParts = explode_string(path, '.');

        for (auto it = pathParts->begin(); it != pathParts->end(); it++) {
            const char* leafName = *it;

            if (relativeElement->getType() == LeafElementType::LeafElementObject) {
                auto tlObject = (LeafObject*) relativeElement->getData();
                if (tlObject->find(leafName) != tlObject->end()) {
                    relativeElement = tlObject->at(leafName);
                    if (std::next(it) == pathParts->end()) {
                        foundElement = relativeElement;
                    }
                } else {
                    // not found
                    return nullptr;
                }
            }
        }

        return foundElement;
    }

    void Tree::mergeValues(std::map<std::string, std::string>* values)
    {
        for (auto it = values->begin(); it != values->end(); it++) {
            const char* key = it->first.c_str();
            this->setValue(key, &(it->second));
        }
    }

    void Tree::setValue(const char *key, std::string *value)
    {

    }
}

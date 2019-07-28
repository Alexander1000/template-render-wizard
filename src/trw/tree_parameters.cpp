#include <trw/tree_parameters.h>
#include <string>
#include <io-buffer.h>
#include <yaml-parser.h>

namespace TemplateRenderWizard::Tree
{
    Tree::Tree() {
        this->root = nullptr;
    }

    void Tree::scan(std::string* fileName)
    {
        IOBuffer::IOFileReader fileReader(fileName->c_str());
        IOBuffer::CharStream charStream(&fileReader);
        YamlParser::Stream yamlStream(&charStream);
        YamlParser::Decoder decoder(&yamlStream);

        YamlParser::Element* valuesObject = decoder.parse();
    }
}

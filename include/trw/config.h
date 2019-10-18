#ifndef H_TRW_CONFIG_INCLUDED
#define H_TRW_CONFIG_INCLUDED

#include <trw/tree_parameters.h>
#include <string>
#include <map>

namespace TemplateRenderWizard
{
    class Config
    {
    public:
        Config(int argc, char** argv);

        bool isHelp();
        const char* getHelpText();

        bool isVersion();
        const char* getVersionText();

        std::string* getTemplateFile();
        std::string* getValuesFile();

        std::map<std::string, std::string>* getValues();

        Tree::Tree* getTree();

    private:
        bool is_help;
        bool is_version;

        std::map<std::string, std::string>* values;

        std::string* templateFile;
        std::string* valuesFile;
        std::string* outputFile;

        Tree::Tree* tree;
    };
}

#endif

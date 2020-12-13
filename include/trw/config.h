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
        static const char* getHelpText();

        bool isVersion();
        static const char* getVersionText();

        std::string* getTemplateFile();
        std::string* getValuesFile();

        std::map<std::string, std::string>* getValues();

        Tree::Tree* getTree();

        bool isDumpTokens();

    private:
        bool is_help;
        bool is_version;
        bool is_dump_tokens;

        std::map<std::string, std::string>* values;

        std::string* templateFile;
        std::string* valuesFile;
        std::string* outputFile;

        Tree::Tree* tree;
    };
}

#endif

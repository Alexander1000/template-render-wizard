#include <trw.h>
#include <string>
#include <map>

namespace TemplateRenderWizard
{
    Config::Config(int argc, char** argv)
    {
        // defaults:
        this->is_help = false;
        this->is_version = false;

        this->templateFile = nullptr;
        this->valuesFile = nullptr;
        this->outputFile = nullptr;

        this->tree = new Tree::Tree();

        this->values = new std::map<std::string, std::string>;

        // initialize parameters
        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if (paramName == "-h" || paramName == "--help") {
                this->is_help = true;
                break;
            }

            if (paramName == "-v" || paramName == "--version") {
                this->is_version = true;
                break;
            }

            if (paramName == "-o" || paramName == "--output") {
                this->outputFile = new std::string(argv[i+1]);
                i++;
                continue;
            }

            if (paramName == "--values") {
                this->tree->scan(new std::string(argv[i+1]));
                i++;
                continue;
            }

            if (paramName == "--set") {
                std::string paramValue = argv[i+1];
                for (int j = 0; j < paramValue.size(); j++) {
                    if (paramValue[j] == '=') {
                        char* objParam = (char*) malloc(sizeof(char) * j);
                        memset(objParam, 0, sizeof(char) * j);
                        memcpy(objParam, paramValue.c_str(), j);

                        char* objValue = (char*) malloc(sizeof(char) * (paramValue.size() - j - 1));
                        memset(objValue, 0, (paramValue.size() - j - 1));
                        memcpy(objValue, paramValue.c_str() + j + 1, paramValue.size() - j - 1);

                        (*this->values)[std::string(objParam)] = std::string(objValue);
                        break;
                    }
                }
                i++;
                continue;
            }

            if (i == argc - 1) {
                this->templateFile = new std::string(paramName);
            }
        }
    }

    std::string* Config::getTemplateFile()
    {
        return this->templateFile;
    }

    std::string* Config::getValuesFile()
    {
        return this->valuesFile;
    }

    bool Config::isVersion()
    {
        return this->is_version;
    }

    const char* Config::getVersionText()
    {
        return "template-render-wizard [trw] version: " TRW_VERSION "\n";
    }

    bool Config::isHelp()
    {
        return this->is_help;
    }

    const char* Config::getHelpText()
    {
        return "Usage: trw [OPTIONS] template-file.tpl\n"
           "Common options:\n"
           "    -h, --help                 Show this message and exit.\n"
           "        --set [string array]   Set value for property.\n"
           "        --values [file]        Yaml-file with values for placeholders for template.\n"
           "    -o, --output [file]        Output template render, by default stdout.\n"
           "    -v, --version              Print version and exit.";
    }

    Tree::Tree* Config::getTree()
    {
        return this->tree;
    }

    std::map<std::string, std::string>* Config::getValues()
    {
        return this->values;
    }
}

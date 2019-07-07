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

        this->templateFile = NULL;
        this->valuesFile = NULL;
        this->outputFile = NULL;

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
                this->valuesFile = new std::string(argv[i+1]);
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
}

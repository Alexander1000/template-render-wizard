#include <trw.h>
#include <string>
#include <map>

namespace TRW
{
    Config::Config(int argc, char** argv)
    {
        this->setDefaults();

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
        }
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

    void Config::setDefaults()
    {
        this->is_help = false;
        this->is_version = false;

        this->templateFile = NULL;
        this->valuesFile = NULL;

        this->values = new std::map<std::string, std::string>;
    }
}

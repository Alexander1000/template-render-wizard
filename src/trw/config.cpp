#include <trw/config.h>
#include <string>

namespace TRW
{
    Config::Config(int argc, char** argv)
    {
        this->setDefaults();

        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if (paramName == "-h" || paramName == "--help") {
                this->is_help = true;
                continue;
            }
        }
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
           "    -v, --values [file]        Yaml-file with values for placeholders for template.\n"
           "    -o, --output [file]        Output template render, by default stdout.\n";
    }

    void Config::setDefaults()
    {
        this->is_help = false;
    }
}

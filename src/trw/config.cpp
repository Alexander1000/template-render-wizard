#include <trw/config.h>
#include <string>

namespace TRW
{
    Config::Config(int argc, char** argv)
    {
        this->setDefaults();

        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if (paramName.compare("-h") == 0 || paramName.compare("--help") == 0) {
                this->is_help = true;
                continue;
            }
        }
    }

    bool Config::isHelp()
    {
        return this->is_help;
    }

    void Config::setDefaults()
    {
        this->is_help = false;
    }
}

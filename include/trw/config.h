#ifndef H_TRW_CONFIG_INCLUDED
#define H_TRW_CONFIG_INCLUDED

#include <string>

namespace TRW
{
    class Config
    {
    public:
        Config(int argc, char** argv);

        bool isHelp();
        const char* getHelpText();

        bool isVersion();
        const char* getVersionText();

    private:
        bool is_help;
        bool is_version;

        void setDefaults();
    };
}

#endif

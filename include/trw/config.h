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

    private:
        bool is_help;

        void setDefaults();
    };
}

#endif

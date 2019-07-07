#ifndef H_TRW_CONFIG_INCLUDED
#define H_TRW_CONFIG_INCLUDED

namespace TRW
{
    class Config
    {
    public:
        Config(int argc, char** argv);
        bool isHelp();

    private:
        bool is_help;

        void setDefaults();
    };
}

#endif

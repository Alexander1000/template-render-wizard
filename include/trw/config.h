#ifndef H_TRW_CONFIG_INCLUDED
#define H_TRW_CONFIG_INCLUDED

namespace TRW
{
    class Config
    {
    public:
        Config(int argc, char** argv);

    private:
        int argc;
        char** argv;
    };
}

#endif

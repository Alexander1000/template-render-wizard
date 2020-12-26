#include <tests.h>
#include <string>
#include <dirent.h>

namespace TrwTests
{
    int filter_tpl(const struct dirent* dir_ent)
    {
        if (!strcmp(dir_ent->d_name, ".") || !strcmp(dir_ent->d_name, "..")) {
            return 0;
        }

        std::string fname = dir_ent->d_name;

        if (fname.find(".tpl") == std::string::npos) {
            return 0;
        }

        return 1;
    }

    int filter_yaml(const struct dirent* dir_ent)
    {
        if (!strcmp(dir_ent->d_name, ".") || !strcmp(dir_ent->d_name, "..")) {
            return 0;
        }

        std::string fname = dir_ent->d_name;

        if (fname.find(".yaml") == std::string::npos) {
            return 0;
        }

        return 1;
    }
}

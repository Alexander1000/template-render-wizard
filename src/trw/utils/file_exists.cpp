#include <trw.h>
#include <sys/stat.h>

namespace TemplateRenderWizard
{
    bool file_exists(const std::string* name)
    {
        struct stat buffer;
        return (stat(name->c_str(), &buffer) == 0);
    }

    bool file_exists(const char* name)
    {
        struct stat buffer;
        return (stat(name, &buffer) == 0);
    }
}

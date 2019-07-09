/**
 * template-render-wizard
 */

#include <iostream>
#include <string>
#include <sys/stat.h>

#include <trw.h>

inline bool file_exists(const std::string* name)
{
    struct stat buffer;
    return (stat(name->c_str(), &buffer) == 0);
}

int main(int argc, char** argv) {
    TemplateRenderWizard::Config config(argc, argv);

    if (config.isHelp()) {
        std::cout << config.getHelpText() << std::endl;
        return 0;
    }

    if (config.isVersion()) {
        std::cout << config.getVersionText() << std::endl;
        return 0;
    }

    std::string* templateFile = config.getTemplateFile();

    if (templateFile == NULL) {
        std::cout << "Template required" << std::endl;
        std::cout << config.getHelpText() << std::endl;
        return -1;
    }

    if (!file_exists(templateFile)) {
        std::cout << "Template file not exists" << std::endl;
        return -1;
    }

    return 0;
}

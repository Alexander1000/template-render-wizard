/**
 * template-render-wizard
 */

#include <iostream>

#include <trw.h>

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

    if (config.getTemplateFile() == NULL) {
        std::cout << "Template required" << std::endl;
        std::cout << config.getHelpText() << std::endl;
        return -1;
    }

    return 0;
}

/**
 * template-render-wizard
 */

#include <iostream>

#include <trw.h>

int main(int argc, char** argv) {
    TRW::Config config(argc, argv);

    if (config.isHelp()) {
        std::cout << config.getHelpText() << std::endl;
    }

    return 0;
}

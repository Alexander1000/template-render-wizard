/**
 * template-render-wizard
 */

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <memory.h>

#include <trw.h>
#include <io-buffer.h>

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

    IOBuffer::IOFileReader fileReader(templateFile->c_str());
    IOBuffer::CharStream charStream(&fileReader);
    TemplateRenderWizard::Stream tokenStream(&charStream);

    TemplateRenderWizard::Render* render;
    render = new TemplateRenderWizard::Render(&tokenStream, config.getTree());

    IOBuffer::IOMemoryBuffer* output = render->toBuffer();

    int nRead = 0;
    char* buffer = (char*) malloc(sizeof(char) * 1024);
    do {
        memset(buffer, 0, sizeof(char) * 1024);
        nRead = output->read(buffer, 1023);
        if (nRead > 0) {
            std::cout << buffer;
        }
    } while(nRead != 0);

    std::cout << std::endl;

    return 0;
}

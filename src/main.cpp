/**
 * template-render-wizard
 */

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <memory.h>

#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

inline bool file_exists(const std::string* name)
{
    struct stat buffer;
    return (stat(name->c_str(), &buffer) == 0);
}

void dump_tokens(IOBuffer::IOMemoryBuffer* buffer, TemplateRenderWizard::Lexer::Lexer* tokenStream) {
    TemplateRenderWizard::Token::TokenMap tokenMap;
    SyntaxTree::Token::Token* token;

    token = tokenStream->getNextToken();
    while (token != nullptr) {
        const char* type = tokenMap.getName(token->getType());
        buffer->write((char*) type, strlen(type));
        buffer->write("\n", 1);
        token = tokenStream->getNextToken();
    }
}

int main(int argc, char** argv) {
    TemplateRenderWizard::Config config(argc, argv);

    if (config.isUnknownCommand()) {
        std::cout << "Unknown command: " << config.getUnknownCommand()->c_str() << std::endl;
        std::cout << config.getHelpText() << std::endl;
        return 0;
    }

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

    TemplateRenderWizard::Tree::Tree tree;

    std::string* valuesFile = config.getValuesFile();
    if (valuesFile != nullptr) {
        if (!file_exists(valuesFile)) {
            std::cout << "Values file not exists" << std::endl;
            return -1;
        }
        tree.scan(valuesFile);
    }

    if (config.getValues() != nullptr) {
        tree.mergeValues(config.getValues());
    }

    IOBuffer::IOFileReader fileReader(templateFile->c_str());
    IOBuffer::CharStream charStream(&fileReader);
    TemplateRenderWizard::Lexer::Lexer tokenStream(&charStream);

    IOBuffer::IOMemoryBuffer* output;

    if (config.isDumpTokens()) {
        output = new IOBuffer::IOMemoryBuffer(1024);
        dump_tokens(output, &tokenStream);
    } else {
        TemplateRenderWizard::Render* render;
        render = new TemplateRenderWizard::Render(&tokenStream, &tree);

        output = render->toBufferTree(nullptr);
    }

    int nRead;
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

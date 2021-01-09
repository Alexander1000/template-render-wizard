#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>
#include <cstring>
#include <libgen.h>
#include <iostream>
#include <filesystem>

namespace TemplateRenderWizard
{
    void Render::render_tree_include(
        IOBuffer::IOBuffer *buffer,
        SyntaxTree::Syntax::Rule *rule,
        std::list<SyntaxTree::Syntax::SyntaxElement*> *elements,
        Context *context
    ) {
        if (strcmp(rule->getName(), "include_stmt") == 0) {
            // do something
            auto it = elements->begin(); // open control tag
            it++; // keyword include
            it++; // file name for render
            auto elFilePath = *it;
            if (elFilePath->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                throw new UnexpectedToken;
            }
            auto tFilePath = elFilePath->getToken();
            RESET_TOKEN_READER(tFilePath);
            INIT_CHAR_STRING(strFilePath, 64);
            tFilePath->getReader()->read(strFilePath, 63);

            IOBuffer::IOMemoryBuffer* ioBuffer = nullptr;

            if (this->tplFile != nullptr) {
                // check nearest template file
                auto path = std::filesystem::path(this->tplFile);
                path.remove_filename();
                auto dirName = path.c_str();
                // auto dirName = dirname((char*) this->tplFile);
                INIT_CHAR_STRING(strFileNearTpl, 1024);
                sprintf(strFileNearTpl, "%s/%s", dirName, strFilePath);

                if (file_exists(strFileNearTpl)) {
                    auto r = new Render(strFileNearTpl, this->tree);
                    ioBuffer = r->toBufferTree(context);
                    delete r;
                } else {
                    std::cout << "File not exists? " << strFileNearTpl << std::endl;
                }

                free(strFileNearTpl);
            }

            if (ioBuffer == nullptr && file_exists(strFilePath)) {
                auto r = new Render(strFilePath, this->tree);
                ioBuffer = r->toBufferTree(context);
                delete r;
            }

            if (ioBuffer != nullptr) {
                std::cout << "Merge Buffers: " << std::endl;
                merge_buffers(buffer, ioBuffer, 4096);
            }

            it++; // close control tag
        }
    }
}

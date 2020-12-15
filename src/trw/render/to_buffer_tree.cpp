#include <trw.h>
#include <list>

namespace TemplateRenderWizard
{
    IOBuffer::IOMemoryBuffer* Render::toBufferTree()
    {
        auto buffer = new IOBuffer::IOMemoryBuffer(TRW_RENDER_MEMORY_BLOCK_SIZE);

        auto tokens = new std::list<Token::Token*>;
        auto token = this->getNextToken();

        while (token != nullptr) {
            tokens->push_back(token);
            token = this->getNextToken();
        }

        return buffer;
    }
}

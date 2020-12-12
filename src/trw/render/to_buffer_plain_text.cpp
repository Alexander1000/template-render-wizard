#include <trw.h>

namespace TemplateRenderWizard
{
    void Render::to_buffer_plain_text(IOBuffer::IOBuffer *buffer, Token::Token *token)
    {
        char* tBuffer = (char*) malloc(sizeof(char) * TRW_RENDER_BUFFER_SIZE);
        IOBuffer::IOReader* reader = token->getReader();
        RESET_TOKEN_READER(token);
        int nSizeRead;
        do {
            memset(tBuffer, 0, sizeof(char) * TRW_RENDER_BUFFER_SIZE);
            nSizeRead = reader->read(tBuffer, TRW_RENDER_BUFFER_SIZE);
            buffer->write(tBuffer, nSizeRead);
        } while (nSizeRead == TRW_RENDER_BUFFER_SIZE);
        free(tBuffer);
    }
}

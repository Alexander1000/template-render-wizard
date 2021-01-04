#include <trw.h>
#include <io-buffer.h>
#include <memory.h>

namespace TemplateRenderWizard
{
    void merge_buffers(IOBuffer::IOWriter* writer, IOBuffer::IOReader* reader, int bufferSize)
    {
        char* buffer = (char*) malloc(sizeof(char) * (bufferSize + 1));
        int nRead;

        do {
            memset(buffer, 0, sizeof(char) * (bufferSize + 1));
            nRead = reader->read(buffer, bufferSize);
            writer->write(buffer, nRead);
        } while (nRead == bufferSize);

        free(buffer);
    }
}

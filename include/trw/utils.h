#ifndef H_TRW_UTILS_INCLUDE
#define H_TRW_UTILS_INCLUDE

#include <memory.h>
#include <list>
#include <io-buffer.h>
#include <trw/context.h>

#define RESET_TOKEN_READER(token) \
    do { \
        auto reader = (IOBuffer::IOMemoryBuffer*) token->getReader(); \
        reader->setPosition(0); \
    } while(0);

#define INIT_CHAR_STRING(str, length) \
    char* str = new char[(length)];     \
    memset(str, 0, (length) * sizeof(char));

namespace TemplateRenderWizard
{
    bool ctype_digits(const char*);

    bool is_digit(char str);

    std::list<char*>* explode_string(const char* str, char delimiter);

    bool file_exists(const std::string* name);
    bool file_exists(const char* name);

    void merge_buffers(IOBuffer::IOWriter*, IOBuffer::IOReader*, int);

    void merge_context(Context* dst, Context* src);
}

#endif

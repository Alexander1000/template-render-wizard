#ifndef H_TRW_UTILS_INCLUDE
#define H_TRW_UTILS_INCLUDE

#define RESET_TOKEN_READER(token) \
    do { \
        auto reader = (IOBuffer::IOMemoryBuffer*) token->getReader(); \
        reader->setPosition(0); \
    } while(0);

namespace TemplateRenderWizard
{
    bool ctype_digits(const char*);

    bool is_digit(char str);
}

#endif

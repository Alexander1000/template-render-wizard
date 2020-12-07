#include <trw/utils.h>

namespace TemplateRenderWizard
{
    bool ctype_digits(const char* str)
    {
        bool result = true;
        int i = 0;
        while (str[i] != 0x00) {
            if (!is_digit(str[i])) {
                result = false;
                break;
            }
            i++;
        }
        return result;
    }

    bool is_digit(char str) {
        return str >= '0' && str <= '9';
    }
}

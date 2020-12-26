#include <trw.h>
#include <list>

namespace TemplateRenderWizard
{
    std::list<char*>* explode_string(const char* str, char delimiter)
    {
        auto list = new std::list<char*>;
        int pos = 0;
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == delimiter) {
                if (i > pos) {
                    INIT_CHAR_STRING(tStr, i - pos + 1)
                    memcpy(tStr, str + pos, i - pos);
                    list->push_back(tStr);
                }
                pos = i + 1;
            }
        }
        if (strlen(str) > pos) {
            INIT_CHAR_STRING(tStr, strlen(str) - pos + 1)
            memcpy(tStr, str + pos, strlen(str) - pos);
            list->push_back(tStr);
        }
        return list;
    }
}

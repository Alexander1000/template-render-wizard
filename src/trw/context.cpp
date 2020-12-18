#include <trw.h>

namespace TemplateRenderWizard
{
    Context::Context()
    {
        this->value = nullptr;
    }

    void Context::setValueContext(Value *v) {
        this->value = v;
    }

    Value* Context::getValueContext() {
        return this->value;
    }

    void Context::setValue(const char *path, Value *v) {}

    Value * Context::getValue(const char* path)
    {
        if (this->value == nullptr) {
            return nullptr;
        }

        Value* foundElement = nullptr;
        Value* relativeElement = this->value;

        int nStart = 0, nStop = 0;

        for (int i = 0; i < strlen(path); i++) {
            if (path[i] == '.' || i == strlen(path) - 1) {
                nStop = i;
                if (i == strlen(path) - 1) {
                    nStop++;
                }
                // get leaf name
                INIT_CHAR_STRING(leafName, (nStop - nStart + 1))
                memcpy(leafName, path + nStart, sizeof(char) * (nStop - nStart));

                if (relativeElement->getType() != ValueType::Object) {
                    throw new UnexpectedToken;
                }

                auto rObj = relativeElement->getObject();
                if (rObj->find(leafName) != rObj->end()) {
                    relativeElement = rObj->at(leafName);
                    if (i == strlen(path) - 1) {
                        foundElement = relativeElement;
                    }
                } else {
                    return nullptr;
                }

                free(leafName);

                // for next part
                nStart = i + 1;
            }
        }

        return foundElement;
    }
}

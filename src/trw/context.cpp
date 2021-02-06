#include <trw.h>
#include <map>
#include <string>

namespace TemplateRenderWizard
{
    Context::Context()
    {
        this->value = nullptr;
        this->parent = nullptr;
    }

    Context::Context(Context *ctxParent) {
        this->value = nullptr;
        this->parent = ctxParent;
    }

    void Context::setValueContext(Value *v) {
        this->value = v;
    }

    Value* Context::getValueContext() {
        return this->value;
    }

    void Context::setValue(const char *path, Value *v)
    {
        if (this->value == nullptr) {
            this->value = new Value;
            auto emptyObj = new std::map<std::string, Value*>;
            this->value->setData(emptyObj);
        }

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
                        (*rObj)[leafName] = v;
                    }
                } else {
                    // not found element - insert empty
                    if (i == strlen(path) - 1) {
                        (*rObj)[leafName] = v; // last object
                    } else {
                        auto emptyValue = new Value;
                        auto emptyObj = new std::map<std::string, Value *>;
                        emptyValue->setData(emptyObj);
                        (*rObj)[leafName] = emptyValue;
                        relativeElement = emptyValue;
                    }
                }

                free(leafName);

                // for next part
                nStart = i + 1;
            }
        }
    }

    Value * Context::getValue(const char* path)
    {
        if (this->value == nullptr) {
            if (this->parent != nullptr) {
                return this->parent->getValue(path);
            }
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
                    if (this->parent != nullptr) {
                        return this->parent->getValue(path);
                    }
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

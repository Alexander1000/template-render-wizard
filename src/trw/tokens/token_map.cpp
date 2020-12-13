#include <trw.h>

namespace TemplateRenderWizard::Token
{
    TokenMap::TokenMap() {
        this->tokenMap = new std::map<std::string, Type>;
        (*this->tokenMap)["plainText"] = Type::PlainTextType;
        (*this->tokenMap)["openTagValue"] = Type::OpenTagValueType;
        (*this->tokenMap)["closeTagValue"] = Type::CloseTagValueType;
        (*this->tokenMap)["plainValue"] = Type::PlainValueType;
        (*this->tokenMap)["openControlTag"] = Type::OpenControlTagType;
        (*this->tokenMap)["closeControlTag"] = Type::CloseControlTagType;
        (*this->tokenMap)["roundBracketOpen"] = Type::RoundBracketOpenType;
        (*this->tokenMap)["roundBracketClose"] = Type::RoundBracketCloseType;
        (*this->tokenMap)["exprValue"] = Type::ExpressionValueType;
        (*this->tokenMap)["mathOp"] = Type::MathOperationType;
        (*this->tokenMap)["compare"] = Type::CompareType;
        (*this->tokenMap)["keyword"] = Type::KeywordType;
    }

    Type TokenMap::getType(const char *typeName) {
        if (this->tokenMap->find(typeName) != this->tokenMap->end()) {
            return this->tokenMap->at(typeName);
        }

        throw new UnknownToken;
    }

    const char* TokenMap::getName(Type type) {
        const char* tokenName = nullptr;
        for (auto it = this->tokenMap->begin(); it != this->tokenMap->end(); it++) {
            if (it->second == type) {
                tokenName = it->first.c_str();
                break;
            }
        }

        return tokenName;
    }
}

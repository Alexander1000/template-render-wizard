#include <trw.h>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Token
{
    TokenMap::TokenMap()
    {
        this->tokenMap = new std::map<std::string, int>{
            {"plainText",         Type::PlainTextType},
            {"openTagValue",      Type::OpenTagValueType},
            {"closeTagValue",     Type::CloseTagValueType},
            {"plainValue",        Type::PlainValueType},
            {"openControlTag",    Type::OpenControlTagType},
            {"closeControlTag",   Type::CloseControlTagType},
            {"roundBracketOpen",  Type::RoundBracketOpenType},
            {"roundBracketClose", Type::RoundBracketCloseType},
            {"exprValue",         Type::ExpressionValueType},
            {"mathOp",            Type::MathOperationType},
            {"compare",           Type::CompareType},
            {"keyword",           Type::KeywordType},
            {"comma",             Type::CommaType},
            {"mathOpHigh",        Type::MathOperationHighPriorityType},
            {"filePath",          Type::FilePathType},
            {"doubleDot",         Type::DoubleDotType},
            {"openBrace",         Type::OpenBraceType},
            {"closeBrace",        Type::CloseBraceType},
            {"includeWithKey",    Type::IncludeWithKeyType},
        };
    }
}

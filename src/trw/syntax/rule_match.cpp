#include <trw.h>

namespace TemplateRenderWizard::Syntax
{
    RuleMatch::RuleMatch(const char *ruleName)
    {
        this->value.ruleName = ruleName;
        this->type = RuleMatchType::RuleMatchName;
    }

    RuleMatch::RuleMatch(TemplateRenderWizard::Token::Type tokenType)
    {
        this->value.tokenType = tokenType;
        this->type = RuleMatchType::RuleMatchTokenType;
    }
}

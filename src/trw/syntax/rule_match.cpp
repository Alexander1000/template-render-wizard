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

    RuleMatchType RuleMatch::getType() {
        return this->type;
    }

    TemplateRenderWizard::Token::Type RuleMatch::getTokenType() {
        return this->value.tokenType;
    }

    const char * RuleMatch::getRuleName() {
        return this->value.ruleName;
    }
}

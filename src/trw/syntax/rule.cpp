#include <trw.h>
#include <list>

namespace TemplateRenderWizard::Syntax
{
    Rule::Rule(const char *ruleName)
    {
        this->name = ruleName;
        this->matches = new std::list<RuleMatch*>;
    }

    void Rule::addMatch(RuleMatch *ruleMatch) {
        this->matches->push_back(ruleMatch);
    }

    std::list<RuleMatch*>* Rule::getMatches() {
        return this->matches;
    }

    const char * Rule::getName() {
        return this->name;
    }
}

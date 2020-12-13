#include <trw.h>
#include <list>

namespace TemplateRenderWizard::Syntax
{
    Rule::Rule(const char *ruleName)
    {
        this->name = ruleName;
        this->matches = new std::list<RuleMatch*>;
    }
}

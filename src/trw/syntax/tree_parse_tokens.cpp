#include <trw.h>

namespace TemplateRenderWizard::Syntax
{
    SyntaxElement* Tree::parse(std::list<TemplateRenderWizard::Token::Token*> *tokens)
    {
        auto syntaxElements = new std::list<SyntaxElement*>;
        for (auto it = tokens->begin(); it != tokens->end(); it++) {
            syntaxElements->push_back(new SyntaxElement(*it));
        }
        return nullptr;
    }

    SyntaxElement* Tree::parse(std::list<SyntaxElement*>* elements) {
        int count = 0;
        for (auto it = elements->begin(); it != elements->end(); it++) {
            count++;
        }
        if (count == 1) {
            return *elements->begin();
        }

        for (auto it = this->rules->begin(); it != this->rules->end(); it++) {
            elements = this->run_rule(*it, elements);
        }
        return nullptr;
    }

    std::list<SyntaxElement*>* Tree::run_rule(Rule *rule, std::list<SyntaxElement*> *elements)
    {
        return nullptr;
    }
}

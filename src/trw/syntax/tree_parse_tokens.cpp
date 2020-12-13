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
        return nullptr;
    }
}

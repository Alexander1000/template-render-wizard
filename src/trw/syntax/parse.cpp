#include <trw.h>
#include <syntax-tree-lib.h>
#include <list>

namespace TemplateRenderWizard::Syntax
{
    SyntaxTree::Syntax::SyntaxElement* Tree::beforeParse(std::list<SyntaxTree::Syntax::SyntaxElement *> *elements)
    {
        auto filteredElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;

        for (auto it = elements->begin(); it != elements->end(); it++) {
            auto token = (*it)->getToken();
            auto bracketElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
            int nestedLevel = 0;

            if (token->getType() == TemplateRenderWizard::Token::Type::RoundBracketOpenType) {
                do {
                    it++;
                    if (std::next(it) == elements->end()) {
                        break;
                    }
                    if ((*it)->getToken()->getType() == TemplateRenderWizard::Token::Type::RoundBracketOpenType) {
                        nestedLevel++;
                    }
                    if ((*it)->getToken()->getType() == TemplateRenderWizard::Token::Type::RoundBracketCloseType) {
                        if (nestedLevel > 0) {
                            nestedLevel--;
                        } else {
                            break;
                        }
                    }
                    bracketElements->push_back(*it);
                } while (true);
            }

            filteredElements->push_back(*it);
        }

        return this->parse(filteredElements);
    }
}

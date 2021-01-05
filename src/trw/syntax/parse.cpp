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
                SyntaxTree::Syntax::SyntaxElement* closeBracket = nullptr;
                filteredElements->push_back(*it);

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
                            closeBracket = *it;
                            break;
                        }
                    }
                    bracketElements->push_back(*it);
                } while (true);

                filteredElements->push_back(this->parseBrackets(bracketElements));
                filteredElements->push_back(closeBracket);
                continue;
            }

            filteredElements->push_back(*it);
        }

        return this->parse(filteredElements);
    }

    SyntaxTree::Syntax::SyntaxElement* Tree::parseBrackets(std::list<SyntaxTree::Syntax::SyntaxElement *> *elements)
    {
        if (elements->size() == 1) {
            return *elements->begin();
        }

        int sizeElements;

        for (auto it = this->mathRules->begin(); it != this->mathRules->end(); it++) {
            SyntaxTree::Syntax::Rule *rule = *it;
            do {
                sizeElements = elements->size();
                elements = this->run_single_rule(rule, elements);
            } while (sizeElements != elements->size());
        }

        return this->parseBrackets(elements);
    }
}

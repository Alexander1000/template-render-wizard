#include <trw.h>
#include <syntax-tree-lib.h>
#include <list>

namespace TemplateRenderWizard::Syntax
{
    SyntaxTree::Syntax::SyntaxElement* Tree::beforeParse(std::list<SyntaxTree::Syntax::SyntaxElement*>* elements)
    {
        auto filteredElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
        for (auto it = elements->begin(); it != elements->end(); it++) {
            if (this->isExprToken(*it)) {
                auto exprList = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
                do {
                    exprList->push_back(*it);
                    it++;
                } while (this->isExprToken(*it));
                filteredElements->push_back(this->parseExpr(exprList));
            } else {
                filteredElements->push_back(*it);
            }
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

    std::list<SyntaxTree::Syntax::SyntaxElement*>* Tree::filterBrackets(std::list<SyntaxTree::Syntax::SyntaxElement *> *elements)
    {
        auto filteredElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;

        for (auto it = elements->begin(); it != elements->end(); it++) {
            auto token = (*it)->getToken();
            auto bracketElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
            int nestedLevel = 0;

            if (token->getType() == TemplateRenderWizard::Token::Type::RoundBracketOpenType) {
                SyntaxTree::Syntax::SyntaxElement* closeBracket = nullptr;
                auto newSyntaxElement = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
                newSyntaxElement->push_back(*it);

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

                newSyntaxElement->push_back(this->parseExpr(bracketElements));
                newSyntaxElement->push_back(closeBracket);
                auto sntxElement = new SyntaxTree::Syntax::SyntaxElement(newSyntaxElement);
                sntxElement->setRule(new SyntaxTree::Syntax::Rule("factor"));
                filteredElements->push_back(sntxElement);
                continue;
            }

            filteredElements->push_back(*it);
        }

        return filteredElements;
    }

    std::list<SyntaxTree::Syntax::SyntaxElement*>* Tree::filterMathHigh(std::list<SyntaxTree::Syntax::SyntaxElement*> *elements)
    {
        auto filteredElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;

        SyntaxTree::Syntax::SyntaxElement* prev = nullptr;

        for (auto it = elements->begin(); it != elements->end(); it++) {
            auto element = *it;

            if (element->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                auto token = element->getToken();
                if (token->getType() == TemplateRenderWizard::Token::Type::MathOperationHighPriorityType) {
                    it++;
                    auto rValue = *it;

                    // make syntax element
                    auto listElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
                    listElements->push_back(prev);
                    listElements->push_back(element);
                    listElements->push_back(rValue);

                    filteredElements->pop_back();

                    auto newElement = new SyntaxTree::Syntax::SyntaxElement(listElements);
                    newElement->setRule(new SyntaxTree::Syntax::Rule("term"));
                    filteredElements->push_back(newElement);


                    continue;
                }
            }

            prev = *it;
            filteredElements->push_back(*it);
        }
        return filteredElements;
    }

    bool Tree::isExprToken(SyntaxTree::Syntax::SyntaxElement *element)
    {
        if (element->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
            auto token = element->getToken();
            switch (token->getType()) {
                case TemplateRenderWizard::Token::Type::RoundBracketCloseType:
                case TemplateRenderWizard::Token::Type::RoundBracketOpenType:
                case TemplateRenderWizard::Token::Type::ExpressionValueType:
                case TemplateRenderWizard::Token::Type::MathOperationHighPriorityType:
                case TemplateRenderWizard::Token::Type::MathOperationType: {
                    return true;
                }
                default: {
                    return false;
                }
            }
        }

        return false;
    }

    SyntaxTree::Syntax::SyntaxElement* Tree::parseExpr(std::list<SyntaxTree::Syntax::SyntaxElement*>* elements)
    {
        if (elements->size() == 1) {
            return *elements->begin();
        }
        elements = this->filterBrackets(elements);
        elements = this->filterMathHigh(elements);
        elements = this->filterMathLow(elements);

        return this->parseExpr(elements);
    }

    std::list<SyntaxTree::Syntax::SyntaxElement*>* Tree::filterMathLow(std::list<SyntaxTree::Syntax::SyntaxElement*>* elements)
    {
        auto filteredElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;

        SyntaxTree::Syntax::SyntaxElement* prev = nullptr;

        for (auto it = elements->begin(); it != elements->end(); it++) {
            auto element = *it;

            if (element->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                auto token = element->getToken();
                if (token->getType() == TemplateRenderWizard::Token::Type::MathOperationType) {
                    it++;
                    auto rValue = *it;

                    // make syntax element
                    auto listElements = new std::list<SyntaxTree::Syntax::SyntaxElement*>;
                    listElements->push_back(prev);
                    listElements->push_back(element);
                    listElements->push_back(rValue);

                    filteredElements->pop_back();

                    auto newElement = new SyntaxTree::Syntax::SyntaxElement(listElements);
                    newElement->setRule(new SyntaxTree::Syntax::Rule("term"));
                    filteredElements->push_back(newElement);


                    continue;
                }
            }

            prev = *it;
            filteredElements->push_back(*it);
        }
        return filteredElements;
    }
}

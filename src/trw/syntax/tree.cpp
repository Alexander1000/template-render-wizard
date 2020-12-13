#include <trw.h>
#include <list>

namespace TemplateRenderWizard::Syntax
{
    Tree::Tree() {
        this->rules = new std::list<Rule*>;
        this->tokenMap = new TemplateRenderWizard::Token::TokenMap;
        this->initializeDefaults();
    }

    void Tree::initializeDefaults()
    {
        // do make syntax tree rules

        // s:injectValue [t:openTagValue t:plainValue t:closeTagValue]
        auto rule1 = new Rule("injectValue");
        rule1->addMatch(new RuleMatch(this->tokenMap->getType("openTagValue")));
        rule1->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule1->addMatch(new RuleMatch(this->tokenMap->getType("closeTagValue")));
        this->rules->push_back(rule1);

        // s:expr [t:exprValue]
        auto rule2 = new Rule("expr");
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("exprValue")));
        this->rules->push_back(rule2);

        // s:expr [t:roundBracketOpen s:expr t:roundBracketClose]
        auto rule3 = new Rule("expr");
        rule3->addMatch(new RuleMatch(this->tokenMap->getType("roundBracketOpen")));
        rule3->addMatch(new RuleMatch("expr"));
        rule3->addMatch(new RuleMatch(this->tokenMap->getType("roundBracketClose")));
        this->rules->push_back(rule3);

        // s:expr [t:roundBracketOpen s:expr t:roundBracketClose]
        auto rule4 = new Rule("expr");
        rule4->addMatch(new RuleMatch(this->tokenMap->getType("roundBracketOpen")));
        rule4->addMatch(new RuleMatch("expr"));
        rule4->addMatch(new RuleMatch(this->tokenMap->getType("roundBracketClose")));
        this->rules->push_back(rule4);

        // s:expr [s:expr t:mathOp s:expr]
        // @todo: * / - high priority and + - for low priority
        auto rule5 = new Rule("expr");
        rule5->addMatch(new RuleMatch("expr"));
        rule5->addMatch(new RuleMatch(this->tokenMap->getType("mathOp")));
        rule5->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule5);

//        s:if_control [t:openControlTag t:keyword(if) s:expr t:closeControlTag]
//        s:else_control [t:openControlTag t:keyword(else) t:closeControlTag]
//        s:endif_control [t:openControlTag t:keyword(endif) t:closeControlTag]
//        s:for_control [t:openControlTag t:keyword(for) t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
//        s:for_control [t:openControlTag t:keyword(for) t:plainValue t:dot t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
//        s:endfor_control [t:openControlTag t:keyword(endfor) t:closeControlTag]
//        s:if_stmt [s:if_control s:body s:endif_control]
//        s:if_stmt [s:if_control s:body s:else_control s:body s:endif_control]
//        s:for_stmt [s:for_control s:body s:endfor_control]
//        s:body [t:plainText]
//        s:body [s:injectValue]
//        s:body [s:if_stmt]
//        s:body [s:for_stmt]
//        s:body [s:body s:body]
    }
}

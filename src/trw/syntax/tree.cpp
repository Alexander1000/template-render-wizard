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

        // s:body [t:plainText]
        auto ruleBody1 = new Rule("body");
        ruleBody1->addMatch(new RuleMatch(this->tokenMap->getType("plainText")));
        this->rules->push_back(ruleBody1);

        // s:body [s:injectValue]
        auto ruleBody2 = new Rule("body");
        ruleBody2->addMatch(new RuleMatch("injectValue"));
        this->rules->push_back(ruleBody2);

        // s:body [s:if_stmt]
        auto ruleBody3 = new Rule("body");
        ruleBody3->addMatch(new RuleMatch("if_stmt"));
        this->rules->push_back(ruleBody3);

        // s:body [s:for_stmt]
        auto ruleBody4 = new Rule("body");
        ruleBody4->addMatch(new RuleMatch("for_stmt"));
        this->rules->push_back(ruleBody4);

        // s:body [s:body s:body]
        auto ruleBody5 = new Rule("body");
        ruleBody5->addMatch(new RuleMatch("body"));
        ruleBody5->addMatch(new RuleMatch("body"));
        this->rules->push_back(ruleBody5);
    }
}

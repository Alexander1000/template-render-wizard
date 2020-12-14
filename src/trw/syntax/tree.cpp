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

        // s:if_control [t:openControlTag t:keyword(if) s:expr t:closeControlTag]
        auto ruleIf1 = new Rule("if_control");
        ruleIf1->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        // todo: add condition: "if"
        ruleIf1->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleIf1->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleIf1);

        // s:else_control [t:openControlTag t:keyword(else) t:closeControlTag]
        auto ruleElse = new Rule("else_control");
        ruleElse->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        // todo: add condition: "else"
        ruleElse->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleElse->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleElse);

        // s:endif_control [t:openControlTag t:keyword(endif) t:closeControlTag]
        auto ruleEndif = new Rule("endif_control");
        ruleEndif->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        // todo: add condition: "endif"
        ruleEndif->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleEndif->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleEndif);

        // s:for_control [t:openControlTag t:keyword(for) t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
        auto ruleForControl1 = new Rule("for_control");
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        // todo: add condition: "for"
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        // todo: add condition: "in"
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleForControl1);

        // s:for_control [t:openControlTag t:keyword(for) t:plainValue t:dot t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
        auto ruleForControl2 = new Rule("for_control");
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        // todo: add condition: "for"
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("dot")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        // todo: add condition: "in"
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleForControl2);

//        s:endfor_control [t:openControlTag t:keyword(endfor) t:closeControlTag]
        auto ruleEndFor = new Rule("endfor_control");
        ruleEndFor->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        // todo: add condition: "endfor"
        ruleEndFor->addMatch(new RuleMatch(this->tokenMap->getType("keyword")));
        ruleEndFor->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleEndFor);

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

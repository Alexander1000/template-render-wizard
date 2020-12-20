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

        // s:expr [s:expr t:mathOpHigh s:expr]
        auto rule5 = new Rule("expr");
        rule5->addMatch(new RuleMatch("expr"));
        rule5->addMatch(new RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule5->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule5);

        // s:expr [s:expr t:mathOp s:expr]
        auto rule6 = new Rule("expr");
        rule6->addMatch(new RuleMatch("expr"));
        rule6->addMatch(new RuleMatch(this->tokenMap->getType("mathOp")));
        rule6->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule6);

        // s:cmpBool [t:keyword(and)]
        auto ruleCmpBool1 = new Rule("cmpBool");
        ruleCmpBool1->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "and"));
        this->rules->push_back(ruleCmpBool1);

        // s:cmpBool [t:keyword(or)]
        auto ruleCmpBool2 = new Rule("cmpBool");
        ruleCmpBool2->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "or"));
        this->rules->push_back(ruleCmpBool2);

        // s:cmpExpr [s:expr t:compare s:expr]
        auto ruleCmpExpr1 = new Rule("cmpExpr");
        ruleCmpExpr1->addMatch(new RuleMatch("expr"));
        ruleCmpExpr1->addMatch(new RuleMatch(this->tokenMap->getType("compare")));
        ruleCmpExpr1->addMatch(new RuleMatch("expr"));
        this->rules->push_back(ruleCmpExpr1);

        // s:boolExpr [s:expr s:cmpBool s:expr]
        auto ruleBoolExpr1 = new Rule("boolExpr");
        ruleBoolExpr1->addMatch(new RuleMatch("expr"));
        ruleBoolExpr1->addMatch(new RuleMatch("cmpBool"));
        ruleBoolExpr1->addMatch(new RuleMatch("expr"));
        this->rules->push_back(ruleBoolExpr1);

        // s:boolExpr [s:cmpExpr s:cmpBool s:cmpExpr]
        auto ruleBoolExpr2 = new Rule("boolExpr");
        ruleBoolExpr2->addMatch(new RuleMatch("cmpExpr"));
        ruleBoolExpr2->addMatch(new RuleMatch("cmpBool"));
        ruleBoolExpr2->addMatch(new RuleMatch("cmpExpr"));
        this->rules->push_back(ruleBoolExpr2);

        // s:boolExpr [s:expr s:cmpBool s:cmpExpr]
        auto ruleBoolExpr3 = new Rule("boolExpr");
        ruleBoolExpr3->addMatch(new RuleMatch("expr"));
        ruleBoolExpr3->addMatch(new RuleMatch("cmpBool"));
        ruleBoolExpr3->addMatch(new RuleMatch("cmpExpr"));
        this->rules->push_back(ruleBoolExpr3);

        // s:boolExpr [s:cmpExpr s:cmpBool s:expr]
        auto ruleBoolExpr4 = new Rule("boolExpr");
        ruleBoolExpr4->addMatch(new RuleMatch("cmpExpr"));
        ruleBoolExpr4->addMatch(new RuleMatch("cmpBool"));
        ruleBoolExpr4->addMatch(new RuleMatch("expr"));
        this->rules->push_back(ruleBoolExpr4);

        // s:if_control [t:openControlTag t:keyword(if) s:expr t:closeControlTag]
        auto ruleIf1 = new Rule("if_control");
        ruleIf1->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleIf1->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "if"));
        ruleIf1->addMatch(new RuleMatch("expr"));
        ruleIf1->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleIf1);

        // s:if_control [t:openControlTag t:keyword(if) s:cmpExpr t:closeControlTag]
        auto ruleIf2 = new Rule("if_control");
        ruleIf2->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleIf2->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "if"));
        ruleIf2->addMatch(new RuleMatch("cmpExpr"));
        ruleIf2->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleIf2);

        // s:if_control [t:openControlTag t:keyword(if) s:boolExpr t:closeControlTag]
        auto ruleIf3 = new Rule("if_control");
        ruleIf3->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleIf3->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "if"));
        ruleIf3->addMatch(new RuleMatch("boolExpr"));
        ruleIf3->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleIf3);

        // s:else_control [t:openControlTag t:keyword(else) t:closeControlTag]
        auto ruleElse = new Rule("else_control");
        ruleElse->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleElse->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "else"));
        ruleElse->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleElse);

        // s:endif_control [t:openControlTag t:keyword(endif) t:closeControlTag]
        auto ruleEndif = new Rule("endif_control");
        ruleEndif->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleEndif->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "endif"));
        ruleEndif->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleEndif);

        // s:for_control [t:openControlTag t:keyword(for) t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
        auto ruleForControl1 = new Rule("for_control");
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "for"));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "in"));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl1->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleForControl1);

        // s:for_control [t:openControlTag t:keyword(for) t:plainValue t:comma t:plainValue t:keyword(in) t:plainValue t:closeControlTag]
        auto ruleForControl2 = new Rule("for_control");
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "for"));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("comma")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "in"));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        ruleForControl2->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleForControl2);

        // s:endfor_control [t:openControlTag t:keyword(endfor) t:closeControlTag]
        auto ruleEndFor = new Rule("endfor_control");
        ruleEndFor->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        ruleEndFor->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "endfor"));
        ruleEndFor->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(ruleEndFor);

        // s:if_stmt [s:if_control s:body s:endif_control]
        auto ruleIfStmt1 = new Rule("if_stmt");
        ruleIfStmt1->addMatch(new RuleMatch("if_control"));
        ruleIfStmt1->addMatch(new RuleMatch("body"));
        ruleIfStmt1->addMatch(new RuleMatch("endif_control"));
        this->rules->push_back(ruleIfStmt1);

        // s:if_stmt [s:if_control s:body s:else_control s:body s:endif_control]
        auto ruleIfStmt2 = new Rule("if_stmt");
        ruleIfStmt2->addMatch(new RuleMatch("if_control"));
        ruleIfStmt2->addMatch(new RuleMatch("body"));
        ruleIfStmt2->addMatch(new RuleMatch("else_control"));
        ruleIfStmt2->addMatch(new RuleMatch("body"));
        ruleIfStmt2->addMatch(new RuleMatch("endif_control"));
        this->rules->push_back(ruleIfStmt2);

        // s:for_stmt [s:for_control s:body s:endfor_control]
        auto ruleForStmt = new Rule("for_stmt");
        ruleForStmt->addMatch(new RuleMatch("for_control"));
        ruleForStmt->addMatch(new RuleMatch("body"));
        ruleForStmt->addMatch(new RuleMatch("endfor_control"));
        this->rules->push_back(ruleForStmt);

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

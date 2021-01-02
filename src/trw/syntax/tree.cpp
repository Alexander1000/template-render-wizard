#include <trw.h>
#include <list>
#include <syntax-tree-lib.h>

namespace TemplateRenderWizard::Syntax
{
    Tree::Tree() : SyntaxTree::Syntax::Tree() {
        this->tokenMap = new TemplateRenderWizard::Token::TokenMap;
    }

    void Tree::initializeDefaults()
    {
        // @syntax-tree: start-autogenerate

        auto rule00 = new SyntaxTree::Syntax::Rule("injectValue");
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openTagValue")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeTagValue")));
        this->rules->push_back(rule00);

        auto rule01 = new SyntaxTree::Syntax::Rule("expr");
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("exprValue")));
        this->rules->push_back(rule01);

        auto rule02 = new SyntaxTree::Syntax::Rule("expr");
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("roundBracketOpen")));
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("roundBracketClose")));
        this->rules->push_back(rule02);

        auto rule03 = new SyntaxTree::Syntax::Rule("expr");
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule03);

        auto rule04 = new SyntaxTree::Syntax::Rule("expr");
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOp")));
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule04);

        auto rule05 = new SyntaxTree::Syntax::Rule("cmpBool");
        rule05->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "and"));
        this->rules->push_back(rule05);

        auto rule06 = new SyntaxTree::Syntax::Rule("cmpBool");
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "or"));
        this->rules->push_back(rule06);

        auto rule07 = new SyntaxTree::Syntax::Rule("cmpExpr");
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("compare")));
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule07);

        auto rule08 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule08);

        auto rule09 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule09);

        auto rule10 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule10);

        auto rule11 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule11);

        auto rule12 = new SyntaxTree::Syntax::Rule("expr_control");
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule12);

        auto rule13 = new SyntaxTree::Syntax::Rule("expr_control");
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule13);

        auto rule14 = new SyntaxTree::Syntax::Rule("expr_control");
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule14);

        auto rule15 = new SyntaxTree::Syntax::Rule("if_control");
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule15);

        auto rule16 = new SyntaxTree::Syntax::Rule("if_control");
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule16);

        auto rule17 = new SyntaxTree::Syntax::Rule("if_control");
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule17);

        auto rule18 = new SyntaxTree::Syntax::Rule("else_control");
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "else"));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule18);

        auto rule19 = new SyntaxTree::Syntax::Rule("endif_control");
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "endif"));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule19);

        auto rule20 = new SyntaxTree::Syntax::Rule("for_control");
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule20);

        auto rule21 = new SyntaxTree::Syntax::Rule("for_control");
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule21);

        auto rule22 = new SyntaxTree::Syntax::Rule("endfor_control");
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "endfor"));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule22);

        auto rule23 = new SyntaxTree::Syntax::Rule("if_stmt");
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch("if_control"));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch("endif_control"));
        this->rules->push_back(rule23);

        auto rule24 = new SyntaxTree::Syntax::Rule("if_stmt");
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch("if_control"));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch("else_control"));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch("endif_control"));
        this->rules->push_back(rule24);

        auto rule25 = new SyntaxTree::Syntax::Rule("for_stmt");
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch("for_control"));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch("endfor_control"));
        this->rules->push_back(rule25);

        auto rule26 = new SyntaxTree::Syntax::Rule("body");
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainText")));
        this->rules->push_back(rule26);

        auto rule27 = new SyntaxTree::Syntax::Rule("body");
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch("injectValue"));
        this->rules->push_back(rule27);

        auto rule28 = new SyntaxTree::Syntax::Rule("body");
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch("expr_control"));
        this->rules->push_back(rule28);

        auto rule29 = new SyntaxTree::Syntax::Rule("body");
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("if_stmt"));
        this->rules->push_back(rule29);

        auto rule30 = new SyntaxTree::Syntax::Rule("body");
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch("for_stmt"));
        this->rules->push_back(rule30);

        auto rule31 = new SyntaxTree::Syntax::Rule("body");
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        this->rules->push_back(rule31);

        // @syntax-tree: stop-autogenerate
    }
}

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

        auto rule00 = new SyntaxTree::Syntax::Rule("s:injectValue");
        rule00->addMatch(new RuleMatch(this->tokenMap->getType("openTagValue")));
        rule00->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule00->addMatch(new RuleMatch(this->tokenMap->getType("closeTagValue")));
        this->rules->push_back(rule00);

        auto rule01 = new SyntaxTree::Syntax::Rule("s:expr");
        rule01->addMatch(new RuleMatch(this->tokenMap->getType("exprValue")));
        this->rules->push_back(rule01);

        auto rule02 = new SyntaxTree::Syntax::Rule("s:expr");
        rule02->addMatch(new RuleMatch(this->tokenMap->getType("roundBracketOpen")));
        rule02->addMatch(new RuleMatch("expr"));
        rule02->addMatch(new RuleMatch(this->tokenMap->getType("roundBracketClose")));
        this->rules->push_back(rule02);

        auto rule03 = new SyntaxTree::Syntax::Rule("s:expr");
        rule03->addMatch(new RuleMatch("expr"));
        rule03->addMatch(new RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule03->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule03);

        auto rule04 = new SyntaxTree::Syntax::Rule("s:expr");
        rule04->addMatch(new RuleMatch("expr"));
        rule04->addMatch(new RuleMatch(this->tokenMap->getType("mathOp")));
        rule04->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule04);

        auto rule05 = new SyntaxTree::Syntax::Rule("s:cmpBool");
        rule05->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "and"));
        this->rules->push_back(rule05);

        auto rule06 = new SyntaxTree::Syntax::Rule("s:cmpBool");
        rule06->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "or"));
        this->rules->push_back(rule06);

        auto rule07 = new SyntaxTree::Syntax::Rule("s:cmpExpr");
        rule07->addMatch(new RuleMatch("expr"));
        rule07->addMatch(new RuleMatch(this->tokenMap->getType("compare")));
        rule07->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule07);

        auto rule08 = new SyntaxTree::Syntax::Rule("s:boolExpr");
        rule08->addMatch(new RuleMatch("expr"));
        rule08->addMatch(new RuleMatch("cmpBool"));
        rule08->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule08);

        auto rule09 = new SyntaxTree::Syntax::Rule("s:boolExpr");
        rule09->addMatch(new RuleMatch("cmpExpr"));
        rule09->addMatch(new RuleMatch("cmpBool"));
        rule09->addMatch(new RuleMatch("cmpExpr"));
        this->rules->push_back(rule09);

        auto rule10 = new SyntaxTree::Syntax::Rule("s:boolExpr");
        rule10->addMatch(new RuleMatch("expr"));
        rule10->addMatch(new RuleMatch("cmpBool"));
        rule10->addMatch(new RuleMatch("cmpExpr"));
        this->rules->push_back(rule10);

        auto rule11 = new SyntaxTree::Syntax::Rule("s:boolExpr");
        rule11->addMatch(new RuleMatch("cmpExpr"));
        rule11->addMatch(new RuleMatch("cmpBool"));
        rule11->addMatch(new RuleMatch("expr"));
        this->rules->push_back(rule11);

        auto rule12 = new SyntaxTree::Syntax::Rule("s:expr_control");
        rule12->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule12->addMatch(new RuleMatch("expr"));
        rule12->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule12);

        auto rule13 = new SyntaxTree::Syntax::Rule("s:expr_control");
        rule13->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule13->addMatch(new RuleMatch("cmpExpr"));
        rule13->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule13);

        auto rule14 = new SyntaxTree::Syntax::Rule("s:expr_control");
        rule14->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule14->addMatch(new RuleMatch("boolExpr"));
        rule14->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule14);

        auto rule15 = new SyntaxTree::Syntax::Rule("s:if_control");
        rule15->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule15->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule15->addMatch(new RuleMatch("expr"));
        rule15->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule15);

        auto rule16 = new SyntaxTree::Syntax::Rule("s:if_control");
        rule16->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule16->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule16->addMatch(new RuleMatch("cmpExpr"));
        rule16->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule16);

        auto rule17 = new SyntaxTree::Syntax::Rule("s:if_control");
        rule17->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule17->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule17->addMatch(new RuleMatch("boolExpr"));
        rule17->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule17);

        auto rule18 = new SyntaxTree::Syntax::Rule("s:else_control");
        rule18->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule18->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "else"));
        rule18->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule18);

        auto rule19 = new SyntaxTree::Syntax::Rule("s:endif_control");
        rule19->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule19->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "endif"));
        rule19->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule19);

        auto rule20 = new SyntaxTree::Syntax::Rule("s:for_control");
        rule20->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule20->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule20->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule20->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule20->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule20->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule20);

        auto rule21 = new SyntaxTree::Syntax::Rule("s:for_control");
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("comma")));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("plainValue")));
        rule21->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule21);

        auto rule22 = new SyntaxTree::Syntax::Rule("s:endfor_control");
        rule22->addMatch(new RuleMatch(this->tokenMap->getType("openControlTag")));
        rule22->addMatch(new RuleMatch(this->tokenMap->getType("keyword"), "endfor"));
        rule22->addMatch(new RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule22);

        auto rule23 = new SyntaxTree::Syntax::Rule("s:if_stmt");
        rule23->addMatch(new RuleMatch("if_control"));
        rule23->addMatch(new RuleMatch("body"));
        rule23->addMatch(new RuleMatch("endif_control"));
        this->rules->push_back(rule23);

        auto rule24 = new SyntaxTree::Syntax::Rule("s:if_stmt");
        rule24->addMatch(new RuleMatch("if_control"));
        rule24->addMatch(new RuleMatch("body"));
        rule24->addMatch(new RuleMatch("else_control"));
        rule24->addMatch(new RuleMatch("body"));
        rule24->addMatch(new RuleMatch("endif_control"));
        this->rules->push_back(rule24);

        auto rule25 = new SyntaxTree::Syntax::Rule("s:for_stmt");
        rule25->addMatch(new RuleMatch("for_control"));
        rule25->addMatch(new RuleMatch("body"));
        rule25->addMatch(new RuleMatch("endfor_control"));
        this->rules->push_back(rule25);

        auto rule26 = new SyntaxTree::Syntax::Rule("s:body");
        rule26->addMatch(new RuleMatch(this->tokenMap->getType("plainText")));
        this->rules->push_back(rule26);

        auto rule27 = new SyntaxTree::Syntax::Rule("s:body");
        rule27->addMatch(new RuleMatch("injectValue"));
        this->rules->push_back(rule27);

        auto rule28 = new SyntaxTree::Syntax::Rule("s:body");
        rule28->addMatch(new RuleMatch("expr_control"));
        this->rules->push_back(rule28);

        auto rule29 = new SyntaxTree::Syntax::Rule("s:body");
        rule29->addMatch(new RuleMatch("if_stmt"));
        this->rules->push_back(rule29);

        auto rule30 = new SyntaxTree::Syntax::Rule("s:body");
        rule30->addMatch(new RuleMatch("for_stmt"));
        this->rules->push_back(rule30);

        auto rule31 = new SyntaxTree::Syntax::Rule("s:body");
        rule31->addMatch(new RuleMatch("body"));
        rule31->addMatch(new RuleMatch("body"));
        this->rules->push_back(rule31);

        // @syntax-tree: stop-autogenerate
    }
}

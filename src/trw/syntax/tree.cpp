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
        // build command: syntax-tree -s syntax.s -i src/trw/syntax/tree.cpp
        // @syntax-tree: start-autogenerate

        auto rule00 = new SyntaxTree::Syntax::Rule("injectValue");
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openTagValue")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeTagValue")));
        this->rules->push_back(rule00);

        auto rule01 = new SyntaxTree::Syntax::Rule("expr");
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOp")));
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch("term"));
        this->rules->push_back(rule01);

        auto rule02 = new SyntaxTree::Syntax::Rule("expr");
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOp")));
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule02);

        auto rule03 = new SyntaxTree::Syntax::Rule("expr");
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch("term"));
        this->rules->push_back(rule03);

        auto rule04 = new SyntaxTree::Syntax::Rule("term");
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch("term"));
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch("factor"));
        this->rules->push_back(rule04);

        auto rule05 = new SyntaxTree::Syntax::Rule("term");
        rule05->addMatch(new SyntaxTree::Syntax::RuleMatch("term"));
        rule05->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule05->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule05);

        auto rule06 = new SyntaxTree::Syntax::Rule("term");
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule06);

        auto rule07 = new SyntaxTree::Syntax::Rule("term");
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch("factor"));
        this->rules->push_back(rule07);

        auto rule08 = new SyntaxTree::Syntax::Rule("factor");
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("exprValue")));
        this->rules->push_back(rule08);

        auto rule09 = new SyntaxTree::Syntax::Rule("factor");
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("roundBracketOpen")));
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("roundBracketClose")));
        this->rules->push_back(rule09);

        auto rule10 = new SyntaxTree::Syntax::Rule("cmpBool");
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "and"));
        this->rules->push_back(rule10);

        auto rule11 = new SyntaxTree::Syntax::Rule("cmpBool");
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "or"));
        this->rules->push_back(rule11);

        auto rule12 = new SyntaxTree::Syntax::Rule("cmpExpr");
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("compare")));
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule12);

        auto rule13 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule13);

        auto rule14 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule14);

        auto rule15 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule15);

        auto rule16 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule16);

        auto rule17 = new SyntaxTree::Syntax::Rule("expr_control");
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule17);

        auto rule18 = new SyntaxTree::Syntax::Rule("expr_control");
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule18);

        auto rule19 = new SyntaxTree::Syntax::Rule("expr_control");
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule19);

        auto rule20 = new SyntaxTree::Syntax::Rule("if_control");
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule20);

        auto rule21 = new SyntaxTree::Syntax::Rule("if_control");
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule21);

        auto rule22 = new SyntaxTree::Syntax::Rule("if_control");
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule22);

        auto rule23 = new SyntaxTree::Syntax::Rule("else_control");
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "else"));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule23);

        auto rule24 = new SyntaxTree::Syntax::Rule("endif_control");
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "endif"));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule24);

        auto rule25 = new SyntaxTree::Syntax::Rule("for_control");
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule25);

        auto rule26 = new SyntaxTree::Syntax::Rule("for_control");
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule26);

        auto rule27 = new SyntaxTree::Syntax::Rule("endfor_control");
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "endfor"));
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule27);

        auto rule28 = new SyntaxTree::Syntax::Rule("if_stmt");
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch("if_control"));
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch("endif_control"));
        this->rules->push_back(rule28);

        auto rule29 = new SyntaxTree::Syntax::Rule("if_stmt");
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("if_control"));
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("else_control"));
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("endif_control"));
        this->rules->push_back(rule29);

        auto rule30 = new SyntaxTree::Syntax::Rule("for_stmt");
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch("for_control"));
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch("endfor_control"));
        this->rules->push_back(rule30);

        auto rule31 = new SyntaxTree::Syntax::Rule("include_with_pair");
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("includeWithKey")));
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule31);

        auto rule32 = new SyntaxTree::Syntax::Rule("include_with_pair");
        rule32->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("includeWithKey")));
        rule32->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule32->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule32);

        auto rule33 = new SyntaxTree::Syntax::Rule("include_with_pair");
        rule33->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("includeWithKey")));
        rule33->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule33->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        this->rules->push_back(rule33);

        auto rule34 = new SyntaxTree::Syntax::Rule("include_with_stmt");
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_pair"));
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_pair"));
        this->rules->push_back(rule34);

        auto rule35 = new SyntaxTree::Syntax::Rule("include_with_stmt");
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_pair"));
        this->rules->push_back(rule35);

        auto rule36 = new SyntaxTree::Syntax::Rule("include_with_stmt");
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        this->rules->push_back(rule36);

        auto rule37 = new SyntaxTree::Syntax::Rule("include_stmt");
        rule37->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule37->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "include"));
        rule37->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("filePath")));
        rule37->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule37);

        auto rule38 = new SyntaxTree::Syntax::Rule("include_stmt");
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "include"));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("filePath")));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "with"));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openBrace")));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeBrace")));
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule38);

        auto rule39 = new SyntaxTree::Syntax::Rule("body");
        rule39->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainText")));
        this->rules->push_back(rule39);

        auto rule40 = new SyntaxTree::Syntax::Rule("body");
        rule40->addMatch(new SyntaxTree::Syntax::RuleMatch("injectValue"));
        this->rules->push_back(rule40);

        auto rule41 = new SyntaxTree::Syntax::Rule("body");
        rule41->addMatch(new SyntaxTree::Syntax::RuleMatch("expr_control"));
        this->rules->push_back(rule41);

        auto rule42 = new SyntaxTree::Syntax::Rule("body");
        rule42->addMatch(new SyntaxTree::Syntax::RuleMatch("if_stmt"));
        this->rules->push_back(rule42);

        auto rule43 = new SyntaxTree::Syntax::Rule("body");
        rule43->addMatch(new SyntaxTree::Syntax::RuleMatch("for_stmt"));
        this->rules->push_back(rule43);

        auto rule44 = new SyntaxTree::Syntax::Rule("body");
        rule44->addMatch(new SyntaxTree::Syntax::RuleMatch("include_stmt"));
        this->rules->push_back(rule44);

        auto rule45 = new SyntaxTree::Syntax::Rule("body");
        rule45->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule45->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        this->rules->push_back(rule45);

        // @syntax-tree: stop-autogenerate
    }
}

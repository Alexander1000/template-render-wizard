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
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch("term"));
        this->rules->push_back(rule02);

        auto rule03 = new SyntaxTree::Syntax::Rule("term");
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch("term"));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("mathOpHigh")));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch("factor"));
        this->rules->push_back(rule03);

        auto rule04 = new SyntaxTree::Syntax::Rule("term");
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch("factor"));
        this->rules->push_back(rule04);

        auto rule05 = new SyntaxTree::Syntax::Rule("factor");
        rule05->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("exprValue")));
        this->rules->push_back(rule05);

        auto rule06 = new SyntaxTree::Syntax::Rule("factor");
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("roundBracketOpen")));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("roundBracketClose")));
        this->rules->push_back(rule06);

        auto rule07 = new SyntaxTree::Syntax::Rule("cmpBool");
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "and"));
        this->rules->push_back(rule07);

        auto rule08 = new SyntaxTree::Syntax::Rule("cmpBool");
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "or"));
        this->rules->push_back(rule08);

        auto rule09 = new SyntaxTree::Syntax::Rule("cmpExpr");
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("compare")));
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule09);

        auto rule10 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule10);

        auto rule11 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule11->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule11);

        auto rule12 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule12->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule12);

        auto rule13 = new SyntaxTree::Syntax::Rule("boolExpr");
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpBool"));
        rule13->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule13);

        auto rule14 = new SyntaxTree::Syntax::Rule("expr_control");
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule14->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule14);

        auto rule15 = new SyntaxTree::Syntax::Rule("expr_control");
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule15->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule15);

        auto rule16 = new SyntaxTree::Syntax::Rule("expr_control");
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        rule16->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule16);

        auto rule17 = new SyntaxTree::Syntax::Rule("if_control");
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        rule17->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule17);

        auto rule18 = new SyntaxTree::Syntax::Rule("if_control");
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        rule18->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule18);

        auto rule19 = new SyntaxTree::Syntax::Rule("if_control");
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "if"));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        rule19->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule19);

        auto rule20 = new SyntaxTree::Syntax::Rule("else_control");
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "else"));
        rule20->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule20);

        auto rule21 = new SyntaxTree::Syntax::Rule("endif_control");
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "endif"));
        rule21->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule21);

        auto rule22 = new SyntaxTree::Syntax::Rule("for_control");
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule22->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule22);

        auto rule23 = new SyntaxTree::Syntax::Rule("for_control");
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "for"));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "in"));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainValue")));
        rule23->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule23);

        auto rule24 = new SyntaxTree::Syntax::Rule("endfor_control");
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "endfor"));
        rule24->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule24);

        auto rule25 = new SyntaxTree::Syntax::Rule("if_stmt");
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch("if_control"));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule25->addMatch(new SyntaxTree::Syntax::RuleMatch("endif_control"));
        this->rules->push_back(rule25);

        auto rule26 = new SyntaxTree::Syntax::Rule("if_stmt");
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch("if_control"));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch("else_control"));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule26->addMatch(new SyntaxTree::Syntax::RuleMatch("endif_control"));
        this->rules->push_back(rule26);

        auto rule27 = new SyntaxTree::Syntax::Rule("for_stmt");
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch("for_control"));
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule27->addMatch(new SyntaxTree::Syntax::RuleMatch("endfor_control"));
        this->rules->push_back(rule27);

        auto rule28 = new SyntaxTree::Syntax::Rule("include_with_pair");
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("includeWithKey")));
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule28->addMatch(new SyntaxTree::Syntax::RuleMatch("expr"));
        this->rules->push_back(rule28);

        auto rule29 = new SyntaxTree::Syntax::Rule("include_with_pair");
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("includeWithKey")));
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule29->addMatch(new SyntaxTree::Syntax::RuleMatch("cmpExpr"));
        this->rules->push_back(rule29);

        auto rule30 = new SyntaxTree::Syntax::Rule("include_with_pair");
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("includeWithKey")));
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule30->addMatch(new SyntaxTree::Syntax::RuleMatch("boolExpr"));
        this->rules->push_back(rule30);

        auto rule31 = new SyntaxTree::Syntax::Rule("include_with_stmt");
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_pair"));
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule31->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_pair"));
        this->rules->push_back(rule31);

        auto rule32 = new SyntaxTree::Syntax::Rule("include_with_stmt");
        rule32->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_pair"));
        this->rules->push_back(rule32);

        auto rule33 = new SyntaxTree::Syntax::Rule("include_with_stmt");
        rule33->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        rule33->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("comma")));
        rule33->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        this->rules->push_back(rule33);

        auto rule34 = new SyntaxTree::Syntax::Rule("include_stmt");
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "include"));
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("filePath")));
        rule34->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule34);

        auto rule35 = new SyntaxTree::Syntax::Rule("include_stmt");
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "include"));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("filePath")));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "with"));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openBrace")));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeBrace")));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "only"));
        rule35->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule35);

        auto rule36 = new SyntaxTree::Syntax::Rule("include_stmt");
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openControlTag")));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "include"));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("filePath")));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("keyword"), "with"));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openBrace")));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch("include_with_stmt"));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeBrace")));
        rule36->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeControlTag")));
        this->rules->push_back(rule36);

        auto rule37 = new SyntaxTree::Syntax::Rule("body");
        rule37->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("plainText")));
        this->rules->push_back(rule37);

        auto rule38 = new SyntaxTree::Syntax::Rule("body");
        rule38->addMatch(new SyntaxTree::Syntax::RuleMatch("injectValue"));
        this->rules->push_back(rule38);

        auto rule39 = new SyntaxTree::Syntax::Rule("body");
        rule39->addMatch(new SyntaxTree::Syntax::RuleMatch("expr_control"));
        this->rules->push_back(rule39);

        auto rule40 = new SyntaxTree::Syntax::Rule("body");
        rule40->addMatch(new SyntaxTree::Syntax::RuleMatch("if_stmt"));
        this->rules->push_back(rule40);

        auto rule41 = new SyntaxTree::Syntax::Rule("body");
        rule41->addMatch(new SyntaxTree::Syntax::RuleMatch("for_stmt"));
        this->rules->push_back(rule41);

        auto rule42 = new SyntaxTree::Syntax::Rule("body");
        rule42->addMatch(new SyntaxTree::Syntax::RuleMatch("include_stmt"));
        this->rules->push_back(rule42);

        auto rule43 = new SyntaxTree::Syntax::Rule("body");
        rule43->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        rule43->addMatch(new SyntaxTree::Syntax::RuleMatch("body"));
        this->rules->push_back(rule43);

        // @syntax-tree: stop-autogenerate
    }
}

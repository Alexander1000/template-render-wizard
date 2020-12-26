#ifndef TRW_TESTS_INCLUDE_H
#define TRW_TESTS_INCLUDE_H

#include <string>
#include <cpp-unit-test.h>
#include <dirent.h>
#include <sys/stat.h>
#include <trw.h>

namespace TrwTests
{
    inline bool file_exists(const std::string* name)
    {
        struct stat buffer;
        return (stat(name->c_str(), &buffer) == 0);
    }

    int filter_tpl(const struct dirent* dir_ent);
    int filter_yaml(const struct dirent* dir_ent);

    // asserts
    void assertEquals(CppUnitTest::TestCase* t, TemplateRenderWizard::Token::Type expectedTokenType, TemplateRenderWizard::Token::Type actualTokenType);
    void assertEquals(CppUnitTest::TestCase* t, TemplateRenderWizard::Tree::LeafElementType expectedLeafType, TemplateRenderWizard::Tree::LeafElementType actualLeafType);

    // test cases
    CppUnitTest::TestCase* testParseToken_Template_Positive();
    CppUnitTest::TestCase* testExplodeString_DataForExplode_Positive();
    CppUnitTest::TestCase* testTreeMergeWithEmpty_ValuesFile_Positive();

    // render tests
    void scanTests(CppUnitTest::TestSuite* testSuite);
    CppUnitTest::TestCase* testRenderWithSyntaxTree_Template_Positive(char* templateName, char* valuesFile);
    CppUnitTest::TestCase* testLexer_Template_Positive(char* templateName);
}

#endif

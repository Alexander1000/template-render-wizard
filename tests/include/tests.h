#ifndef TRW_TESTS_INCLUDE_H
#define TRW_TESTS_INCLUDE_H

#include <string>
#include <cpp-unit-test.h>
#include <dirent.h>
#include <sys/stat.h>

namespace TrwTests
{
    inline bool file_exists(const std::string* name)
    {
        struct stat buffer;
        return (stat(name->c_str(), &buffer) == 0);
    }

    int filter_tpl(const struct dirent* dir_ent);
    int filter_yaml(const struct dirent* dir_ent);

    // render tests
    void scanTests(CppUnitTest::TestSuite* testSuite);
    CppUnitTest::TestCase* testRenderWithSyntaxTree_Template_Positive(char* templateName, char* valuesFile);
    CppUnitTest::TestCase* testLexer_Template_Positive(char* templateName);
}

#endif

#ifndef TRW_TESTS_INCLUDE_H
#define TRW_TESTS_INCLUDE_H

#include <cpp-unit-test.h>

namespace TrwTests
{
    CppUnitTest::TestCase* testRenderWithSyntaxTree_Template_Positive(char* templateName, char* valuesFile);
}

#endif

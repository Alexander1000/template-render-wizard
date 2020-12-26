#include <tests.h>
#include <cpp-unit-test.h>

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(TrwTests::testParseToken_Template_Positive());

    testSuite.addTestCase(TrwTests::testTreeMergeWithEmpty_ValuesFile_Positive());

    TrwTests::scanTests(&testSuite);

    testSuite.addTestCase(TrwTests::testExplodeString_DataForExplode_Positive());

    testSuite.addTestCase(TrwTests::testTree_OverrideYamlValues_Positive());

    testSuite.printTotal();

    return 0;
}

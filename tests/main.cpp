#include <cpp-unit-test.h>

CppUnitTest::TestCase* testParseToken_Template_Positive() {
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("001-simple-object");

    t->printTitle();

    t->finish();
    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(testParseToken_Template_Positive());

    testSuite.printTotal();

    return 0;
}

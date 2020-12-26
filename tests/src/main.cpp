#include <tests.h>
#include <trw.h>
#include <io-buffer.h>
#include <cpp-unit-test.h>
#include <memory.h>

CppUnitTest::TestCase* testTreeMergeWithEmpty_ValuesFile_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("002-merge-with-empty-values-file");

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    tree.scan("./fixtures/002-tree-merge-with-empty.yaml");

    TemplateRenderWizard::Tree::LeafElement* leafElement = tree.get("data.foo");
    CppUnitTest::assertNotNull(t, leafElement);

    assertEquals(t, TemplateRenderWizard::Tree::LeafElementType::LeafElementText, leafElement->getType());
    CppUnitTest::assertEquals(t, "bar", (std::string*) leafElement->getData());

    t->finish();
    return t;
}

CppUnitTest::TestCase* testExplodeString_DataForExplode_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("test explode string");

    t->printTitle();

    std::map<std::string, std::list<std::string>> dataSet = {
        {"test.x", {"test", "x"}},
        {"test", {"test"}},
        {"x.test.y", {"x", "test", "y"}},
        {".test", {"test"}},
        {"test.", {"test"}},
        {".test.x", {"test", "x"}},
        {"test.x.", {"test", "x"}},
        {"test..", {"test"}},
        {"..test", {"test"}},
        {"..test..", {"test"}},
        {"x..test..y", {"x", "test", "y"}},
    };

    for (auto it = dataSet.begin(); it != dataSet.end(); it++) {
        auto list = TemplateRenderWizard::explode_string(it->first.c_str(), '.');
        CppUnitTest::assertEquals(t, (int) it->second.size(), (int) list->size());

        auto iExpected = it->second.begin();
        for (auto iKey = list->begin(); iKey != list->end(); iKey++) {
            CppUnitTest::assertEquals(t, 0, strcmp(*iKey, iExpected->c_str()));
            iExpected++;
        }
    }

    t->finish();

    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(TrwTests::testParseToken_Template_Positive());

    testSuite.addTestCase(testTreeMergeWithEmpty_ValuesFile_Positive());

    TrwTests::scanTests(&testSuite);

    testSuite.addTestCase(testExplodeString_DataForExplode_Positive());

    testSuite.printTotal();

    return 0;
}

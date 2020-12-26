#include <tests.h>
#include <trw.h>
#include <cpp-unit-test.h>
#include <string>

namespace TrwTests
{
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

    CppUnitTest::TestCase* testTree_OverrideYamlValues_Positive()
    {
        auto t = new CppUnitTest::TestCase("[tree] - override yaml values");
        t->printTitle();

        t->finish();
        return t;
    }
}

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

        TemplateRenderWizard::Tree::Tree tree;
        tree.scan("./fixtures/003-tree-override-values.yaml");

        tree.setValue("user.name", new std::string("Hell Knight"));
        tree.setValue("place", new std::string("ship"));

        auto render = new TemplateRenderWizard::Render("./fixtures/003-tree-override-values.tpl", &tree);

        IOBuffer::IOMemoryBuffer* buffer = render->toBufferTree(nullptr);

        INIT_CHAR_STRING(tBuffer, 1024);
        buffer->read(tBuffer, 1023);

        CppUnitTest::assertEquals(
            t,
            "Hello Hell Knight!\n"
            "Do you go to the ship today?\n",
            tBuffer
        );

        t->finish();
        return t;
    }

    CppUnitTest::TestCase* testTree_OnlySetValues_Positive()
    {
        auto t = new CppUnitTest::TestCase("[tree] - only setup values");
        t->printTitle();

        TemplateRenderWizard::Tree::Tree tree;

        tree.setValue("user.name", new std::string("Zevs"));
        tree.setValue("place", new std::string("park"));

        auto render = new TemplateRenderWizard::Render("./fixtures/003-tree-override-values.tpl", &tree);

        IOBuffer::IOMemoryBuffer* buffer = render->toBufferTree(nullptr);

        INIT_CHAR_STRING(tBuffer, 1024);
        buffer->read(tBuffer, 1023);

        CppUnitTest::assertEquals(
                t,
                "Hello Zevs!\n"
                "Do you go to the park today?\n",
                tBuffer
        );

        t->finish();
        return t;
    }
}

#include <trw.h>
#include <io-buffer.h>
#include <cpp-unit-test.h>
#include <memory.h>

void assertEquals(CppUnitTest::TestCase* t, TemplateRenderWizard::Token::Type expectedTokenType, TemplateRenderWizard::Token::Type actualTokenType) {
    t->increment();
    if (expectedTokenType != actualTokenType) {
        throw new CppUnitTest::AssertEqualsException;
    }
}

void assertEquals(CppUnitTest::TestCase* t, TemplateRenderWizard::Tree::LeafElementType expectedLeafType, TemplateRenderWizard::Tree::LeafElementType actualLeafType) {
    t->increment();
    if (expectedLeafType != actualLeafType) {
        throw new CppUnitTest::AssertEqualsException;
    }
}

CppUnitTest::TestCase* testParseToken_Template_Positive() {
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("001-simple-text");

    t->printTitle();

    TemplateRenderWizard::Token::Token* token = nullptr;
    char* textBuffer = new char[1000];

    IOBuffer::IOFileReader fileReader("./fixtures/001-simple-text.txt");
    IOBuffer::CharStream charStream(&fileReader);
    TemplateRenderWizard::Stream tokenStream(&charStream);

    token = tokenStream.getNextToken();

    CppUnitTest::assertNotNull(t, token);
    assertEquals(t, TemplateRenderWizard::Token::Type::PlainTextType, token->getType());
    CppUnitTest::assertNotNull(t, token->getReader());
    memset(textBuffer, 0, sizeof(char) * 1000);
    token->getReader()->read(textBuffer, 999);
    CppUnitTest::assertEquals(t, "Hello world!\nMy name is ", textBuffer);

    token = tokenStream.getNextToken();
    CppUnitTest::assertNotNull(t, token);
    assertEquals(t, TemplateRenderWizard::Token::Type::OpenTagValueType, token->getType());

    token = tokenStream.getNextToken();
    CppUnitTest::assertNotNull(t, token);
    assertEquals(t, TemplateRenderWizard::Token::Type::PlainValueType, token->getType());
    CppUnitTest::assertNotNull(t, token->getReader());
    memset(textBuffer, 0, sizeof(char) * 1000);
    token->getReader()->read(textBuffer, 999);
    CppUnitTest::assertEquals(t, "name", textBuffer);

    token = tokenStream.getNextToken();
    CppUnitTest::assertNotNull(t, token);
    assertEquals(t, TemplateRenderWizard::Token::Type::CloseTagValueType, token->getType());

    token = tokenStream.getNextToken();
    CppUnitTest::assertNotNull(t, token);
    assertEquals(t, TemplateRenderWizard::Token::Type::PlainTextType, token->getType());
    CppUnitTest::assertNotNull(t, token->getReader());
    memset(textBuffer, 0, sizeof(char) * 1000);
    token->getReader()->read(textBuffer, 999);
    CppUnitTest::assertEquals(t, "!\n", textBuffer);

    token = tokenStream.getNextToken();
    CppUnitTest::assertNull(t, token);

    delete[] textBuffer;

    t->finish();
    return t;
}

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

CppUnitTest::TestCase* testRender_TemplateAndValues_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("003-template-and-values-file");

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    tree.scan("./fixtures/003-values.yaml");

    TemplateRenderWizard::Render* render;
    render = new TemplateRenderWizard::Render("./fixtures/003-simple-text.txt", &tree);

    IOBuffer::IOMemoryBuffer* buffer = render->toBuffer();

    char* tBuffer = (char*) malloc(sizeof(char) * 1024);
    memset(tBuffer, 0, sizeof(char) * 1024);
    int tSize = buffer->read(tBuffer, 1024);

    CppUnitTest::assertEquals(t, "Hello world!\nMy name is test-data!\n", tBuffer);

    free(tBuffer);

    t->finish();
    return t;
}

CppUnitTest::TestCase* testRender_TemplateWithConditions_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("004-template-with-conditions");

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    tree.scan("./fixtures/004-values.yaml");

    TemplateRenderWizard::Render* render;
    render = new TemplateRenderWizard::Render("./fixtures/004-text-with-condition.tpl", &tree);

    IOBuffer::IOMemoryBuffer* buffer = render->toBuffer();

    char* tBuffer = (char*) malloc(sizeof(char) * 1024);
    memset(tBuffer, 0, sizeof(char) * 1024);
    int tSize = buffer->read(tBuffer, 1024);

    // todo: remove after success debug
    std::cout << "Given text: " << tBuffer << std::endl;

    CppUnitTest::assertEquals(
        t,
        " - Hello Alexander1000!\n"
        " - Can you go to aquapark?\n"
        " - Perfect!\n"
        "(Test text with template and conditions)",
        tBuffer
    );

    t->finish();
    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(testParseToken_Template_Positive());

    testSuite.addTestCase(testTreeMergeWithEmpty_ValuesFile_Positive());

    testSuite.addTestCase(testRender_TemplateAndValues_Positive());

    testSuite.addTestCase(testRender_TemplateWithConditions_Positive());

    testSuite.printTotal();

    return 0;
}

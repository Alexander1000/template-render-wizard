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
    buffer->read(tBuffer, 1024);

    CppUnitTest::assertEquals(
        t,
        " - Hello Alexander1000!\n"
        " - Can you go to aquapark?\n"
        " - Perfect!\n"
        "(Test text with template and conditions)\n",
        tBuffer
    );

    t->finish();
    return t;
}

CppUnitTest::TestCase* testRender_TemplateWithNestedConditionsCase01_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("005-template-with-nested-conditions-test01");

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    tree.scan("./fixtures/005-values-test01.yaml");

    TemplateRenderWizard::Render* render;
    render = new TemplateRenderWizard::Render("./fixtures/005-text-with-nested-conditions.tpl", &tree);

    IOBuffer::IOMemoryBuffer* buffer = render->toBuffer();

    INIT_CHAR_STRING(tBuffer, 1024);
    buffer->read(tBuffer, 1024);

    CppUnitTest::assertEquals(
        t,
        "<html>\n"
        "<head>\n"
        "    <title>dankovtsev.pro[Alexander1000]</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Hello on </h1>\n"
        "    <div>\n"
        "        \n" // if expr
        "            <a href=\"/logout\">Выйти[Alexander1000]</a>\n"
        "        \n" // else
        "    </div>\n"
        "</body>\n"
        "</html>\n",
        tBuffer
    );

    t->finish();
    return t;
}

CppUnitTest::TestCase* testRender_TemplateWithNestedConditionsCase02_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("005-template-with-nested-conditions-test02");

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    tree.scan("./fixtures/005-values-test02.yaml");

    TemplateRenderWizard::Render* render;
    render = new TemplateRenderWizard::Render("./fixtures/005-text-with-nested-conditions.tpl", &tree);

    IOBuffer::IOMemoryBuffer* buffer = render->toBuffer();

    INIT_CHAR_STRING(tBuffer, 1024);
    buffer->read(tBuffer, 1024);

    CppUnitTest::assertEquals(
            t,
            "<html>\n"
            "<head>\n"
            "    <title>dankovtsev.pro</title>\n"
            "</head>\n"
            "<body>\n"
            "    <h1>Hello on </h1>\n"
            "    <div>\n"
            "        \n" // if-else expr
            "            Go to login page: <a href=\"/login\">Login</a>\n"
            "            \n" // if site.redesign
            "                <div>test-content</div>\n"
            "            \n" // endif
            "        \n" // endif
            "    </div>\n"
            "</body>\n"
            "</html>\n",
            tBuffer
    );

    t->finish();
    return t;
}

CppUnitTest::TestCase* testRender_TemplateWithNestedConditionsCase03_Positive()
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("005-template-with-nested-conditions-test03");

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    tree.scan("./fixtures/005-values-test03.yaml");

    TemplateRenderWizard::Render* render;
    render = new TemplateRenderWizard::Render("./fixtures/005-text-with-nested-conditions.tpl", &tree);

    IOBuffer::IOMemoryBuffer* buffer = render->toBuffer();

    INIT_CHAR_STRING(tBuffer, 1024);
    buffer->read(tBuffer, 1024);

    CppUnitTest::assertEquals(
            t,
            "<html>\n"
            "<head>\n"
            "    <title>dankovtsev.pro</title>\n"
            "</head>\n"
            "<body>\n"
            "    <h1>Hello on Alexander1000 home page</h1>\n"
            "    <div>\n"
            "        \n" // if-else expr
            "            Go to login page: <a href=\"/login\">Login</a>\n"
            "            \n" // if site.redesign
            "        \n" // endif
            "    </div>\n"
            "</body>\n"
            "</html>\n",
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

    testSuite.addTestCase(testRender_TemplateWithNestedConditionsCase01_Positive());
    testSuite.addTestCase(testRender_TemplateWithNestedConditionsCase02_Positive());
    testSuite.addTestCase(testRender_TemplateWithNestedConditionsCase03_Positive());

    testSuite.printTotal();

    return 0;
}

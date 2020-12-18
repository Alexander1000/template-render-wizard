#include <trw.h>
#include <io-buffer.h>
#include <cpp-unit-test.h>
#include <memory.h>
#include <dirent.h>

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

CppUnitTest::TestCase* testRenderWithSyntaxTree_Template_Positive(char* templateName, char* valuesFile)
{
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase(valuesFile);

    t->printTitle();

    TemplateRenderWizard::Tree::Tree tree;
    INIT_CHAR_STRING(fileWithValues, 1024)
    sprintf(fileWithValues, "./fixtures/%s", valuesFile);
    tree.scan(fileWithValues);

    TemplateRenderWizard::Render* render;
    INIT_CHAR_STRING(fileWithTemplate, 1024)
    sprintf(fileWithTemplate, "./fixtures/%s", templateName);
    render = new TemplateRenderWizard::Render(fileWithTemplate, &tree);

    IOBuffer::IOMemoryBuffer* buffer = render->toBufferTree();

    int nRead = 0;
    int nBaseSize = 1024;
    int offset = 0;
    INIT_CHAR_STRING(tBuffer, nBaseSize);
    do {
        nRead = buffer->read(tBuffer + offset, 1023);
        if (nRead == 1023) {
            nBaseSize += 1024;
            tBuffer = (char*) realloc(tBuffer, nBaseSize);
            offset += 1023;
        }
    } while(nRead == 1023);

    INIT_CHAR_STRING(expected, 1024)
    INIT_CHAR_STRING(fileExpected, 1024)
    memcpy(fileExpected, valuesFile, sizeof(char) * (strlen(valuesFile) - 5));

    INIT_CHAR_STRING(strFileExpected, 1024)
    sprintf(strFileExpected, "./fixtures/%s.out", fileExpected);

    IOBuffer::IOFileReader* fileReader;
    fileReader = new IOBuffer::IOFileReader(strFileExpected);
    nRead = 0;
    offset = 0;
    nBaseSize = 1024;
    do {
        nRead = fileReader->read(expected + offset, 1023);
        if (nRead == 1023) {
            nBaseSize += 1024;
            expected = (char*) realloc(expected, nBaseSize);
            offset += 1023;
        }
    } while (nRead == 1023);

    CppUnitTest::assertEquals(t, expected, tBuffer);

    t->finish();
    return t;
}

CppUnitTest::TestCase* testLexer_Template_Positive(char* templateName)
{
    CppUnitTest::TestCase* t = nullptr;

    INIT_CHAR_STRING(strTestCaseName, 1024);
    sprintf(strTestCaseName, "[lexer] %s", templateName);

    t = new CppUnitTest::TestCase(strTestCaseName);

    t->printTitle();

    INIT_CHAR_STRING(srcTemplateFile, 1024)
    sprintf(srcTemplateFile, "./fixtures/%s", templateName);

    IOBuffer::IOFileReader* fileReader;
    fileReader = new IOBuffer::IOFileReader(srcTemplateFile);
    IOBuffer::CharStream* charStream;
    charStream = new IOBuffer::CharStream(fileReader);
    auto stream = new TemplateRenderWizard::Stream(charStream);

    INIT_CHAR_STRING(strTokenFile, 1024)
    INIT_CHAR_STRING(strTokenFileName, 1024)
    memcpy(strTokenFileName, templateName, sizeof(char) * (strlen(templateName) - 4));
    sprintf(strTokenFile, "./fixtures/%s.t", strTokenFileName);
    free(strTokenFileName);

    auto tokenFile = new TemplateRenderWizard::TokenFile(strTokenFile);
    TemplateRenderWizard::Token::Type tokenType;
    TemplateRenderWizard::Token::Token* token;

    do {
        tokenType = tokenFile->getNextTokenType();
        token = stream->getNextToken();
        if (token != nullptr) {
            assertEquals(t, tokenType, token->getType());
        }
    } while(tokenType != TemplateRenderWizard::Token::Type::EofType);

    t->finish();
    return t;
}

static int filter_tpl(const struct dirent* dir_ent)
{
    if (!strcmp(dir_ent->d_name, ".") || !strcmp(dir_ent->d_name, "..")) {
        return 0;
    }

    std::string fname = dir_ent->d_name;

    if (fname.find(".tpl") == std::string::npos) {
        return 0;
    }

    return 1;
}

static int filter_yaml(const struct dirent* dir_ent)
{
    if (!strcmp(dir_ent->d_name, ".") || !strcmp(dir_ent->d_name, "..")) {
        return 0;
    }

    std::string fname = dir_ent->d_name;

    if (fname.find(".yaml") == std::string::npos) {
        return 0;
    }

    return 1;
}

void scanTests(CppUnitTest::TestSuite* testSuite) {
    // std::vector<std::string> v;

    struct dirent **namelist;
    struct dirent **yamlList;

    int n = scandir("./fixtures", &namelist, *filter_tpl, alphasort);
    int nValues = scandir("./fixtures", &yamlList, *filter_yaml, alphasort);

    INIT_CHAR_STRING(strTplNum, 5);
    INIT_CHAR_STRING(strYamlNum, 5);

    for (int i = 0; i<n; i++) {
        memset(strTplNum, 0, sizeof(char) * 5);
        memcpy(strTplNum, namelist[i]->d_name, 3 * sizeof(char));
        testSuite->addTestCase(testLexer_Template_Positive(namelist[i]->d_name));

        for (int j = 0; j < nValues; j++) {
            memset(strYamlNum, 0, sizeof(char) * 5);
            memcpy(strYamlNum, yamlList[j]->d_name, 3 * sizeof(char));

            if (strcmp(strTplNum, strYamlNum) == 0) {
                testSuite->addTestCase(testRenderWithSyntaxTree_Template_Positive(namelist[i]->d_name, yamlList[j]->d_name));
            }
        }

        free(namelist[i]);
    }
    free(namelist);
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(testParseToken_Template_Positive());

    testSuite.addTestCase(testTreeMergeWithEmpty_ValuesFile_Positive());

    scanTests(&testSuite);

    testSuite.printTotal();

    return 0;
}

#include <tests.h>
#include <trw.h>
#include <io-buffer.h>
#include <cpp-unit-test.h>
#include <memory.h>
#include <dirent.h>
#include <sys/stat.h>

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

inline bool file_exists(const std::string* name)
{
    struct stat buffer;
    return (stat(name->c_str(), &buffer) == 0);
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

CppUnitTest::TestCase* testLexer_Template_Positive(char* templateName)
{
    CppUnitTest::TestCase* t = nullptr;

    INIT_CHAR_STRING(strTestCaseName, 1024);
    sprintf(strTestCaseName, "[lexer] %s", templateName);

    t = new CppUnitTest::TestCase(strTestCaseName);

    t->printTitle();

    INIT_CHAR_STRING(srcTemplateFile, 1024)
    sprintf(srcTemplateFile, "./fixtures/%s", templateName);

    CppUnitTest::assertTrue(t, file_exists(new std::string(srcTemplateFile)));

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

    CppUnitTest::assertTrue(t, file_exists(new std::string(strTokenFile)));

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

void scanTests(CppUnitTest::TestSuite* testSuite)
{
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
                testSuite->addTestCase(TrwTests::testRenderWithSyntaxTree_Template_Positive(namelist[i]->d_name, yamlList[j]->d_name));
            }
        }

        free(namelist[i]);
    }
    free(namelist);
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

    testSuite.addTestCase(testParseToken_Template_Positive());

    testSuite.addTestCase(testTreeMergeWithEmpty_ValuesFile_Positive());

    scanTests(&testSuite);

    testSuite.addTestCase(testExplodeString_DataForExplode_Positive());

    testSuite.printTotal();

    return 0;
}

#include <tests.h>
#include <trw.h>
#include <cpp-unit-test.h>
#include <dirent.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TrwTests
{
    CppUnitTest::TestCase* testRenderWithSyntaxTree_Template_Positive(char* templateName, char* valuesFile)
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase(valuesFile);

        t->printTitle();

        TemplateRenderWizard::Tree::Tree tree;
        INIT_CHAR_STRING(fileWithValues, 1024)
        sprintf(fileWithValues, "./fixtures/render-tests/%s", valuesFile);
        tree.scan(fileWithValues);

        TemplateRenderWizard::Render* render;
        INIT_CHAR_STRING(fileWithTemplate, 1024)
        sprintf(fileWithTemplate, "./fixtures/render-tests/%s", templateName);
        render = new TemplateRenderWizard::Render(fileWithTemplate, &tree);

        IOBuffer::IOMemoryBuffer* buffer = render->toBufferTree(nullptr);

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
        sprintf(strFileExpected, "./fixtures/render-tests/%s.out", fileExpected);

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

        std::cout << tBuffer << std::endl;

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
        sprintf(srcTemplateFile, "./fixtures/render-tests/%s", templateName);

        CppUnitTest::assertTrue(t, file_exists(new std::string(srcTemplateFile)));

        IOBuffer::IOFileReader* fileReader;
        fileReader = new IOBuffer::IOFileReader(srcTemplateFile);
        IOBuffer::CharStream* charStream;
        charStream = new IOBuffer::CharStream(fileReader);
        auto stream = new TemplateRenderWizard::Lexer::Lexer(charStream);

        INIT_CHAR_STRING(strTokenFile, 1024)
        INIT_CHAR_STRING(strTokenFileName, 1024)
        memcpy(strTokenFileName, templateName, sizeof(char) * (strlen(templateName) - 4));
        sprintf(strTokenFile, "./fixtures/render-tests/%s.t", strTokenFileName);
        free(strTokenFileName);

        CppUnitTest::assertTrue(t, file_exists(new std::string(strTokenFile)));

        auto tokenFile = new TemplateRenderWizard::TokenFile(strTokenFile);
        int tokenType;
        SyntaxTree::Token::Token* token;

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

    void scanTests(CppUnitTest::TestSuite* testSuite)
    {
        struct dirent **namelist;
        struct dirent **yamlList;

        int n = scandir("./fixtures/render-tests", &namelist, *filter_tpl, alphasort);
        int nValues = scandir("./fixtures/render-tests", &yamlList, *filter_yaml, alphasort);

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
}

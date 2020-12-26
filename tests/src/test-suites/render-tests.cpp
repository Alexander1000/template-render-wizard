#include <tests.h>
#include <trw.h>
#include <cpp-unit-test.h>

namespace TrwTests
{
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
}

#include <trw.h>
#include <io-buffer.h>
#include <cpp-unit-test.h>

void assertEquals(CppUnitTest::TestCase* t, TemplateRenderWizard::Token::Type expectedTokenType, TemplateRenderWizard::Token::Type actualTokenType) {
    t->increment();
    if (expectedTokenType != actualTokenType) {
        throw new CppUnitTest::AssertEqualsException;
    }
}

CppUnitTest::TestCase* testParseToken_Template_Positive() {
    CppUnitTest::TestCase* t = nullptr;
    t = new CppUnitTest::TestCase("001-simple-text");

    t->printTitle();

    IOBuffer::IOReader* reader = nullptr;
    TemplateRenderWizard::Token::Token* token = nullptr;
    char* textBuffer = new char[1000];

    IOBuffer::IOFileReader fileReader("./fixtures/001-simple-text.txt");
    IOBuffer::CharStream charStream(&fileReader);
    TemplateRenderWizard::Stream tokenStream(&charStream);

    token = tokenStream.getNextToken();

    CppUnitTest::assertNotNull(t, token);
    assertEquals(t, TemplateRenderWizard::Token::Type::PlainTextType, token->getType());
    reader = token->getReader();
    CppUnitTest::assertNotNull(t, reader);
    memset(textBuffer, 0, sizeof(char) * 1000);
    reader->read(textBuffer, 999);
    CppUnitTest::assertEquals(t, "Hello world!\nMy name is ", textBuffer);

    delete[] textBuffer;

    t->finish();
    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(testParseToken_Template_Positive());

    testSuite.printTotal();

    return 0;
}

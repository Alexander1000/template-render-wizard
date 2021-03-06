#include <tests.h>
#include <cpp-unit-test.h>
#include <trw.h>
#include <io-buffer.h>
#include <syntax-tree-lib.h>

namespace TrwTests
{
    CppUnitTest::TestCase* testParseToken_Template_Positive()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("001-simple-text");

        t->printTitle();

        SyntaxTree::Token::Token* token = nullptr;
        char* textBuffer = new char[1000];

        IOBuffer::IOFileReader fileReader("./fixtures/001-simple-text.txt");
        IOBuffer::CharStream charStream(&fileReader);
        TemplateRenderWizard::Lexer::Lexer tokenStream(&charStream);

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
}

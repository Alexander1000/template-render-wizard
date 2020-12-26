#include <tests.h>
#include <trw.h>
#include <cpp-unit-test.h>

namespace TrwTests
{
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
}

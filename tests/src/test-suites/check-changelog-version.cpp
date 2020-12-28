#include <tests.h>
#include <cpp-unit-test.h>
#include <io-buffer.h>

namespace TrwTests
{
    CppUnitTest::TestCase* testChangeLogVersion_CurrentVersion_Positive()
    {
        auto t = new CppUnitTest::TestCase("changelog assert");
        t->printTitle();

        IOBuffer::IOFileReader fileReader("./CHANGELOG.md");
        IOBuffer::CharStream charStream(&fileReader);

        char* curSymbol = nullptr;

        do {
            curSymbol = charStream.getNext();
            if (curSymbol != nullptr && *curSymbol == '#') {
                curSymbol = charStream.getNext();
                if (curSymbol != nullptr && *curSymbol == '#') {
                    curSymbol = charStream.getNext();
                    if (curSymbol != nullptr && *curSymbol == '#') {
                        curSymbol = charStream.getNext();
                        break;
                    }
                }
            }
        } while (curSymbol != nullptr);

        CppUnitTest::assertNotNull(t, curSymbol);

        if (*curSymbol == 0x20) {
            // skip spaces
            do {
                curSymbol = charStream.getNext();
            } while(curSymbol != nullptr && *curSymbol == 0x20);
        }

        CppUnitTest::assertNotNull(t, curSymbol);

        IOBuffer::IOMemoryBuffer buffer(8);
        do {
            if (curSymbol != nullptr && ((*curSymbol >= '0' && *curSymbol <= '9') || *curSymbol == '.')) {
                buffer.write(curSymbol, 1);
            } else {
                break;
            }
            curSymbol = charStream.getNext();
        } while (curSymbol != nullptr);

        INIT_CHAR_STRING(actualVersion, 8);
        buffer.read(actualVersion, 7);

        CppUnitTest::assertEquals(t, TRW_VERSION, actualVersion);

        t->finish();
        return t;
    }
}

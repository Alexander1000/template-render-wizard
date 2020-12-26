#include <tests.h>
#include <cpp-unit-test.h>
#include <trw.h>
#include <list>
#include <map>

namespace TrwTests
{
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
}

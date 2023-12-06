#include <cassert>
#include "EarlyParser.h"

struct Test {
    void test1() {
        std::vector<Rule> rules = {{"S", "A"},
                                   {"A", "aB"},
                                   {"B", "b"}};
        EarlyParser early;
        early.fit(rules, "S");
        assert(early.predict("ab") == true);
        assert(early.predict("aba") == false);
        assert(early.predict("abba") == false);
    }

    void test2() {
        std::vector<Rule> rules = {{"S", "aA"},
                                   {"A", "aB"},
                                   {"B", "b"},
                                   {"A", "b"}};
        EarlyParser early;
        early.fit(rules, "S");
        assert(early.predict("aab") == true);
        assert(early.predict("abb") == false);
        assert(early.predict("aba") == false);
    }

    void test3() {
        std::vector<Rule> rules = {{"S", "aA"},
                                   {"S", "aB"},
                                   {"B", "b"},
                                   {"A", "b"}};
        EarlyParser early;
        early.fit(rules, "S");
        assert(early.predict("ab") == true);
        assert(early.predict("aba") == false);
    }

    void test4() {
        std::vector<Rule> rules = {{"S", "aFbF"},
                                   {"F", "aFb"},
                                   {"F", ""}};
        EarlyParser early;
        early.fit(rules, "S");
        assert(early.predict("aabb") == true);
        assert(early.predict("aba") == false);
    }

    void test5() {
        std::vector<Rule> rules = {{"S", "aSbS"},
                                   {"S", "bSaS"},
                                   {"S", ""}};
        EarlyParser early;
        early.fit(rules, "S");
        assert(early.predict("abb") == false);
        assert(early.predict("abab") == true);
    }

    void test6() {
        std::vector<Rule> rules = {{"S", "aB"},
                                   {"A", "a"},
                                   {"A", "Ba"},
                                   {"B", "ABC"},
                                   {"B", "b"},
                                   {"C", "BA"},
                                   {"C", "c"}};
        EarlyParser early;
        early.fit(rules, "S");
        assert(early.predict("ababba") == true);
        assert(early.predict("abababbaba") == true);
        assert(early.predict("abababba") == false);
    }

    void RunAllTests() {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
    }
};
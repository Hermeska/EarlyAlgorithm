#include "gtest/gtest.h"
#include "Grammar.h"
#include "EarleyParser.h"

TEST(earley_test, basic_no_epsilon_1) {
    Grammar gr;
    Symbol s1(nonTerminal);
    gr.setInitial(s1);
    Symbol s2(isTerminal);

    gr.addRule(s1, {s2});
    gr.addRule(s1, {s1, s1});
    EarleyParser parser;
    parser.init(gr);
    std::vector<Symbol> vec;
    for (int i = 0; i < 20; i++) {
        vec.push_back(s2);
        Word word(vec);
        EXPECT_TRUE(parser.parse(word));
    }
    Symbol trash(isTerminal);
    Word word({trash});
    EXPECT_FALSE(parser.parse(word));
}

TEST(earley_test, basic_with_epsilon_1) {
    Grammar gr;
    Symbol S(nonTerminal); // S
    gr.setInitial(S);
    Symbol left(isTerminal); // (
    Symbol right(isTerminal); // )
    Symbol eps(epsilon);

    gr.addRule(S, {S, S});
    gr.addRule(S, {left, S, right});
    gr.addRule(S, {eps});
    EarleyParser parser;
    parser.init(gr);

    Word correct1({left, right});
    Word correct2({left, right, left, left, right, right});
    EXPECT_TRUE(parser.parse(correct1));
    EXPECT_TRUE(parser.parse(correct2));

    Word wrong({left});
    EXPECT_FALSE(parser.parse(wrong));

    std::vector<Symbol> vec;
    for (int i = 0; i < 20; i++) {
        vec.push_back(left);
        vec.push_back(right);
    }
    Word correct3(vec);
    EXPECT_TRUE(parser.parse(correct3));

    vec.push_back(right);
    vec.push_back(left);
    Word wrong2(vec);
    EXPECT_FALSE(parser.parse(wrong2));
}
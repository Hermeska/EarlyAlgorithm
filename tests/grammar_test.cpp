#include "gtest/gtest.h"
#include "Grammar.h"
#include "InputPolicy.h"
#include <fstream>

TEST(symbol_test, basic) {
    Symbol sym1(isTerminal);
    Symbol sym2(nonTerminal);
    EXPECT_EQ(sym1.getId(), 0);
    EXPECT_EQ(sym2.getId(), 1);
    EXPECT_EQ(sym1.getType(), isTerminal);
    EXPECT_EQ(sym2.getType(), nonTerminal);
}

TEST(representation, basic) {
    Symbol sym1(isTerminal);
    Symbol sym2(nonTerminal);
    GrammarRepresentation gr;
    gr.addRepresentation(sym1, "ab");
    gr.addRepresentation(sym2, "cd");
    Symbol sym = gr.getIdByRepresentation("cd");
    EXPECT_TRUE(sym == sym2);
    EXPECT_EQ(gr.getRepresentation(sym1), "ab");
    EXPECT_TRUE(gr.existsRepresentation("ab"));
    EXPECT_TRUE(gr.existsRepresentation("cd"));
    EXPECT_FALSE(gr.existsRepresentation("abc"));

    gr.clear();
    EXPECT_FALSE(gr.existsRepresentation("ab"));
    EXPECT_FALSE(gr.existsRepresentation("cd"));
}

TEST(gramar_test, construct) {
    Symbol s(nonTerminal);
    Grammar gr(s);
    EXPECT_TRUE(gr.getInitial() == s);
}

TEST(word_test, basic) {
    Word word;
    Symbol c(isTerminal);
    word.push_back(c);

    EXPECT_EQ(word.length(), 1);
    EXPECT_EQ(word[0], c);

    word.clear();
    EXPECT_EQ(word.length(), 0);

    const Word c_word({c});
    EXPECT_EQ(c_word[0], c);
}

TEST(input_policy_test, basic) {
    std::ifstream in("../tests/input_tests/test1");
    assert(in.is_open());
    Grammar grammar;
    GrammarRepresentation repr;
    BNFInputPolicy bnf;
    bnf.input(grammar, repr, in);
    EXPECT_TRUE(repr.existsRepresentation("blabla"));
    EXPECT_TRUE(repr.existsRepresentation("name"));
    EXPECT_TRUE(repr.existsRepresentation("var"));
    EXPECT_TRUE(repr.getRepresentation(grammar.getInitial()) == "blabla");
}

TEST(input_policy_test, opsilon_exists) {
    std::ifstream in("../tests/input_tests/test2");
    assert(in.is_open());
    Grammar grammar;
    GrammarRepresentation repr;
    BNFInputPolicy bnf;
    bnf.input(grammar, repr, in);
    EXPECT_TRUE(repr.existsRepresentation(""));
    Symbol s = repr.getIdByRepresentation("");
    ASSERT_EQ(s.getType(), epsilon);
}

TEST(input_policy_test, several_lines) {
    std::ifstream in("../tests/input_tests/test3");
    assert(in.is_open());
    Grammar grammar;
    GrammarRepresentation repr;
    BNFInputPolicy bnf;
    bnf.input(grammar, repr, in);
    EXPECT_TRUE(repr.existsRepresentation("xxx"));
    EXPECT_TRUE(repr.existsRepresentation("a"));
    EXPECT_TRUE(repr.existsRepresentation("b"));
    EXPECT_TRUE(repr.existsRepresentation("c"));
    EXPECT_FALSE(repr.existsRepresentation("d"));
    Symbol s = repr.getIdByRepresentation("xxx");
    EXPECT_EQ(s.getType(), nonTerminal);
    s = repr.getIdByRepresentation("c");
    EXPECT_EQ(s.getType(), isTerminal);
}

TEST(input_policy_test, word_input){
    std::ifstream in("../tests/input_tests/word_input");
    assert(in.is_open());
    BNFInputPolicy bnf;
    GrammarRepresentation repr;
    Word word;
    bnf.getWord(word, repr, in);

    EXPECT_EQ(word.length(), 3);

    EXPECT_TRUE(word[1]==word[2]);

    EXPECT_FALSE(word[1] == word[0]);

    EXPECT_TRUE(word[0].getType()==isTerminal);
}
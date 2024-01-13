#pragma once

#include "Grammar.h"
#include "ParserAlgo.h"
struct State {
    Rule rule;
    size_t dotPosition;
    size_t parentCnt;

    State(const Rule& rule, size_t d, size_t p) : rule(rule), dotPosition(d), parentCnt(p) {};

    bool operator==(const State& other) const;
};
class EarleyParser : Parser {
private:
    Grammar grammar;

    std::vector<std::vector<State>> D;

    void scan(size_t, const Word&);

    bool addState(size_t pos, State& state);

    bool complete(size_t j, size_t&);

    bool predict(size_t j, size_t&);

    bool find_rule(size_t length, const State&) const;

public:
    EarleyParser() = default;

    ~EarleyParser() = default;

    void init(Grammar& grammar) override;

    bool parse(const Word& word) override;

    bool checkWordValidity(const Word& word);
};
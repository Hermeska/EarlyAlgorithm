#pragma once

#include "Grammar.h"

class Parser {
public:
    Parser() = default;

    virtual void init(Grammar& grammar) = 0;

    virtual bool parse(const Word& word) = 0;
};
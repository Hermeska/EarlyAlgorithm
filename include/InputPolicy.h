#pragma once

#include "Grammar.h"

struct inputPolicy {
    virtual void input(Grammar&, GrammarRepresentation&, std::istream&) = 0;
};

struct BNFInputPolicy :inputPolicy {
    Symbol receiveId(GrammarRepresentation&, const std::string&, SymbolType);

    void input(Grammar&, GrammarRepresentation&, std::istream&) override;

    void getWord(Word&, GrammarRepresentation&, std::istream&);
};
#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>

enum SymbolType {
    isTerminal,
    nonTerminal,
    epsilon,
};

class Symbol {
private:
    SymbolType symbol_type;
    static inline size_t counter = 0;
    size_t id;
public:
    explicit Symbol(SymbolType);

    ~Symbol() = default;

    Symbol(const Symbol &other) = default;

    size_t getId() const;

    SymbolType getType() const;
};

bool operator<(Symbol l, Symbol r);

bool operator==(Symbol l, Symbol r);

bool operator!=(Symbol l, Symbol r);

struct Rule {
    Symbol from;
    std::vector <Symbol> to;
};

bool operator==(const Rule &l, const Rule &r);

class Grammar {
private:
    std::set <Symbol> symbols;
    std::map <Symbol, std::vector<Rule>> rules;
    Symbol initial = Symbol(nonTerminal);
public:
    Grammar() = default;

    explicit Grammar(Symbol initial);

    ~Grammar() = default;

    void clear();

    void addRule(Symbol from, const std::vector <Symbol> &);

    void setInitial(Symbol);

    Symbol getInitial();

    std::vector <Rule> getRules(Symbol id);

    std::set <Symbol> getSymbols() const;

    bool existsRule(Symbol id) const;
};

class Word {
private:
    std::vector <Symbol> letters;

public:
    size_t length() const;

    Symbol &operator[](size_t pos);

    Symbol operator[](size_t pos) const;

    explicit Word(const std::vector <Symbol> &letters);

    Word() = default;

    void clear();

    void push_back(const Symbol &);
};

class GrammarRepresentation {
private:
    std::map <Symbol, std::string> repr_by_id;
    std::map <std::string, Symbol> id_by_repr;
public:
    void addRepresentation(Symbol id, const std::string &repr);

    std::string getRepresentation(Symbol);

    Symbol getIdByRepresentation(const std::string &);

    bool existsRepresentation(const std::string &);

    void clear();
};

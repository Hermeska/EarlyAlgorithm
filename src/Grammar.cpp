#include "Grammar.h"

bool operator<(Symbol l, Symbol r) {
    return l.getId() < r.getId();
}

bool operator==(Symbol l, Symbol r) {
    return l.getId() == r.getId() && l.getType() == r.getType();
}

bool operator!=(Symbol l, Symbol r) {
    return l.getId() != r.getId() || l.getType() != r.getType();
}

Symbol::Symbol(SymbolType type) : id(counter++), symbol_type(type) {}

size_t Symbol::getId() const {
    return id;
}

SymbolType Symbol::getType() const {
    return symbol_type;
}

Grammar::Grammar(Symbol initial) : initial(initial) {}

void Grammar::clear() {
    symbols.clear();
    rules.clear();
}

void Grammar::addRule(Symbol from, const std::vector<Symbol>& rule) {
    if (from.getType() != nonTerminal) {
        throw std::logic_error("Unable to create rule from terminal");
    }
    symbols.insert(from);
    for (const auto& el: rule) {
        symbols.insert(el);
    }
    rules[from].push_back({from, rule});
}

void Grammar::setInitial(Symbol symb) {
    initial = symb;
}

Symbol Grammar::getInitial() {
    return initial;
}

std::vector<Rule> Grammar::getRules(Symbol id) {
    return rules[id];
}

bool Grammar::existsRule(Symbol id) const {
    return rules.find(id) != rules.end();
}

std::set<Symbol> Grammar::getSymbols() const {
    return symbols;
}

void GrammarRepresentation::addRepresentation(Symbol id, const std::string& repr) {
    repr_by_id.emplace(id, repr);
    id_by_repr.emplace(repr, id);
}

std::string GrammarRepresentation::getRepresentation(Symbol id) {
    return repr_by_id[id];
}

void GrammarRepresentation::clear() {
    repr_by_id.clear();
    id_by_repr.clear();
}

bool GrammarRepresentation::existsRepresentation(const std::string& s) {
    return id_by_repr.find(s) != id_by_repr.end();
}

Symbol GrammarRepresentation::getIdByRepresentation(const std::string& str) {
    return id_by_repr.at(str);
}

Word::Word(const std::vector<Symbol>& letters) : letters(letters) {}

size_t Word::length() const {
    return letters.size();
}

Symbol& Word::operator[](size_t pos) {
    return letters[pos];
}

Symbol Word::operator[](size_t pos) const {
    return letters[pos];
}

void Word::clear() {
    letters.clear();
}

void Word::push_back(const Symbol& symbol) {
    letters.push_back(symbol);
};
bool operator==(const Rule& l, const Rule& r) {
    return l.from == r.from && l.to == r.to;
}

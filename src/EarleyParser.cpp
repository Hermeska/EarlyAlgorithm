#include "EarleyParser.h"

void EarleyParser::init(Grammar& gr) {
    grammar.clear();
    Symbol S(nonTerminal);
    grammar.addRule(S, {gr.getInitial()});
    grammar.setInitial(S);
    for (const auto& symb: gr.getSymbols()) {
        if (!gr.existsRule(symb)) {
            continue;
        }
        for (const auto& rule: gr.getRules(symb)) {
            Rule rule_to_add = rule;
            if (rule.to.size() == 1 && rule.to[0].getType() == epsilon) {
                rule_to_add.to.clear();
            }
            grammar.addRule(rule_to_add.from, rule_to_add.to);
        }
    }
}

bool EarleyParser::parse(const Word& word) {
    if (!checkWordValidity(word)) {
        throw std::logic_error("Word consists not only of terminals");
    }
    D.clear();
    D.resize(word.length() + 1);
    Rule initialRule = grammar.getRules(grammar.getInitial())[0];
    D[0].emplace_back(initialRule, 0, 0);

    for (size_t j = 0; j <= word.length(); j++) {
        scan(j, word);
        bool changed = true;
        size_t prev_complete = 0;
        size_t prev_predict = 0; //last visited situationS
        while (changed) {
            bool res1 = complete(j, prev_complete);
            bool res2 = predict(j, prev_predict);
            changed &= (res1 || res2);
        }

    }
    State initialState(initialRule, 1, 0);
    if (find_rule(word.length(), initialState)) {
        return true;
    } else {
        return false;
    }
}

void EarleyParser::scan(size_t pos, const Word& word) {
    if (pos == 0) {
        return;
    }
    for (State& state: D[pos - 1]) {
        if (state.dotPosition >= state.rule.to.size()) {
            continue;
        }
        Symbol next_to_read = state.rule.to[state.dotPosition];
        if (word[pos - 1] == next_to_read) {
            State copy = state;
            copy.dotPosition++;
            addState(pos, copy);
        }
    }
}

bool EarleyParser::checkWordValidity(const Word& word) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (word[i].getType() != isTerminal) {
            return false;
        }
    }
    return true;
}

bool EarleyParser::addState(size_t pos, EarleyParser::State& state) {
    for (const State& st: D[pos]) {
        if (st == state) {
            return false;
        }
    }
    D[pos].push_back(state);
    return true;
}

bool EarleyParser::complete(size_t pos, size_t& prev) {
    if (pos == 0) {
        return false;
    }
    bool changed = false;
    for (size_t& i = prev; i < D[pos].size(); ++i) { //Do not use range-base loop because of possible reallocation
        State st = D[pos][i];
        if (st.dotPosition < st.rule.to.size()) {
            continue;
        }
        for (const State& possible_target: D[st.parentCnt]) {
            if (possible_target.dotPosition >= possible_target.rule.to.size()) {
                continue;
            }
            Symbol next_symb = possible_target.rule.to[possible_target.dotPosition];
            if (next_symb != st.rule.from) {
                continue;
            }
            State state_to_add = possible_target;
            state_to_add.dotPosition++;
            changed |= addState(pos, state_to_add);
        }
    }
    return changed;
}

bool EarleyParser::predict(size_t pos, size_t& prev) {
    bool changed = false;
    for (size_t& i = prev; i < D[pos].size(); ++i) { //Do not use range-base loop because of possible reallocation
        State st = D[pos][i];
        if (st.dotPosition >= st.rule.to.size()) {
            continue;
        }
        Symbol next_symb = st.rule.to[st.dotPosition];
        if (next_symb.getType() != nonTerminal) {
            continue;
        }
        for (const Rule& rule: grammar.getRules(next_symb)) {
            State state_to_add(rule, 0, pos);
            changed |= addState(pos, state_to_add);
        }
    }
    return changed;
}

bool EarleyParser::find_rule(size_t pos, const State& target) const {
    for (const auto& rule: D[pos]) {
        if (rule == target) {
            return true;
        }
    }
    return false;
}

bool EarleyParser::State::operator==(const EarleyParser::State& other) const {
    return rule == other.rule && dotPosition == other.dotPosition && parentCnt == other.parentCnt;
}

#include "InputPolicy.h"

void
BNFInputPolicy::input(Grammar &grammar, GrammarRepresentation &grammarRepresentation, std::istream &in = std::cin) {
    grammar.clear();
    grammarRepresentation.clear();
    std::string initial_string;
    std::getline(in, initial_string);
    grammar.setInitial(receiveId(grammarRepresentation, initial_string, nonTerminal));
    while (in.peek() != EOF) {
        std::string first_line;
        std::string start;
        std::string tmp;
        std::vector <Symbol> rule;
        std::getline(in, first_line);
        if (first_line.empty()) {
            continue;
        }
        auto it = first_line.begin();
        while (it != first_line.end() && *it != '<') {
            ++it;
        }
        if (it == first_line.end()) {
            throw std::logic_error("Invalid line. No first terminal.");
        }
        ++it;
        while (*it != '>') {
            start += *it;
            ++it;
        }
        while (*it != '<' && *it != '"') {
            ++it;
        }
        Symbol start_id = receiveId(grammarRepresentation, start, SymbolType(nonTerminal));
        while (it != first_line.end()) {
            if (*it == '|') {
                grammar.addRule(start_id, rule);
                rule.clear();
                tmp.clear();
                ++it;
                continue;
            }
            if (*it == '<') {
                ++it;
                while (*it != '>') {
                    tmp += *it;
                    ++it;
                }
                Symbol id = receiveId(grammarRepresentation, tmp, SymbolType(nonTerminal));
                rule.push_back(id);
                tmp.clear();
            }
            if (*it == '"') {
                ++it;
                while (*it != '"') {
                    tmp += *it;
                    ++it;
                }
                if (!tmp.empty()) {
                    Symbol id = receiveId(grammarRepresentation, tmp, SymbolType(isTerminal));
                    rule.push_back(id);
                } else {
                    Symbol id = receiveId(grammarRepresentation, tmp, SymbolType(epsilon));
                    rule.push_back(id);
                }
                tmp.clear();
            }
            ++it;
        }
    }
}

Symbol
BNFInputPolicy::receiveId(GrammarRepresentation &grammarRepresentation, const std::string &str,
                          SymbolType type) {
    if (grammarRepresentation.existsRepresentation(str)) {
        return grammarRepresentation.getIdByRepresentation(str);
    }
    Symbol symb(type);
    grammarRepresentation.addRepresentation(symb, str);
    return symb;
}

void BNFInputPolicy::getWord(Word &word, GrammarRepresentation &grammarRepresentation,
                             std::istream &in = std::cin) {
    std::string str, tmp;
    getline(in, str);

    auto it = str.begin();
    while (it != str.end()) {
        if (*it == '"') {
            ++it;
            while (*it != '"') {
                tmp += *it;
                ++it;
            }
            Symbol id = receiveId(grammarRepresentation, tmp, SymbolType(isTerminal));
            word.push_back(id);
            tmp.clear();
        }
        ++it;
    }
}

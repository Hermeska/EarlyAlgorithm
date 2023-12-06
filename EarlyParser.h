#include <iostream>
#include <unordered_set>
#include <vector>


struct Rule {
    std::string left_part;
    std::string right_part;
};

struct Situation {
    std::string left_part;
    std::string right_part;
    int num_parent;
    int position_of_coursoure;

    bool operator==(const Situation &other) const {
        return left_part == other.left_part &&
               right_part == other.right_part &&
               position_of_coursoure == other.position_of_coursoure &&
               num_parent == other.num_parent;
    }
};

namespace std {
    template<>
    struct hash<Situation> {
        size_t operator()(const Situation &s) const {
            return hash<std::string>()(s.left_part) ^
                   hash<std::string>()(s.right_part) ^
                   hash<int>()(s.position_of_coursoure) ^
                   hash<int>()(s.num_parent);
        }
    };
}

class EarlyParser {
private:
    std::vector<Rule> grammar_;
    std::string word_;
    Situation START_;
    Situation FINISH_;
    std::vector<std::unordered_set<Situation>> list_situations_;
public:
    EarlyParser() {}

    void fit(const std::vector<Rule> &grammar, const std::string &start_nonterminal) {
        this->grammar_ = grammar;
        START_ = {"#", start_nonterminal, 0, 0};
        FINISH_ = {"#", start_nonterminal, 1, 0};
        this->grammar_.push_back({"#", start_nonterminal});
    }

    bool predict(const std::string &word) {
        this->word_ = word;
        this->list_situations_ = std::vector<std::unordered_set<Situation>>(word.length() + 1,
                                                                            std::unordered_set<Situation>{});

        // Manually set START_ in the first set if necessary
        if (!this->list_situations_.empty()) {
            this->list_situations_[0].insert(START_);
        }

        for (size_t i = 0; i <= word.length(); ++i) {
            scan(i, list_situations_);
            size_t changed = 0;
            do {
                changed = list_situations_[i].size();
                predict(i, list_situations_);
                complete(i, list_situations_);
            } while (changed != list_situations_[i].size());
        }

        return list_situations_.back().count(FINISH_) > 0;
    }

private:
    void scan(int index, std::vector<std::unordered_set<Situation>> &situations) {
        if (index > 0) {
            for (const auto &item: situations[index - 1]) {
                if (item.position_of_coursoure < item.right_part.length() &&
                    item.right_part[item.position_of_coursoure] == word_[index - 1]) {
                    Situation new_situation = {item.left_part, item.right_part, item.position_of_coursoure + 1,
                                               item.num_parent};
                    situations[index].insert(new_situation);
                }
            }
        }
    }

    void predict(int index, std::vector<std::unordered_set<Situation>> &situations) {
        std::unordered_set<Situation> new_situations;
        for (const auto &item: situations[index]) {
            if (item.position_of_coursoure == item.right_part.length()) {
                continue;
            }

            char expecting_left = item.right_part[item.position_of_coursoure];
            for (const auto &rule: grammar_) {
                if (rule.left_part[0] == expecting_left) {
                    Situation new_situation = {rule.left_part, rule.right_part, 0, static_cast<int>(index)};
                    new_situations.insert(new_situation);
                }
            }
        }

        situations[index].insert(new_situations.begin(), new_situations.end());
    }

    void complete(int index, std::vector<std::unordered_set<Situation>> &situachiya) {
        std::unordered_set<Situation> new_situachiya;
        for (const auto &compItem: situachiya[index]) {
            if (compItem.position_of_coursoure < compItem.right_part.length()) {
                continue;
            }

            for (const auto &nextItem: situachiya[compItem.num_parent]) {
                if (nextItem.position_of_coursoure < nextItem.right_part.length() &&
                    nextItem.right_part[nextItem.position_of_coursoure] == compItem.left_part[0]) {
                    Situation transitives = {nextItem.left_part, nextItem.right_part,
                                             nextItem.position_of_coursoure + 1,
                                             nextItem.num_parent};
                    new_situachiya.insert(transitives);
                }
            }
        }

        situachiya[index].insert(new_situachiya.begin(), new_situachiya.end());
    }
};

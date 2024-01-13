#include <iostream>
#include <fstream>
#include "Grammar.h"
#include "InputPolicy.h"
#include "EarleyParser.h"
#include "ParserAlgo.h"
#include <cassert>

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    assert(in.is_open());
    Grammar grammar;
    GrammarRepresentation repr;
    BNFInputPolicy bnf;
    bnf.input(grammar, repr, in);

    EarleyParser parser;
    parser.init(grammar);

    Word word;
    while (true) {
        bnf.getWord(word, repr, std::cin);
        if (parser.parse(word)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}

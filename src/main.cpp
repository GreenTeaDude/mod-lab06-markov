// Copyright 2026 GreenTea

#include <fstream>
#include <iostream>
#include <string>

#include "../include/textgen.h"

const int kNpref = 2;
const int kMaxgen = 1200;
const char kNonword[] = "\n";

int main() {
    std::ifstream input("input.txt");

    if (!input) {
        std::cout << "Error: cannot open input.txt" << std::endl;
        return 1;
    }

    std::ofstream output("result/gen.txt");

    if (!output) {
        std::cout << "Error: cannot open result/gen.txt" << std::endl;
        return 1;
    }

    StateTab statetab;
    Prefix prefix;

    for (int i = 0; i < kNpref; i++) {
        prefix.push_back(kNonword);
    }

    build(statetab, prefix, input);
    generate(statetab, kMaxgen, output);

    input.close();
    output.close();

    std::cout << "Text generated in result/gen.txt" << std::endl;

    return 0;
}

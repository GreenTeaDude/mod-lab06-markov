// Copyright 2026 GreenTea

#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../include/textgen.h"

const int kNpref = 2;
const char kNonword[] = "\n";

void add(StateTab& statetab, Prefix& prefix, const std::string& suffix) {
    statetab[prefix].push_back(suffix);

    prefix.pop_front();
    prefix.push_back(suffix);
}

void build(StateTab& statetab, Prefix& prefix, std::istream& in) {
    std::string word;

    while (in >> word) {
        add(statetab, prefix, word);
    }

    add(statetab, prefix, kNonword);
}

void generate(StateTab& statetab, int maxWords, std::ostream& out) {
    Prefix prefix;

    for (int i = 0; i < kNpref; i++) {
        prefix.push_back(kNonword);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < maxWords; i++) {
        std::vector<std::string>& suffixes = statetab[prefix];

        if (suffixes.empty()) {
            break;
        }

        std::uniform_int_distribution<> dist(
            0,
            static_cast<int>(suffixes.size()) - 1);

        std::string nextWord = suffixes[dist(gen)];

        if (nextWord == kNonword) {
            break;
        }

        out << nextWord << " ";

        prefix.pop_front();
        prefix.push_back(nextWord);
    }
}

std::string prefixToString(const Prefix& prefix) {
    std::stringstream ss;

    for (Prefix::const_iterator it = prefix.begin();
         it != prefix.end();
         ++it) {
        ss << *it << " ";
    }

    return ss.str();
}

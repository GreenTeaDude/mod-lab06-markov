#include "../include/textgen.h"

#include <iostream>
#include <sstream>
#include <random>

const int NPREF = 2;
const std::string NONWORD = "\n";

void add(StateTab& statetab, Prefix& prefix, const std::string& suffix)
{
    statetab[prefix].push_back(suffix);

    prefix.pop_front();
    prefix.push_back(suffix);
}

void build(StateTab& statetab, Prefix& prefix, std::istream& in)
{
    std::string word;

    while (in >> word)
    {
        add(statetab, prefix, word);
    }

    add(statetab, prefix, NONWORD);
}

void generate(StateTab& statetab, int maxWords, std::ostream& out)
{
    Prefix prefix;

    for (int i = 0; i < NPREF; i++)
    {
        prefix.push_back(NONWORD);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < maxWords; i++)
    {
        std::vector<std::string>& suffixes = statetab[prefix];

        if (suffixes.empty())
        {
            break;
        }

        std::uniform_int_distribution<> dist(0, suffixes.size() - 1);
        std::string nextWord = suffixes[dist(gen)];

        if (nextWord == NONWORD)
        {
            break;
        }

        out << nextWord << " ";

        prefix.pop_front();
        prefix.push_back(nextWord);
    }
}

std::string prefixToString(const Prefix& prefix)
{
    std::stringstream ss;

    for (const std::string& word : prefix)
    {
        ss << word << " ";
    }

    return ss.str();
}

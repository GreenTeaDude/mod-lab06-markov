#pragma once

#include <string>
#include <vector>
#include <deque>
#include <map>

typedef std::deque<std::string> Prefix;
typedef std::map<Prefix, std::vector<std::string>> StateTab;

void add(StateTab& statetab, Prefix& prefix, const std::string& suffix);
void build(StateTab& statetab, Prefix& prefix, std::istream& in);
void generate(StateTab& statetab, int maxWords, std::ostream& out);

std::string prefixToString(const Prefix& prefix);

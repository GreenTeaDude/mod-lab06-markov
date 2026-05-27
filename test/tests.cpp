// Copyright 2026 GreenTea

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "../include/textgen.h"

const char kNonwordTest[] = "\n";

TEST(PrefixTest, PrefixSize) {
    Prefix prefix;

    prefix.push_back("one");
    prefix.push_back("two");

    ASSERT_EQ(prefix.size(), 2);
}

TEST(PrefixTest, PrefixFrontAndBack) {
    Prefix prefix;

    prefix.push_back("first");
    prefix.push_back("second");

    ASSERT_EQ(prefix.front(), "first");
    ASSERT_EQ(prefix.back(), "second");
}

TEST(AddTest, AddCreatesRecord) {
    StateTab table;
    Prefix prefix;

    prefix.push_back("one");
    prefix.push_back("two");

    add(table, prefix, "three");

    Prefix key;
    key.push_back("one");
    key.push_back("two");

    ASSERT_EQ(table[key].size(), 1);
    ASSERT_EQ(table[key][0], "three");
}

TEST(AddTest, PrefixShift) {
    StateTab table;
    Prefix prefix;

    prefix.push_back("one");
    prefix.push_back("two");

    add(table, prefix, "three");

    ASSERT_EQ(prefix.front(), "two");
    ASSERT_EQ(prefix.back(), "three");
}

TEST(AddTest, AddSeveralSuffixesForSamePrefix) {
    StateTab table;
    Prefix prefix;

    prefix.push_back("one");
    prefix.push_back("two");
    add(table, prefix, "three");

    prefix.clear();
    prefix.push_back("one");
    prefix.push_back("two");
    add(table, prefix, "four");

    Prefix key;
    key.push_back("one");
    key.push_back("two");

    ASSERT_EQ(table[key].size(), 2);
    ASSERT_EQ(table[key][0], "three");
    ASSERT_EQ(table[key][1], "four");
}

TEST(BuildTest, BuildTable) {
    StateTab table;
    Prefix prefix;

    prefix.push_back(kNonwordTest);
    prefix.push_back(kNonwordTest);

    std::stringstream input("hello world hello");

    build(table, prefix, input);

    ASSERT_FALSE(table.empty());
}

TEST(BuildTest, BuildAddsFirstWordForStartPrefix) {
    StateTab table;
    Prefix prefix;

    prefix.push_back(kNonwordTest);
    prefix.push_back(kNonwordTest);

    std::stringstream input("hello world");

    build(table, prefix, input);

    Prefix key;
    key.push_back(kNonwordTest);
    key.push_back(kNonwordTest);

    ASSERT_EQ(table[key].size(), 1);
    ASSERT_EQ(table[key][0], "hello");
}

TEST(BuildTest, BuildAddsSecondWord) {
    StateTab table;
    Prefix prefix;

    prefix.push_back(kNonwordTest);
    prefix.push_back(kNonwordTest);

    std::stringstream input("hello world");

    build(table, prefix, input);

    Prefix key;
    key.push_back(kNonwordTest);
    key.push_back("hello");

    ASSERT_EQ(table[key].size(), 1);
    ASSERT_EQ(table[key][0], "world");
}

TEST(BuildTest, BuildAddsEndMarker) {
    StateTab table;
    Prefix prefix;

    prefix.push_back(kNonwordTest);
    prefix.push_back(kNonwordTest);

    std::stringstream input("hello");

    build(table, prefix, input);

    Prefix key;
    key.push_back(kNonwordTest);
    key.push_back("hello");

    ASSERT_EQ(table[key].size(), 1);
    ASSERT_EQ(table[key][0], kNonwordTest);
}

TEST(GenerateTest, GenerateText) {
    StateTab table;
    Prefix prefix;

    prefix.push_back(kNonwordTest);
    prefix.push_back(kNonwordTest);

    std::stringstream input("hello world hello world");
    std::stringstream output;

    build(table, prefix, input);
    generate(table, 10, output);

    ASSERT_FALSE(output.str().empty());
}

TEST(GenerateTest, GenerateNotMoreThanMaxWords) {
    StateTab table;
    Prefix prefix;

    prefix.push_back(kNonwordTest);
    prefix.push_back(kNonwordTest);

    std::stringstream input("one two three four five six");
    std::stringstream output;

    build(table, prefix, input);
    generate(table, 3, output);

    std::stringstream result(output.str());
    std::string word;
    int count = 0;

    while (result >> word) {
        count++;
    }

    ASSERT_LE(count, 3);
}

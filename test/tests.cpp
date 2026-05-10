// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include "../include/textgen.h"

#include <sstream>

const std::string NONWORD_TEST = "\n";

TEST(PrefixTest, PrefixSize)
{
    Prefix prefix;

    prefix.push_back("one");
    prefix.push_back("two");

    ASSERT_EQ(prefix.size(), 2);
}

TEST(AddTest, AddCreatesRecord)
{
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

TEST(AddTest, PrefixShift)
{
    StateTab table;
    Prefix prefix;

    prefix.push_back("one");
    prefix.push_back("two");

    add(table, prefix, "three");

    ASSERT_EQ(prefix.front(), "two");
    ASSERT_EQ(prefix.back(), "three");
}

TEST(BuildTest, BuildTable)
{
    StateTab table;
    Prefix prefix;

    prefix.push_back(NONWORD_TEST);
    prefix.push_back(NONWORD_TEST);

    std::stringstream input("hello world hello");

    build(table, prefix, input);

    ASSERT_FALSE(table.empty());
}

TEST(GenerateTest, GenerateText)
{
    StateTab table;
    Prefix prefix;

    prefix.push_back(NONWORD_TEST);
    prefix.push_back(NONWORD_TEST);

    std::stringstream input("hello world hello world");
    std::stringstream output;

    build(table, prefix, input);
    generate(table, 10, output);

    ASSERT_FALSE(output.str().empty());
}

// File Name: newTests.cpp
//
// Author: Andrew Daly
// Date: 04/22/2020
// Assignment Number: 5
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program contains test functions created by me

#include "newTests.h"
#include "StringList.h"
#include <iostream>

using namespace std;

bool testConcatenate3() {
    StringList list(vector<string>{"I", "love", "Mountain Dew!"});
    return list.concatenate(" *breathe heavily* ") == "I *breathe heavily* love *breathe heavily* Mountain Dew!";
}

bool testConcatenate4() {
    StringList list(vector<string>{"I love doritos!"});
    return list.concatenate("I love doritos!") == "I love doritos!";
}

bool testToString3() {
    StringList list(vector<string>{"I", "love", "Mountain", "Dew", "so", "much", "!"});
    return list.toString() == "I\nlove\nMountain\nDew\nso\nmuch\n!";
}

bool testToString4() {
    StringList list(vector<string>{ "I love doritos so much too!" });
    return list.concatenate("I love doritos so much too!") == "I love doritos so much too!";
}

bool testCopyConstructor3() {
    StringList list1(vector<string>{"still", "the", "same"});
    StringList list2 = list1;
    return list1 == list2;
}

bool testCopyConstructor4() {
    StringList list1(vector<string>{"still", "the", "same", "even", "with", "gibberish", "at", "the", "end"});
    StringList list2 = list1;
    list1.pushBack("asdfasdfgadasfa");
    return list1 == StringList(vector<string>{"still", "the", "same", "even", "with", "gibberish", "at", "the", "end", "asdfasdfgadasfa"}) &&
        StringList(vector<string>{"still", "the", "same", "even", "with", "gibberish", "at", "the", "end"}) == list2;
}

bool testPopFront3() {
    StringList list(vector<string>{"I", "love", "Mountain Dew!"});

    list.popFront();
    return list == StringList(vector<string>{"love", "Mountain Dew!"});
}

bool testPopFront4() {
    StringList list(vector<string>{"I love anime girls!"});

    list.popFront();
    return list == StringList();
}

bool testPushFront3() {
    StringList list(vector<string>{"I", "love", "Mountain Dew!"});

    list.pushFront("Hey!");
    return list == StringList(vector<string>{"Hey!", "I", "love", "Mountain Dew!" });
}

bool testPushFront4() {
    StringList list(vector<string>{});

    list.pushFront("first!");
    return list == StringList(vector<string>{ "first!" });
}

bool testFront3() {
    StringList list(vector<string>{ "1", "2", "3" });

    return list.front() == "1";
}

bool testFront4() {
    StringList list(vector<string>{ "Mountain Dew", "or", "water" });

    return list.front() == "Mountain Dew";
}

bool testReverse3() {
    StringList list(vector<string>{"k", "a", "y", "a", "k"});
    list.reverse();
    return list == StringList(vector<string>{ "k", "a", "y", "a", "k" });
}

bool testReverse4() {
    StringList list(vector<string>{ "me", "loves", "Mountain Dew" });
    list.reverse();
    return list == StringList(vector<string>{ "Mountain Dew", "loves", "me" });
}

bool testInsert3() {
    StringList list(vector<string>{"Dew"});
    bool success = list.insert("Mountain", 0);
    return success && list == StringList(vector<string>{"Mountain", "Dew"});
}

bool testInsert4() {
    StringList list(vector<string>{"0", "1", "2", "3", "4"});
    bool success = list.insert("5", 5);
    return success && list == StringList(vector<string>{"0", "1", "2", "3", "4", "5"});
}

bool testRemove3() {
    StringList list(vector<string>{"v0", "v1", "v2", "v3", "v4"});
    bool success = list.remove(3);
    return success && list == StringList(vector<string>{"v0", "v1", "v2", "v4"});
}

bool testRemove4() {
    StringList list(vector<string>{"v0", "v1"});
    bool success = list.remove(1);
    return success && list == StringList(vector<string>{"v0"});
}

bool testOperatorPlus3() {
    StringList list1(vector<string>{"some", "random", "values"});
    StringList list2(vector<string>{"Something", "else"});
    StringList list = list1 + list2;
    return list == StringList(vector<string>{"some", "random", "values", "Something", "else"});
}

bool testOperatorPlus4() {
    StringList list1;
    StringList list2(vector<string>{"Something", "else"});
    StringList list = list1 + list2;
    return list == StringList(vector<string>{"Something", "else"});
}
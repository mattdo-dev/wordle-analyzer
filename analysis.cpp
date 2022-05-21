//
// Created by Matt Do on 5/20/2022.
//

#include <iostream>
#include "analysis.h"

Analysis::Analysis() {
    for (char c : ALPHABET) {
        first.insert(std::pair<char, int>(c, 0));
        second = first;
        third = first;
        fourth = first;
        fifth = first;
    }
}


void Analysis::enter(std::string word) {
    first.insert(std::pair<char, int>(word.at(0), 1 + first.at(word.at(0))));
    second.insert(std::pair<char, int>(word.at(1), second.at(word.at(1)) + 1));
    third.insert(std::pair<char, int>(word.at(2), third.at(word.at(2)) + 1));
    fourth.insert(std::pair<char, int>(word.at(3), fourth.at(word.at(3)) + 1));
    fifth.insert(std::pair<char, int>(word.at(4), fifth.at(word.at(4)) + 1));
}

void Analysis::data() {
    for (const auto& val : first) {
        std::cout << val.first << ": " << val.second << " / ";
    }
}
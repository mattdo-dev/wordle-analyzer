//
// Created by Matt Do on 5/20/2022.
//

#include <iostream>
#include <iomanip>
#include <thread>
#include "analysis.h"

Analysis::Analysis() {
    for (char c : ALPHABET) {
        first.insert(std::pair<const char, int>(c, 0));
        second = first;
        third = first;
        fourth = first;
        fifth = first;
    }
}


void Analysis::enter(std::string word) {
    first[word.at(0)]++;
    second[word.at(1)]++;
    third[word.at(2)]++;
    fourth[word.at(3)]++;
    fifth[word.at(4)]++;
}

void Analysis::display() {
    int count = 0;
    for (auto const& x : this->first) {
        count = count + x.second;
    }

    auto two = [this] {

    };

    std::thread th_two(two);


    for (auto const& x : first) {
        std::cout << x.first << ": " << std::setprecision(4) << (double) x.second / count * 100 << "%; \n";
    }
}
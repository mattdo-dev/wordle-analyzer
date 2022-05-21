//
// Created by Matt Do on 5/20/2022.
//

#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H


#include <map>

class Analysis {
    const std::string ALPHABET = {"abcdefghijklmnopqrstuvwxyz"};

    std::map<char, int> first;
    std::map<char, int> second;
    std::map<char, int> third;
    std::map<char, int> fourth;
    std::map<char, int> fifth;

public:
    Analysis();
    void enter(std::string str);
    void data();
};


#endif //UNTITLED_ANALYSIS_H

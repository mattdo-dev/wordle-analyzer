//
// Created by Matt Do on 5/20/2022.
//

#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H


#include <map>

class Analysis {
    const std::string ALPHABET = {"abcdefghijklmnopqrstuvwxyz"};
    int lines = 0;

    std::map<const char, int> first;
    std::map<const char, int> second;
    std::map<const char, int> third;
    std::map<const char, int> fourth;
    std::map<const char, int> fifth;

public:
    Analysis();
    void enter(std::string str);
    void display();

private:
    float* assign_weight(const std::map<const char, int>& map);
};


#endif //UNTITLED_ANALYSIS_H

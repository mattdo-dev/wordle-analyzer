#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H


#include <map>
#include <vector>

class Analysis {
private:
    const std::string ALPHABET = {"abcdefghijklmnopqrstuvwxyz"};
    std::vector<std::string> words;
    unsigned int lines;

    //TODO: work on assigning calculated weights to each word...

    std::map<const char, int> first;
    std::map<const char, int> second;
    std::map<const char, int> third;
    std::map<const char, int> fourth;
    std::map<const char, int> fifth;

public:
    Analysis();
    void enter(std::string str);
    void create_weights();

private:
    float *assign_weight(const std::map<const char, int> &map) const;
};


#endif //UNTITLED_ANALYSIS_H

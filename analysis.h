#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H


#include <map>
#include <vector>

class Analysis {
private:
    const std::string ALPHABET = {"abcdefghijklmnopqrstuvwxyz"};

    std::vector<std::string> words;
    unsigned int lines;

    std::map<const char, int> first;
    std::map<const char, int> second;
    std::map<const char, int> third;
    std::map<const char, int> fourth;
    std::map<const char, int> fifth;

    float* weights_one;
    float* weights_two;
    float* weights_three;
    float* weights_four;
    float* weights_five;

public:
    Analysis();
    void enter(std::string str);
    void create_weights();
    void set_weight_array();

private:
    float *calculate_weight(const std::map<const char, int> &map) const;
};


#endif //UNTITLED_ANALYSIS_H

#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H


#include <map>
#include <vector>

struct weighted_word {
    std::string word;
    const char a;
    float a_f;
    const char b;
    float b_f;
    const char c;
    float c_f;
    const char d;
    float d_f;
    const char e;
    float e_f;
    float weight;
};

class Analysis {
private:
    const std::string ALPHABET = {"abcdefghijklmnopqrstuvwxyz"};

    std::vector<std::string> words;
    unsigned int lines{};

    std::map<const char, int> first;
    std::map<const char, int> second;
    std::map<const char, int> third;
    std::map<const char, int> fourth;
    std::map<const char, int> fifth;

    std::map<char, float> weighted_first{};
    std::map<char, float> weighted_second{};
    std::map<char, float> weighted_third{};
    std::map<char, float> weighted_fourth{};
    std::map<char, float> weighted_fifth{};

    std::vector<weighted_word> weighted_words;

public:
    Analysis();

    void enter(std::string str);

    void create_weights();

    void set_weight_array();

private:
    std::map<char, float> calculate_weight(const std::map<const char, int> &map) const;

    weighted_word generate_weighted_word(std::string);
};


#endif //UNTITLED_ANALYSIS_H

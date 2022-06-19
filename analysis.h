#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H


#include <map>
#include <vector>

enum State {
    GREEN,
    YELLOW,
    GREY,
};

struct weighted_word {
    std::string word;
    std::pair<char, float> first;
    std::pair<char, float> second;
    std::pair<char, float> third;
    std::pair<char, float> fourth;
    std::pair<char, float> fifth;
    float linear;
    float complex;
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

    void set_array_weight();

    void test_word(std::vector<std::pair<char, State>> pairs);

private:
    std::map<char, float> calculate_weight(const std::map<const char, int> &map) const;

    weighted_word generate_weighted_word(std::string);

    static bool compare(const weighted_word& lhs, const weighted_word& rhs);

    void display_weights();
};


#endif //UNTITLED_ANALYSIS_H

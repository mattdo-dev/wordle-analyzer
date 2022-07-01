#ifndef UNTITLED_ANALYSIS_H
#define UNTITLED_ANALYSIS_H

#include <map>
#include <regex>
#include <vector>

enum State {
    GREEN,
    YELLOW,
    GREY,
};

struct weighted_word {
    std::string word;
    std::vector<std::pair<const char, float>> weights;
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
    explicit Analysis(const std::string& file_name);

    void start();

    static std::vector<std::pair<char, State>> enter_word(std::string args);

    void test_word(std::vector<std::pair<char, State>> pairs);

private:
    void enter(std::string str);

    void create_weights();

    void set_array_weight();

    std::map<char, float> calculate_weight(const std::map<const char, int> &map) const;

    weighted_word generate_weighted_word(std::string);

    void display_weights();

    static bool compare(const weighted_word& lhs, const weighted_word& rhs);

    static std::string exclude(const std::string& init, char c);
};


#endif //UNTITLED_ANALYSIS_H

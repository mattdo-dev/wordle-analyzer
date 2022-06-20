#include <iostream>
#include <fstream>

#include "analysis.h"

int main() {
    std::string dir = R"(../words.txt)";
    std::ifstream file;
    Analysis analysis = Analysis();

    try {
        file.open(dir, std::ios::in);

        if (file.is_open()) {
            std::string word;
            while (std::getline(file, word)) {
                analysis.enter(word);
            }
        }

        file.close();

        analysis.create_weights();
        analysis.set_array_weight();

        std::vector<std::pair<char, State>> test;

        std::pair<char, State> one;
        one.first = 'd';
        one.second = State::GREY;
        std::pair<char, State> two;
        two.first = 'e';
        two.second = State::YELLOW;
        std::pair<char, State> thr;
        thr.first = 'a';
        thr.second = State::GREY;
        std::pair<char, State> fou;
        fou.first = 'l';
        fou.second = State::YELLOW;
        std::pair<char, State> fiv;
        fiv.first = 't';
        fiv.second = State::GREY;

        test.push_back(one);
        test.push_back(two);
        test.push_back(thr);
        test.push_back(fou);
        test.push_back(fiv);

        analysis.test_word(test);

    } catch (const std::ifstream::failure &failure) {
        std::cout << failure.what() << "\n";
    }

    return 0;
}

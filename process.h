//
// Created by Nobody on 7/1/2022.
//

#ifndef WORDLE_ANALYZER_PROCESS_H
#define WORDLE_ANALYZER_PROCESS_H

#include <string>
#include <vector>


class Process {
    struct word {
        std::string word;
        char one = word.at(0);
        char two = word.at(1);
        char three = word.at(2);
        char four = word.at(3);
        char five = word.at(4);
    };
public:
    virtual void test_word(std::string word);

    virtual void display_results();

private:
    virtual void sort();
};


#endif //WORDLE_ANALYZER_PROCESS_H

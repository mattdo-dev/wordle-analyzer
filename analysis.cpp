//
// Created by Matt Do on 5/20/2022.
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <future>
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
    lines++;
}

void Analysis::assign_weight(const std::map<const char, int>& map) {

}

void Analysis::display() {
    auto one = [this] {
        int i = 0;
        auto *weights = new float[this->lines];
        for (auto const& x : first) {
            weights[i] = (float) x.second /  (float) this->lines;
            i++;
        }
        return weights;
    };

    auto two = [this] {
        int i = 0;
        auto *weights = new float[this->lines];
        for (auto const& x : second) {
            weights[i] = (float) x.second /  (float) this->lines;
            i++;
        }
        return weights;
    };

    auto three = [this] {
        int i = 0;
        auto *weights = new float[this->lines];
        for (auto const& x : third) {
            weights[i] = (float) x.second /  (float) this->lines;
            i++;
        }
        return weights;
    };

    auto four = [this] {
        int i = 0;
        auto *weights = new float[this->lines];
        for (auto const& x : fourth) {
            weights[i] = (float) x.second /  (float) this->lines;
            i++;
        }
        return weights;
    };

    auto five = [this] {
        int i = 0;
        auto *weights = new float[this->lines];
        for (auto const& x : fifth) {
            weights[i] = (float) x.second /  (float) this->lines;
            i++;
        }
        return weights;
    };

    std::thread th_one(one);
    std::thread th_two(two);
    std::thread th_three(three);
    std::thread th_four(four);
    std::thread th_five(five);

    th_one.join();
    th_two.join();
    th_three.join();
    th_four.join();
    th_five.join();

    std::promise<float *> p;
    auto f = p.get_future();
    float * array = f.get();
}
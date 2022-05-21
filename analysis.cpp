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

float* Analysis::assign_weight(const std::map<const char, int>& map) {
    int i = 0;
    auto *weights = new float[this->lines];
    for (auto const x : map) {
        weights[i] = (float) x.second /  (float) this->lines * 100;
        i++;
    }
    return weights;
}

void Analysis::display() {
    auto one = [this](std::promise<float*> p) {
        p.set_value(assign_weight(first));
    };

    auto two = [this](std::promise<float*> p) {
        p.set_value(assign_weight(second));
    };

    auto three = [this](std::promise<float*> p) {
        p.set_value(assign_weight(third));
    };

    auto four = [this](std::promise<float*> p) {
        p.set_value(assign_weight(fourth));
    };

    auto five = [this](std::promise<float*> p) {
        p.set_value(assign_weight(fifth));
    };

    std::promise<float*> pr_one;
    auto f_one = pr_one.get_future();
    std::promise<float*> pr_two;
    auto f_two = pr_two.get_future();
    std::promise<float*> pr_three;
    auto f_three = pr_three.get_future();
    std::promise<float*> pr_four;
    auto f_four = pr_four.get_future();
    std::promise<float*> pr_five;
    auto f_five = pr_five.get_future();

    std::thread th_one(one, std::move(pr_one));
    std::thread th_two(two, std::move(pr_two));
    std::thread th_three(three, std::move(pr_three));
    std::thread th_four(four, std::move(pr_four));
    std::thread th_five(five, std::move(pr_five));

    th_one.join();
    th_two.join();
    th_three.join();
    th_four.join();
    th_five.join();

    float* weights_one = f_one.get();
    float* weights_two = f_two.get();
    float* weights_three = f_three.get();
    float* weights_four = f_four.get();
    float* weights_five = f_five.get();

    for (int i = 0; i < ALPHABET.length(); i++) {
        std::cout << weights_one[i] << ", ";
    }
}
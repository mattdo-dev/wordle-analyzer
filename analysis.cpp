#include <algorithm>
#include <iostream>
#include <thread>
#include <future>
#include <regex>
#include <vector>
#include "analysis.h"

Analysis::Analysis() {
    for (char c: ALPHABET) {
        first.insert(std::pair<const char, int>(c, 0));
        second = first;
        third = first;
        fourth = first;
        fifth = first;
    }
}

void Analysis::enter(std::string word) {
    words.push_back(word);
    first[word.at(0)]++;
    second[word.at(1)]++;
    third[word.at(2)]++;
    fourth[word.at(3)]++;
    fifth[word.at(4)]++;
}

void Analysis::create_weights() {
    lines = words.size();
    auto one = [this](std::promise<std::map<char, float>> p) {
        p.set_value(calculate_weight(first));
    };

    auto two = [this](std::promise<std::map<char, float>> p) {
        p.set_value(calculate_weight(second));
    };

    auto three = [this](std::promise<std::map<char, float>> p) {
        p.set_value(calculate_weight(third));
    };

    auto four = [this](std::promise<std::map<char, float>> p) {
        p.set_value(calculate_weight(fourth));
    };

    auto five = [this](std::promise<std::map<char, float>> p) {
        p.set_value(calculate_weight(fifth));
    };

    std::promise<std::map<char, float>> pr_one;
    auto f_one = pr_one.get_future();
    std::promise<std::map<char, float>> pr_two;
    auto f_two = pr_two.get_future();
    std::promise<std::map<char, float>> pr_three;
    auto f_three = pr_three.get_future();
    std::promise<std::map<char, float>> pr_four;
    auto f_four = pr_four.get_future();
    std::promise<std::map<char, float>> pr_five;
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

    weighted_first = f_one.get();
    weighted_second = f_two.get();
    weighted_third = f_three.get();
    weighted_fourth = f_four.get();
    weighted_fifth = f_five.get();
}

void Analysis::set_array_weight() {
    for (const std::string &word: words) {
        weighted_words.push_back(generate_weighted_word(word));
    }

    std::sort(weighted_words.begin(), weighted_words.end(), compare);
}

void Analysis::test_word(std::vector<std::pair<char, State>> pairs) {

    if (pairs.size() != 5) {
        throw std::invalid_argument("Size of vector needs to be of size 5.");
    }

    std::string greys;
    char yellows[5] = {};
    char greens[5] = {};
    std::vector<weighted_word> new_list;

    for (int i = 0; i < 5; i++) {
        std::pair<char, State> pair = pairs.at(i);
        if (pair.second == State::GREY) {
            greys += pair.first;
        } else if (pair.second == State::YELLOW) {
            yellows[i] = pair.first;
        } else if (pair.second == State::GREEN) {
            greens[i] = pair.first;
        }
    }

    std::string regex_expr = "^";

    for (int i = 0; i < 5; i++) {
        if (pairs.at(i).second == State::GREEN) {
            regex_expr += pairs.at(i).first;
            regex_expr += '?';
        }

        if (pairs.at(i).second == State::YELLOW) {
            regex_expr += exclude(greys, pairs.at(i).first);
        }

        if (pairs.at(i).second == State::GREY) {
            regex_expr += exclude(greys, '\0');
        }

        regex_expr += "{1}";
    }

    regex_expr += '$';

    std::regex regex(regex_expr, std::regex::icase);

    for (const weighted_word &word: weighted_words) {
        if (std::regex_match(word.word, regex)) {
            new_list.push_back(word);
        }
    }

    Analysis::display_weights(new_list);
    std::cout << "regexp: " << regex_expr << std::endl;
    std::cout << "No. remaining words: " << new_list.size() << std::endl;
}

std::vector<std::pair<char, State>> Analysis::enter_word(std::string args) {
    //TODO fix
    std::replace(args.begin(), args.end(), ';', '\0');
    std::vector<std::string> words;
    std::stringstream ss(args);
    int temp;
    while (ss >> temp) {
        words.push_back(std::to_string(temp));
    }

    std::vector<std::pair<char, State>> pairs;

    for (int i = 0; i < 5; i++) {
        if (std::regex_match(words.at(i), std::regex(":(n|grey)"))) {
            pairs.emplace_back(words.at(i).at(0), State::GREY);
        } else if (std::regex_match(words.at(i), std::regex(":(y|yellow)"))) {
            pairs.emplace_back(words.at(i).at(0), State::YELLOW);
        } else if (std::regex_match(words.at(i), std::regex(":(g|green)"))) {
            pairs.emplace_back(words.at(i).at(0), State::GREEN);
        } else {
            throw std::invalid_argument("Invalid input.");
        }
    }

    return pairs;
}

std::map<char, float> Analysis::calculate_weight(const std::map<const char, int> &map) const {
    std::map<char, float> weights;
    for (auto const &x: map) {
        weights.insert(std::pair<const char, float>(x.first, (float) x.second / (float) lines * 100));
    }
    return weights;
}

weighted_word Analysis::generate_weighted_word(std::string word) {
    float _one = weighted_first.at(word.at(0));
    float _two = weighted_second.at(word.at(1));
    float _three = weighted_third.at(word.at(2));
    float _four = weighted_fourth.at(word.at(3));
    float _five = weighted_fifth.at(word.at(4));

    std::vector<std::pair<const char, float>> weights = {
            std::pair<const char, float>(word.at(0), _one),
            std::pair<const char, float>(word.at(1), _two),
            std::pair<const char, float>(word.at(2), _three),
            std::pair<const char, float>(word.at(3), _four),
            std::pair<const char, float>(word.at(4), _five)
    };

    return weighted_word {
            word,
            weights,
            _one + _two + _three + _four + _five,
            (_one * _two) / 2 + (_two * _three) / 3 + (_three + _four) / 3 * (_four + _five) / 2,
    };
}

bool Analysis::compare(const weighted_word& lhs, const weighted_word& rhs) {
    // Bottoms up
    if (lhs.linear > rhs.linear) {
        return false;
    }
    return true;
}

void Analysis::display_weights(const std::vector<weighted_word>& words) {
    for (const weighted_word& w: words) {
        // print all the contents of w
        std::cout << w.word << ": ";
        for (int i = 0; i < 5; i++) {
            std::cout << w.weights.at(i).first << ": " << w.weights.at(i).second << "; ";
        }
        std::cout << "score: " << w.linear << "\n";
    }
}

std::string Analysis::exclude(const std::string& init, char c) {
    std::stringstream s;
    if (c == '\0') {
        s << "[^" << init << "]";
    } else {
        s << "[^" << init << c << "]";
    }
    return s.str();
}

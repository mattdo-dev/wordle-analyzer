//
// Created by Nobody on 1/1/2023.
//

#ifndef WORDLE_ANALYZER_THREADED_ANALYSIS_H
#define WORDLE_ANALYZER_THREADED_ANALYSIS_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <regex>

#include "fast_read.h"

enum State {
    GREEN,
    YELLOW,
    GREY,
};


class threaded_analysis {

    typedef std::vector<std::pair<char, State>> word_state;
public:
    explicit threaded_analysis(const std::string &file_name) {
        try {
            std::ifstream file(file_name);
            if (!file.is_open()) {
                throw std::runtime_error("File not found");
            }
            std::string line;
            while (!sanitize_getline(file, line).eof()) {
                words.push_back(line);
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };

    void start() {
        for(;;) {
            try {
                temp.clear();
                std::cout << "Enter a word to search for: ";
                std::string word;
                std::cin >> word;
                word_state pairs = enter_word(word);
                generate_regex(pairs);
                workers = threads; // Reset the worker counter
                complete = false; // Reset the completion flag
                for (int i = 0; i < threads; i++) {
                    guessers_threads.emplace_back(&threaded_analysis::guessers, this, i * blocks);
                }

                // Wait for all workers to finish
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&] { return complete; });

                for (auto &thread : guessers_threads) {
                    std::cout << "Joining thread" << std::endl;
                    thread.join();
                }

                for (std::string &w : temp) {
                    std::cout << w << std::endl;
                }

                guessers_threads.clear();
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

private:
    bool complete = false;
    unsigned int workers = 0;
    unsigned int threads = std::thread::hardware_concurrency();
    unsigned int lines = 2309;
    unsigned int blocks = std::ceil(lines / threads);

    std::string greys;
    std::string yellows;
    std::string regex_expr;

    std::vector<std::string> words;
    std::vector<std::string> temp;

    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::thread> guessers_threads;

    static word_state enter_word(std::string word) {
        if (word == "exit") {
            exit(0);
        }

        std::string arg = std::move(word);
        std::replace(arg.begin(), arg.end(), ';', ' ');
        std::string buffer;
        std::stringstream ss(arg);
        std::vector<std::string> tokens;

        while (ss >> buffer) {
            tokens.push_back(buffer);
        }

        std::vector<std::pair<char, State>> pairs;

        for (int i = 0; i < 5; i++) {
            if (std::regex_match(tokens.at(i), std::regex(".:(n|grey)"))) {
                pairs.emplace_back(tokens.at(i).at(0), State::GREY);
            } else if (std::regex_match(tokens.at(i), std::regex(".:(y|yellow)"))) {
                pairs.emplace_back(tokens.at(i).at(0), State::YELLOW);
            } else if (std::regex_match(tokens.at(i), std::regex(".:(g|green)"))) {
                pairs.emplace_back(tokens.at(i).at(0), State::GREEN);
            } else {
                throw std::invalid_argument("Invalid input.");
            }
        }

        return pairs;
    }

    void generate_regex(word_state word) {
        std::string generated_regex;

        for (auto& pair : word) {
            if (pair.second == State::GREY && greys.find(pair.first) == std::string::npos) {
                greys += pair.first;
            } else if (pair.second == State::YELLOW && yellows.find(pair.first) == std::string::npos) {
                yellows += pair.first;
            }
        }

        if (!yellows.empty()) {
            for (char c : yellows) {
                generated_regex += "(?=.*[";
                generated_regex += c;
                generated_regex += "])";
            }
        }

        for (int i = 0; i < 5; i++) {
            if (word.at(i).second == State::GREEN) {
                generated_regex += word[i].first;
                continue;
            } else if (word.at(i).second == State::YELLOW) {
                generated_regex += exclude(greys, word[i].first);
                continue;
            } else if (word.at(i).second == State::GREY) {
                generated_regex += exclude(greys, '\0');
            }
        }

        regex_expr = generated_regex;
    }

    static std::string exclude(std::string& letters, char compare) {
        std::string s;

        if (compare == '\0') {
            s += "[^" + letters + "]";
        } else {
            s += "[^" + letters + compare + "]";
        }

        return s;
    }

    void guessers(int index) {
        std::vector<std::string> good_words;
        std::regex regex(regex_expr, std::regex::ECMAScript | std::regex::icase);
        for (int i = index; i < index + blocks && i < words.size(); i++) {
            if (std::regex_match(words[i], regex)) {
                good_words.push_back(words[i]);
            }
        }

        std::unique_lock<std::mutex> lock(mtx);
        temp.insert(temp.end(), good_words.begin(), good_words.end());
        workers--;

        // If this was the last worker, notify the main thread
        if (workers == 0) {
            complete = true;
            cv.notify_one();
        }
    }
};


#endif //WORDLE_ANALYZER_THREADED_ANALYSIS_H

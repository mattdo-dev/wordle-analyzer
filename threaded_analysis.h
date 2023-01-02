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
    explicit threaded_analysis(const std::string& file_name) {
        try {
            std::ifstream file(file_name);
            if (!file.is_open()) {
                throw std::runtime_error("File not found");
            }
            std::string line;
            while (!sanitize_getline(file, line).eof()) {
                this->insert_into_chunk(line);
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void start() {
        for(;;) {
            try {
                std::cout << "Enter a word to search for: ";
                std::string word;
                std::cin >> word;
                word_state pairs = enter_word(word);
            }
        }
    }

private:
    bool complete = false;
    unsigned int workers = 0;
    unsigned int threads = std::thread::hardware_concurrency();
    unsigned int lines = 2309;
    unsigned int blocks = std::ceil(lines / threads);

    std::unordered_set<std::string> greys;
    std::unordered_set<std::string> yellows;

    std::vector<std::vector<std::string>> chunks;

    std::mutex mtx;
    std::condition_variable cv;

    word_state enter_word(std::string word) {
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

    void insert_into_chunk(std::string word) {
        for (auto& chunk : chunks) {
            if (chunk.size() < blocks) {
                chunk.push_back(word);
                return;
            }
        }
        chunks.push_back({word});
    }

    // TODO: idea is to merge the chunks into one vector.
    void guessers(word_state& word, std::vector<std::string>& chunk, int index) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !chunk.empty() || complete; });
            if (complete) {
                return;
            }

            lock.unlock();
            std::vector<std::string> good_words;



            workers++;

            workers--;
            lock.unlock();

            if (workers == 0)
                complete = true;
            cv.notify_all();
        }
    }

    bool check_word(std::string& to_test) {

    }
};


#endif //WORDLE_ANALYZER_THREADED_ANALYSIS_H

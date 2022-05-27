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

    } catch (const std::ifstream::failure &failure) {
        std::cout << failure.what() << "\n";
    }

    return 0;
}

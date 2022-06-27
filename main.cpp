#include <iostream>
#include <fstream>

#include "analysis.h"

std::istream& sanitize_getline(std::istream& is, std::string& t){
    t.clear();

    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case std::streambuf::traits_type::eof():
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char) c;
        }
    }
}

int main() {
    std::string dir = "../words.txt";
    std::ifstream file;
    Analysis analysis = Analysis();

    try {
        file.open(dir.c_str(), std::ios::in);

        if (file.is_open()) {
            std::string word;
            // be sure to deal with universal file handling, i.e. \r, \n, the like
            while (!sanitize_getline(file, word).eof()) {
                analysis.enter(word);
            }
        } else {
            std::cout << "Could not open file" << std::endl;
            return EXIT_FAILURE;
        }

        file.close();

        analysis.create_weights();
        analysis.set_array_weight();

        std::string in;

        for (int i = 0; i < 5; i++) {
            std::cout << "Enter word: ";
            std::cin >> in;
            std::vector<std::pair<char, State>> pairs = Analysis::enter_word(in);
            analysis.test_word(pairs);
        }

    } catch (const std::ifstream::failure &failure) {
        std::cout << failure.what() << "\n";
    }

    return 0;
}

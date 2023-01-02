#include <iostream>

#include "threaded_analysis.h"

int main() {
    std::string dir = "../words.txt";
    threaded_analysis analysis = threaded_analysis(dir);
    analysis.random();
    return 0;
}

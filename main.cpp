#include <iostream>

#include "threaded_analysis.h"

int main() {
    std::string dir = "../words.txt";
    threaded_analysis analysis(dir);
    analysis.start();
    return 0;
}

#include <iostream>

#include "analysis.h"

int main() {
    std::string dir = "../words.txt";
    Analysis analysis = Analysis(dir);
    analysis.start();

    return 0;
}

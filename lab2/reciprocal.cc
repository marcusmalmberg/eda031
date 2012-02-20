#include <iostream>
#include <cstdlib> // for atoi, see below

double reciprocal(int i) {
    return 1.0 / i;
}

int main(int argc, char** argv) {
    int i = std::atoi(argv[1]); // atoi: "ascii-to-integer"
    double r = reciprocal(i);
    std::cout << "argv[1] = " << argv[1] << ", 1/argv[1] = " << r << std::endl;
}

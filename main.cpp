#include <iostream>
#include <boost/dynamic_bitset.hpp>
int main(int, char*[]) {
    boost::dynamic_bitset<> x(1); // all 0's by default
    x[0] = 1;
    x.push_back(0);
    std::cout << x[0];

    return EXIT_SUCCESS;
}
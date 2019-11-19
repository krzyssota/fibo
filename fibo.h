#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <boost/dynamic_bitset.hpp>

class Fibo {
public:
    Fibo();
    Fibo(std::string str);
    Fibo(unsigned long long n);

private:
    boost::dynamic_bitset<> fibset;

    void normalize();
};

#endif //FIBO_H

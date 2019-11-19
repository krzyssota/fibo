#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <boost/dynamic_bitset.hpp>

class Fibo {
public:
    Fibo();
    Fibo(std::string str);
    Fibo(unsigned long long n);
    Fibo(const Fibo& that);
    Fibo(Fibo&& that);

    Fibo& operator=(const Fibo& that);
    Fibo& operator=(Fibo&& that);

private:
    boost::dynamic_bitset<> fibset;

    void normalize();
    void cutZeros();
};

#endif //FIBO_H

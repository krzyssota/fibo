#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <boost/dynamic_bitset.hpp>

class Fibo {
public:
    Fibo();
    Fibo(std::string str);
    Fibo(unsigned long long n);
    void normalize(); // TODO może nie potrzebne (dodane dla potrzeb operator+)
    boost::dynamic_bitset<> getFibset() { return fibset; }
    Fibo& operator+=(Fibo a);
    
private:
    boost::dynamic_bitset<> fibset;

    //void normalize(); // TODO może nie potrzebne (dodane dla potrzeb operator+)
    void cutZeros();
};

#endif //FIBO_H

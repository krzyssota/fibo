#include <boost/dynamic_bitset.hpp>
#include "fibo.h"
#include <vector>
#include <iostream>

void completeFibNumbers(std::vector<unsigned long long>& fib, int to) {
    if(fib.empty()) {
        fib.push_back(1);
        fib.push_back(2);
    }

    for(int i = fib.size() - 1, j = fib.size() - 2; i <= to; i++, j++) {
        fib.push_back(fib[i] + fib[j]);
    }
}

unsigned long long getFibNumber(int i) {
    static std::vector<unsigned long long> fib;

    if(i >= fib.size()) {
        completeFibNumbers(fib, i);
    }

    return fib[i];
}

Fibo::Fibo() {

}

Fibo::Fibo(int n) {

}

Fibo::Fibo(std::string str) {

}


boost::dynamic_bitset<> normalize(boost::dynamic_bitset<> x){
    size_t safeSpot = x.size();
    for(size_t i = x.size()-1; i >= 1;){
        int j = i;
        while(j-1 >= 0 && x[j] == 1 && x[j-1] == 0){
            j-=2;
        }
        if(x[j] == 1 && x[j-1] == 1) {
            x[j] = 0;
            x[j-1] = 0;

            for(size_t k = safeSpot-1; k > j+1;){
                x[k] = 0;
                k -= 2;

            }
            if(safeSpot == x.size()) x.push_back(0);
            x[safeSpot] = 1;
        }
        safeSpot = j-1;
        if(i>=2) i = j-2;
        else i = 0;
    }
    return x;
}

int main(int, char*[]) {
    boost::dynamic_bitset<> x(3); // all 0's by default
    x[0] = 1;
    x[1] = 1;
    x[2] = 1;
    /*x[3] = 1;
    x[4] = 0;
    x[5] = 1;
    x[6] = 0;
    x[7] = 1;*/
    std::cout << x << "\n";
    x = normalize(x);
    std::cout << x << "\n";
}
    //Fibo f1      - tworzy liczbę 0
    //
    //Fibo f1(str) - tworzy liczbę na podstawie napisu str, który jest zapisem tej
    //               liczby w systemie Fibonacciego (zapis niekoniecznie musi być
    //               w postaci unormowanej)
    //
    //Fibo(n)      - tworzy liczbę równą liczbie całkowitej n
    //
    //Fibo f1(f2)  - konstruktor kopiujący
    //
    //f1 = f2 - przypisanie
    //
    //f1 + f2 - dodawanie
    //
    //f1 & f2 - and fibitowy (na postaci unormowanej)
    //
    //f1 | f2 - or fibitowy (na postaci unormowanej)
    //
    //f1 ^ f2 - xor fibitowy (na postaci unormowanej)
    //
    //f1 << n  - przesunięcie fibitowe w lewo o n pozycji
    //
    //f1 += f2
    //
    //f1 &= f2
    //
    //f1 |= f2
    //
    //f1 ^= f2
    //
    //f1 <<= n
    //
    //f1 op f2 - operatory porównujące wartości liczbowe reprezentowane przez f1 i f2,
    //           gdzie op to jeden z operatorów: ==, <, <=, != , >, >=
    //
    //os << f1 - wypisuje f1 na strumień os bez żadnych białych znaków w postaci
    //           unormowanej
    //
    //f1.length() - zwraca długość zapisu w postaci unormowanej liczby f1
    //
    //Ponadto należy zaimplementować globalne funkcje:
    //
    //Zero() - zwraca obiekt reprezentujący liczbę 0
    //
    //One()  - zwraca obiekt reprezentujący liczbę 1
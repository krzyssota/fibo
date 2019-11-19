#include "fibo.h"
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <iostream>
#include <cmath>

namespace {
    double phi() {
        static double phi = (1 + std::sqrt(5)) / 2;
        return phi;
    }

    size_t findK(unsigned long long n) {
        if(n == 0) {
            return 0;
        }

        double numerator = std::log(n * std::sqrt(5) + 0.5);
        static double dominator = std::log(phi());

        return std::floor(numerator/dominator) - 2;
    }

    void completeFibNumbers(std::vector<unsigned long long>& fib, size_t to) {
        if (fib.empty()) {
            fib.push_back(1);
            fib.push_back(2);
        }

        for (size_t i = fib.size() - 1, j = fib.size() - 2; i <= to; i++, j++) {
            fib.push_back(fib[i] + fib[j]);
        }
    }

    unsigned long long getFibNumber(size_t i) {
        static std::vector<unsigned long long> fib;

        if (i >= fib.size()) {
            completeFibNumbers(fib, i);
        }

        return fib[i];
    }
}


Fibo::Fibo() : fibset(0) {

}

Fibo::Fibo(std::string str) : Fibo() {
    //TODO: remove leading 0
    for (int i = str.length() - 1; i >= 0; i--) {
        fibset.push_back(str[i] == '1');
    }

    normalize();
}

Fibo::Fibo(unsigned long long n) : fibset(findK(n) + 1) {
    while(n != 0) {
        size_t k = findK(n);
        auto fibNum = getFibNumber(k);
        fibset[k] = 1;
        n -= fibNum;
    }
}

void Fibo::normalize() {
    size_t safeSpot = fibset.size();
    for (size_t i = fibset.size() - 1; i >= 1;) {
        int j = i;
        while (j - 1 >= 0 && fibset[j] == 1 && fibset[j - 1] == 0) {
            j -= 2;
        }

        if (fibset[j] == 1 && fibset[j - 1] == 1) {
            fibset[j] = 0;
            fibset[j - 1] = 0;

            for (size_t k = safeSpot - 1; k > j + 1;) {
                fibset[k] = 0;
                k -= 2;
            }
            if (safeSpot == fibset.size()) {
                fibset.push_back(0);
            }
            fibset[safeSpot] = 1;
        }

        safeSpot = j - 1;
        if (i >= 2) {
            i = j - 2;
        }
        else {
            i = 0;
        }
    }
}

void Fibo::cutZeros() {
    size_t first1 = 0;
    for(size_t i = fibset.size() - 1; i >= 0; i--) {
        if(fibset[i]) {
            first1 = i;
            break;
        }
    }

    fibset.resize(first1 + 1, false);
}

int main(int, char* []) {
    std::cout << findK(1) << std::endl;
    std::cout << findK(2) << std::endl;
    std::cout << findK(0) << std::endl;
    std::cout << findK(28) << std::endl << "koniec\n";

    std::string r = "12345";
    for (int i = 0; i < r.length(); i++) {
        std::cout << r[i];
    }


    boost::dynamic_bitset<> x(3); // all 0's by default
    x[0] = 1;
    x[1] = 1;
    std::cout << std::endl << x << std::endl;

    x[2] = 1;
    /*x[3] = 1;
    x[4] = 0;
    x[5] = 1;
    x[6] = 0;
    x[7] = 1;*/
    std::cout << x << "\n";
    //x = normalize(x);
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
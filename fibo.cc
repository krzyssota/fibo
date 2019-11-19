#include "fibo.h"
#include <boost/dynamic_bitset.hpp>
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

Fibo::Fibo() : fibset(0) {

}

Fibo::Fibo(int n) {

}

Fibo::Fibo(std::string str) : Fibo() {
    //TODO: remove leading 0
    for(int i = str.length() - 1; i <= 0; i--) {
        fibset.push_back(str[i] == '1');
    }
}


boost::dynamic_bitset<> normalize(boost::dynamic_bitset<>& x){
    size_t i = x.size()-1;
    while(x[i] == 0) --i;
    size_t safeSpot = i+1;

    for(i; i >= 1;){
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

int bitAt(size_t i, boost::dynamic_bitset<> const &c){
    if(i < c.size()) return c[i];
    else return 0;
}
void changeWindow(size_t i, std::vector<short>& window){
    if(window[i] == 0) {
        if (window[i - 1] == 2) {
            if (window[i - 2] == 0) { //020x → 100(x++)
                window[i] = 1;
                window[i - 1] = 0;
                window[i - 2] = 0;
                window[i - 3]++;
            } else if (window[i - 2] == 1) { //021x → 110x
                window[i] = 1;
                window[i - 1] = 1;
                window[i - 2] = 0;
            }
        } else if (window[i - 1] == 3 && window[i - 2] == 0){ //030x → 110(x++)
            window[i] = 1;
            window[i - 1] = 1;
            window[i - 2] = 0;
            window[i - 3]++;
        } else if (window[i - 1] == 1 && window[i - 2] == 0){ //012x → 101x
            window[i] = 1;
            window[i - 1] = 0;
            window[i - 2] = 1;
        }
    }
}
void correctLastWindow(std::vector<short>& window){
    if(window.at(0) == 3){ //  03 can be changed to 11
        window[1] = 1;
        window[0] = 1;
    } else if(window.at(0) == 2){
        if(window.at(1) == 0) { //  02 can be changed to 10
            window[1] = 1;
            window[0] = 0;
        } else if(window.at(1) == 1){    // 012 can be changed to 101
            window[2] = 1;
            window[1] = 0;
            window[0] = 1;
        }
    } else if(window.at(0) == 0){
        if(window.at(1) == 3) { // 030 can be changed to 111
            window[2] = 1;
            window[1] = 1;
            window[0] = 1;
        } else if(window.at(1) == 2){  // 020 can be changed to 101
            if(window.at(2) == 0) {
                window[2] = 1;
                window[1] = 0;
                window[0] = 1;
            } else if(window.at(2) == 1){ //0120 can be changed to 1010
                window[3] = 1;
                window[2] = 0;
                window[1] = 1;
                window[0] = 0;
            }
        }
    }
}

boost::dynamic_bitset<> operator + (boost::dynamic_bitset<> const &c1, boost::dynamic_bitset<> const &c2) {

    std::vector<short> vector;
    for (size_t i = 0; i < std::max(c1.size(), c2.size()); ++i) {
        vector.push_back(bitAt(i, c1) + bitAt(i, c2));
    }

    if(vector.at(vector.size() - 1) != 0) vector.push_back(0);
    for(size_t j = vector.size() - 1; j >= 3; --j) {
        changeWindow(j, vector);
    }
    correctLastWindow(vector);

    boost::dynamic_bitset<> result(vector.size());
    for(size_t i = 0; i < vector.size() ; ++i) result[i] = vector.at(i);
    normalize(result);
    return result;
}

int main(int, char*[]) {
    std::string r = "12345";
    for(int i = 0; i < r.length(); i++) {
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
    x = normalize(x);
    std::cout << x << "\n";

    std::cout << std::endl;
    std::cout << std::endl;

    boost::dynamic_bitset<> b(7);
    b[0] = 0;
    b[1] = 0;
    b[2] = 1;
    b[3] = 0;
    b[4] = 0;
    b[5] = 1;
    b[6] = 0;
    boost::dynamic_bitset<> a(7);
    a[0] = 1;
    a[1] = 0;
    a[2] = 1;
    a[3] = 0;
    a[4] = 1;
    a[5] = 0;
    a[6] = 1;

    boost::dynamic_bitset<> c = a+b;
    std::cout << c << std::endl;





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
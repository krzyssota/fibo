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

int main() {
    for(int i = 0; i < 100; i++) {
        std::cout << "fib " << i << " = " << getFibNumber(i) << std::endl;
    }
}

/*Fibo::Fibo() {

}

Fibo::Fibo(int n) {

}

Fibo::Fibo(std::string str) {

}
*/
#include "fibo.h"
#include <boost/dynamic_bitset.hpp>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <functional>

namespace {
    double phi() {
        static double phi = (1 + std::sqrt(5)) / 2;
        return phi;
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

    void changeWindow(size_t i, std::vector<short>& window) {
        if (window[i] == 0) {
            if (window[i - 1] == 2) {
                if (window[i - 2] == 0) { //020x → 100(x++)
                    window[i] = 1;
                    window[i - 1] = 0;
                    window[i - 2] = 0;
                    window[i - 3]++;
                }
                else if (window[i - 2] == 1) { //021x → 110x
                    window[i] = 1;
                    window[i - 1] = 1;
                    window[i - 2] = 0;
                }
            }
            else if (window[i - 1] == 3 && window[i - 2] == 0) { //030x → 110(x++)
                window[i] = 1;
                window[i - 1] = 1;
                window[i - 2] = 0;
                window[i - 3]++;
            }
            else if (window[i - 1] == 1 && window[i - 2] == 0) { //012x → 101x
                window[i] = 1;
                window[i - 1] = 0;
                window[i - 2] = 1;
            }
        }
    }

    void correctLastWindow(std::vector<short>& window) {
        if (window.at(0) == 3) { //  03 can be changed to 11
            window[1] = 1;
            window[0] = 1;
        }
        else if (window.at(0) == 2) {
            if (window.at(1) == 0) { //  02 can be changed to 10
                window[1] = 1;
                window[0] = 0;
            }
            else if (window.at(1) == 1) {    // 012 can be changed to 101
                window[2] = 1;
                window[1] = 0;
                window[0] = 1;
            }
        }
        else if (window.at(0) == 0) {
            if (window.at(1) == 3) { // 030 can be changed to 111
                window[2] = 1;
                window[1] = 1;
                window[0] = 1;
            }
            else if (window.at(1) == 2) {  // 020 can be changed to 101
                if (window.at(2) == 0) {
                    window[2] = 1;
                    window[1] = 0;
                    window[0] = 1;
                }
                else if (window.at(2) == 1) { //0120 can be changed to 1010
                    window[3] = 1;
                    window[2] = 0;
                    window[1] = 1;
                    window[0] = 0;
                }
            }
        }
    }
}

Fibo::Fibo() : fibset(0) {}

Fibo::Fibo(const std::string& str) : Fibo() {
    //TODO: remove leading 0
    for (int i = str.length() - 1; i >= 0; i--) {
        assert(str[i] == '1' || str[i] == '0');
        fibset.push_back(str[i] == '1');
    }

    normalize();
    cutZeros();
}

Fibo::Fibo(const Fibo& that) : fibset(that.fibset) {

}

Fibo::Fibo(Fibo&& that) noexcept : fibset(std::move(that.fibset)) {

}

Fibo& Fibo::operator=(const Fibo& that) {
    fibset = that.fibset;
    return *this;
}

Fibo& Fibo::operator=(Fibo&& that) noexcept {
    fibset = std::move(that.fibset);
    return *this;
}

Fibo& Fibo::operator+=(const Fibo& b) { // TODO zrobic w pamieci stalej jak starczy czasu
    std::vector<short> vector;
    unsigned long maxLength = std::max(this->length(), b.length());
    vector.reserve(maxLength); // TODO potrzebne?
    for (unsigned long i = 0; i < maxLength; ++i) {
        vector.push_back(this->bitAt(i) + b.bitAt(i));
    }

    if (vector.at(vector.size() - 1) != 0) vector.push_back(0);
    for (size_t j = vector.size() - 1; j >= 3; --j) {
        changeWindow(j, vector);
    }
    correctLastWindow(vector);

    std::reverse(vector.begin(), vector.end()); // troche gówno
    std::ostringstream oss;
    if (!vector.empty()) {
        std::copy(vector.begin(), vector.end(), std::ostream_iterator<int>(oss, ""));
    }
    std::string s = oss.str(); // dotąd ale działa

    Fibo result(s);
    result.normalize();
    this->fibset = result.fibset; // TODO efektywne? może jakiś move?
    return *this;
}

Fibo& Fibo::operator&=(const Fibo& b) {
    doBitwiseOperation(b, std::bit_and<>());
    return *this;
}

Fibo& Fibo::operator|=(const Fibo& b) {
    doBitwiseOperation(b, std::bit_or<>());
    return *this;
}

Fibo& Fibo::operator^=(const Fibo& b) {
    doBitwiseOperation(b, std::bit_xor<>());
    return *this;
}

Fibo& Fibo::operator<<=(unsigned long long rhs) {
    fibset.resize(fibset.size() + rhs, false);
    fibset <<= rhs;
}

bool operator<(const Fibo& lhs, const Fibo& rhs) {
    return lhs.fibset < rhs.fibset;
}

bool operator==(const Fibo& lhs, const Fibo& rhs) {
    return lhs.fibset == rhs.fibset;
}

size_t Fibo::length() const {
    return fibset.size();
}

std::ostream& operator<<(std::ostream& stream, const Fibo& fibo) {
    stream << fibo.fibset;
    return stream;
}

bool Fibo::bitAt(size_t i) const {
    if (i < fibset.size()) return fibset[i];
    else return false;
}

void Fibo::normalize() {

    size_t i = fibset.size() - 1;
    while (fibset[i] == 0) --i;
    size_t safeSpot = i + 1;

    for (i; i >= 1;) {
        int j = i;
        while (j - 1 >= 0 && fibset[j] == 1 && fibset[j - 1] == 0) {
            j -= 2;
        }
        if (j >= 1 && fibset[j] == 1 && fibset[j - 1] == 1) {
            fibset[j] = 0;
            fibset[j - 1] = 0;

            for (size_t k = safeSpot - 1; k > j + 1;) {
                fibset[k] = 0;
                k -= 2;

            }
            if (safeSpot == fibset.size()) fibset.push_back(0);
            fibset[safeSpot] = 1;
            j >= 1 ? safeSpot = j - 1 : safeSpot = 0;
            if (j >= 2) i = j - 2;
            else i = 0;
        }
        else if (j >= 1 && fibset[j] == 0 && fibset[j - 1] == 1) {
            safeSpot = j;
            i = j - 1;
        }
        else {
            j >= 1 ? safeSpot = j - 1 : safeSpot = 0;
            if (j >= 2) i = j - 2;
            else i = 0;
        }
    }
}

void Fibo::cutZeros() {
    size_t first1 = 0;
    for (size_t i = fibset.size() - 1; i >= 0; i--) {
        if (fibset[i]) {
            first1 = i;
            break;
        }
    }
    fibset.resize(first1 + 1, false);
}

void Fibo::doBitwiseOperation(const Fibo& b, const std::function<bool(bool, bool)>& f) {
    unsigned long maxLength = std::max(this->length(), b.length());
    for (unsigned long i = 0; i < maxLength; ++i) {
        fibset[i] = f(this->bitAt(i), b.bitAt(i));
    }
    cutZeros();
}

unsigned long long Fibo::getFibNumber(size_t i) {
    static std::vector<unsigned long long> fib;

    if (i >= fib.size()) {
        completeFibNumbers(fib, i);
    }

    return fib[i];
}

size_t Fibo::findK(unsigned long long n) {
    if (n == 0) {
        return 0;
    }

    double numerator = std::log(n * std::sqrt(5) + 0.5);
    static double dominator = std::log(phi());

    return std::floor(numerator / dominator) - 2;
}

const Fibo& Zero() {
    static const Fibo zero;
    return zero;
}

const Fibo& One() {
    static const Fibo one(1);
    return one;
}
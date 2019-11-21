#include "fibo.h"

#include <cassert>
#include <iostream>

int main() {

    int x = 238336;
    int y = 7;
    int z = x+y;
    Fibo fx(x);
    Fibo fy(y);
    Fibo suma = fx+fy;
    bool fxfy = (z == suma);
    std::cout << "x+y == fx+fy: " << fxfy << std::endl;


    bool aa = Fibo(x) < Fibo(y);
    bool bb = x < y;
    std::cout << "fx < fy " << aa << std::endl;
    std::cout << "x < y " << bb << std::endl;


    Fibo f;
    Fibo t1("1001");
    Fibo t2("1100");
    std::cout << t1 << std::endl << t2 << std::endl;
    Fibo t3 = t1 & t2;
    std::cout << t3 << std::endl;

    Fibo tt = Zero();
    std::cout << tt << std::endl;

    Fibo a(42);
    Fibo b(83);
    Fibo c = a + 8; //50
    Fibo d = 26 + b; //109
    assert(c == 50);
    assert(d < 110);
    assert(d >= 109);
    assert(b + 7 == 90);



    assert(f == Zero());
    assert(Fibo(f) == Zero());
    assert(Zero() < One());
    assert(Fibo("11") == Fibo("100"));
    assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));
    assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    assert((Fibo("101") << 3) == Fibo("101000"));

    f = One();
    f <<= 3;
    assert(f == Fibo("1000"));

    f = One();
    assert(f + Fibo("1") == Fibo("10"));
    assert(f == One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    assert(f1 == f2);

    assert(Fibo("11").length() == 3); // 11 == 100

    std::cout << Fibo("11") << std::endl; // prints 100
}

/*#include "fibo.h"

#include <cassert>
#include <iostream>


Fibo testFib(long long n) {
    Fibo a(n);
    std::cout << n << " = " << a << std::endl;
    return  a;
}

int main() {
    Fibo t1("1001");
    Fibo t2("1100");
    std::cout << t1 << std::endl << t2 << std::endl;
    Fibo t3 = t1 & t2;

    return 0;



    Fibo ff = testFib(5);
    testFib(16);
    Fibo a = testFib(26);
    Fibo b = testFib(9);
    testFib(13);
    //do tego momentu ok
    std::cout << std::endl;

    a <<= 2;
    std::cout << a << std::endl;

    Fibo c = b << 1;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    //Fibo d = ff | 4;
    //std::cout << "d = " << d << std::endl;
    std::cout << std::endl << std::endl;

    Fibo f;

    assert(f == Zero());
    assert(Fibo(f) == Zero());
    assert(Zero() < One());
    assert(Fibo("11") == Fibo("100"));
    //assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));

    return 0;
    assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    assert((Fibo("101") << 3) == Fibo("101000"));

    f = One();
    f <<= 3;
    assert(f == Fibo("1000"));

    f = One();
    //assert(f + Fibo("1") == Fibo("10"));
    assert(f == One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    assert(f1 == f2);

    assert(Fibo("11").length() == 3); // 11 == 100

    std::cout << Fibo("11") << std::endl; // prints 100

    return 0;
}*/
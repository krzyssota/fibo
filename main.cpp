#include <iostream>

#include <cassert>
#include "fibo.h"

using namespace std;
// tu wklej swoja klase

const int n = 10;

int tab[n];
string str[n];

int main()
{
    assert((Fibo(4) + Fibo(2)) == 6);
    assert((Fibo(73) + Fibo(3)) == 76);
    assert((Fibo(26) + Fibo(2)) == 28);
    assert((Fibo(52) + Fibo(274)) == 326);
    assert((Fibo(273) + Fibo(23)) == 296);
    assert((Fibo(93) + Fibo(5166)) == 5259);
    assert((Fibo(4) + Fibo(2)) == 6);
    assert((Fibo(4) + Fibo(2)) == 6);
    assert((Fibo(65829) + Fibo(122209)) == (65829+122209));
    for (int i=10000; i<100000; i+=10000) {
        for (int j=0; j<=100000; j++) {
            cout << i << " " << j << endl;
            assert((Fibo(i) + Fibo(j)) == (i+j));
        }
    }



    int x = 238336;
    int y = 7;
    Fibo a(x);
    Fibo b(y);

    Fibo r1 = a + b;
    bool aa = r1 == (x+y);

    cout << a << endl << b << endl << r1 << endl << aa << endl;

    for (int i=0; i<n; i++) {
        //cin >> tab[i];
        tab[i] = i;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<=i; j++) {
            cout << "tab i = " << tab[i] << endl;
            cout << "tab j = " << tab[j] << endl << endl;
            assert((Fibo(tab[i]) + Fibo(tab[j])) == Fibo(tab[i]+tab[j]));
            assert((Fibo(tab[i]) < Fibo(tab[j])) == (tab[i] < tab[j]));
        }
    }

    for (int i=0; i<n; i++) {
        cout << Fibo(tab[i]).length() << " " << Fibo(tab[i]) << "\n";
    }

    // Wydajnosciowe

    for (int i=0; i<n; i++) {
        cin >> str[i];
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<=i; j++) {
            cout << (Fibo(str[i]) + Fibo(str[j])) << "\n";
            cout << (Fibo(str[i]) | Fibo(str[j])) << "\n";
            cout << (Fibo(str[i]) ^ Fibo(str[j])) << "\n";
            cout << (Fibo(str[i]) & Fibo(str[j])) << "\n";
        }
    }
}

// FCAI – Object-Oriented Programming 1 – 2022 - Assignment 1
// Program Name: BigDecimalInt
// Last Modification Date: 13/10/2022
// Author1 and ID and Group: Basmala Mohamed Sayed Gad  ID: 20210090 (a, b, c)
// Author2 and ID and Group: Aya Ali Hassan  ID: 20210083 (d, e)
// Author3 and ID and Group: Mohamed Ashraf Fahim  ID: 20210329 (f, i, j , k)
/*
description: In this problem we developed a new C++ type (class).
that can hold unlimited decimal integer values and performs arithmetic operations on them.
such as: +, -, <, and >.
 */

#include "BigDecimalIntClass.h"

int main() {
/*    string n1 = "-34", n2 = "100", n3 = "-500", n4 = "7";

    BigDecimalInt input(n1), input3(n2);
    BigDecimalInt e = input + input3;
    BigDecimalInt d = input - input3;
    cout << "---------TEST ONE---------" << "\n";
    cout << e;
    cout << d;
    cout << (input < input3) << "\n";
    cout << (input > input3) << "\n";
    cout << input.Sign() << "\n";
    cout << input3.size() << "\n";

    BigDecimalInt in(n1), in2(n3);
    BigDecimalInt a = in + in2;
    BigDecimalInt b = in - in2;
    cout << "---------TEST TWO---------" << "\n";
    cout << a;
    cout << b;
    cout << (in < in2) << "\n";
    cout << (in > in2) << "\n";
    cout << in2.Sign() << "\n";
    cout << in.size() << "\n";

    BigDecimalInt input6(n2), input7(n3);
    BigDecimalInt h = input6 + input7;
    BigDecimalInt f = input6 - input7;
    cout << "---------TEST THREE---------" << "\n";
    cout << h;
    cout << f;
    cout << (input6 < input7) << "\n";
    cout << (input6 > input7) << "\n";
    cout << input6.Sign() << "\n";
    cout << input7.size() << "\n";

    BigDecimalInt in1(n4), in3(n2);
    BigDecimalInt k = in1 + in3;
    BigDecimalInt l = in1 - in3;
    cout << "---------TEST FOUR---------" << "\n";
    cout << k;
    cout << l;
    cout << (in1 < in3) << "\n";
    cout << (in1 > in3) << "\n";
    cout << in1.Sign() << "\n";
    cout << in3.size() << "\n";

    BigDecimalInt test0(n3), test11(n3);
    BigDecimalInt c = test0 + test11;
    BigDecimalInt g = test0 - test11;
    cout << "---------TEST FIVE---------" << "\n";
    cout << c;
    cout << g;
    cout << (test0 < test11) << "\n";
    cout << (test0 > test11) << "\n";
    cout << test0.Sign() << "\n";
    cout << test11.size() << "\n";

    BigDecimalInt test(n3), test2(n2);
    BigDecimalInt j = test + test2;
    BigDecimalInt i = test - test2;
    cout << "---------TEST SIX---------" << "\n";
    cout << j;
    cout << i;
    cout << (test < test2) << "\n";
    cout << (test > test2) << "\n";
    cout << test.Sign() << "\n";
    cout << test2.size() << "\n";

    BigDecimalInt test3(n2), test4(n1);
    BigDecimalInt o = test3 + test4;
    BigDecimalInt p = test3 - test4;
    cout << "---------TEST SEVEN---------" << "\n";
    cout << o;
    cout << p;
    cout << (test3 < test4) << "\n";
    cout << (test3 > test4) << "\n";
    cout << test3.Sign() << "\n";
    cout << test4.size() << "\n";

    BigDecimalInt test5(n3), test6(n4);
    BigDecimalInt q = test5 + test6;
    BigDecimalInt w = test5 - test6;
    cout << "---------TEST EIGHT---------" << "\n";
    cout << q;
    cout << w;
    cout << (test5 < test6) << "\n";
    cout << (test5 > test6) << "\n";
    cout << test5.Sign() << "\n";
    cout << test6.size() << "\n";

    BigDecimalInt test7(n3), test8(n1);
    BigDecimalInt m = test7 + test8;
    BigDecimalInt n = test7 - test8;
    cout << "---------TEST NINE---------" << "\n";
    cout << m;
    cout << n;
    cout << (test7 < test8) << "\n";
    cout << (test7 > test8) << "\n";
    cout << test7.Sign() << "\n";
    cout << test8.size() << "\n";

    BigDecimalInt test9(n2), test10(n4);
    BigDecimalInt x = test9 + test10;
    BigDecimalInt y = test9 - test10;
    cout << "---------TEST TEN---------" << "\n";
    cout << x;
    cout << y;
    cout << (test9 < test10) << "\n";
    cout << (test9 > test10) << "\n";
    cout << test9.Sign() << "\n";
    cout << test10.size() << "\n";*/
    string s1,s2;
    while(cin>>s1>>s2){
        BigDecimalInt a(s1),b(s2);
        cout<<a+b<<endl;
        cout<<a-b<<endl;
        cout<<b-a<<endl;
        cout << (a < b) << "\n";
        cout << (a > b) << "\n";
        cout << a.sign() << "\n";
        cout << b.size() << "\n";
        cout << a.getNumber() << "\n";
        a.setNumber("100");
        cout << a.getNumber() << "\n";
    }

    return 0;
}




//
//  ch16.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//

#include "unit_test.h"

using namespace std;


void test_insertion() {
    bitset<8> bits{ "01110011" };
    string s("Say hello to my lil' fren'!");
    size_t num{ 111 };
    cout << bits;
    cout << '\n';
    cout << s;
    cout << '\n';
    cout << num;
    cout << "s\n";
}


void run_all_tests() {
    run_test(test_insertion, "test_insertion");
}

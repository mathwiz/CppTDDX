//
//  ch16.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//

#include "unit_test.h"

using namespace std;

bitset<8> bits{ "01110011" };
string s("Say hello to my lil' fren'!");
size_t num{ 111 };


void test_insertion() {
    cout << bits;
    cout << '\n';
    cout << s;
    cout << '\n';
    cout << num;
    cout << "s\n";
}

void test_chaining() {
    cout << bits << '\n' << s << '\n' << num << "s\n";
}


void run_all_tests() {
    //run_test(test_insertion, "test_insertion");
    run_test(test_chaining, "test_chaining");
}

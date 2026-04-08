//
//  ch16.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//
#include <iostream>
#include <string>
#include <bitset>

#include "unit_test.h"

using namespace std;

bitset<8> bits{ "01110011" };
string string1("Say hello to my lil' fren'!");
size_t num{ 111 };


void test_insertion() {
    cout << bits;
    cout << '\n';
    cout << string1;
    cout << '\n';
    cout << num;
    cout << "s\n";
}

void test_chaining() {
    cout << bits << '\n' << string1 << '\n' << num << "s\n";
}

void test_extration() {
    double x, y;
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;
    
    string op;
    cout << "operation (+-*/): ";
    cin >> op;
    if (op == "+")
        cout << x + y;
    else if (op == "-")
        cout << x - y;
    else if (op == "*")
        cout << x * y;
    else if (op == "/")
        cout << x / y;
    else
        cout << "bad operation: " << op;
    cout << "\n";
}

void run_all_tests() {
    //run_test(test_insertion, "test_insertion");
    //run_test(test_chaining, "test_chaining");
    run_test(test_extration, "test_extration");
}

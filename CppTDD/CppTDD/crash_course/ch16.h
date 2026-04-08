//
//  ch16.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//
#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

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

void test_extraction() {
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

void test_status() {
    cin.exceptions(istream::badbit);
    string word;
    size_t count{};
    cout << "Start typing words (RET then ctrl-D to stop):\n";
    try {
        while (cin >> word)
            count++;
        cout << "Discovered " << count << " words.\n";
    } catch (const exception& e) {
        cerr << "Error occurred reading from stdin: " << e.what();
    }

}

void test_manipulators() {
    cout << "Gotham needs its " << boolalpha << true << " hero.";
    cout << "\nMark it " << noboolalpha << false << "!";
    cout << "\nThere are " << 69 << "," << oct << 105 << " leaves in here.";
    cout << "\nYabba " << hex << 3669732608 << "!";
    cout << "\nAvogadro's number: " << scientific << 6.0221415e23;
    cout << "\nHogwart's platform: " << fixed << setprecision(2) << 9.75123;
    cout << "\nAlways eliminate " << 3735929054;
    cout << setw(4) << "\n"
    << 0x1 << "\n"
    << 0x10 << "\n"
    << 0x100 << "\n"
    << 0x1000
    << endl;
}

void run_all_tests() {
    //run_test(test_insertion, "test_insertion");
    //run_test(test_chaining, "test_chaining");
    //run_test(test_extraction, "test_extraction");
    //run_test(test_status, "test_status");
    run_test(test_manipulators, "test_manipulators");
}

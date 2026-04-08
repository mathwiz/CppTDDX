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
#include <vector>
#include <deque>
#include <sstream>

#include "unit_test.h"

using namespace std;

using ostringstream = basic_ostringstream<char>;
using wostringstream = basic_ostringstream<wchar_t>;

template <typename T>
ostream& operator<<(ostream& s, vector<T> v) {
    s << "Size: " << v.size() << " Capacity: " << v.capacity() << " Elements:\n";
    for (const auto& element : v)
        s << element << "\n";
    return s;
}

template <typename T>
istream& operator>>(istream& s, deque<T>& t) {
    T element;
    while (s >> element)
        t.emplace_back(move(element));
    return s;
}

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

void test_insertion_user_defined() {
    const vector<string> characters{
        "Harry Potter", "Hermione Granger", "Ron Weasley", "Draco Malfoy"
    };
    cout << characters << endl;
    const vector<bool> bits{
        true, false, true,
    };
    cout << boolalpha << bits << endl;
}

void test_extraction_user_defined() {
    cout << "Enter integers separated by whitespace (RET and ctrl-D to end):\n";
    deque<int> numbers;
    cin >> numbers;
    int sum{};
    cout << "Cumulative sum:\n";
    for (const auto& element : numbers) {
        sum += element;
    }
    cout << sum << endl;
}

void test_output_string() {
    string s1("By Grabthar's hammer, ");
    string s2("by the suns of Worvan. ");
    string s3("You shall be avenged.");
    ostringstream ss;
    ss << s1 << s2 << s3;
    const auto lazarus = ss.str();
    assert_that(lazarus == s1.append(s2).append(s3), "1");

    string s4("I am Groot!");
    ss.str(s4);
    const auto groot = ss.str();
    assert_that(groot == s4, "2");
}

void run_all_tests() {
    //run_test(test_insertion, "test_insertion");
    //run_test(test_chaining, "test_chaining");
    //run_test(test_extraction, "test_extraction");
    //run_test(test_status, "test_status");
    //run_test(test_manipulators, "test_manipulators");
    //run_test(test_insertion_user_defined, "test_vector_user_defined");
    //run_test(test_extraction_user_defined, "test_extraction_user_defined");
    run_test(test_output_string, "test_output_string");
}

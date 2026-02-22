//
//  ch07.h
//  CppTDD
//
//  Created by Yohan Lee on 2/22/26.
//

#include <stdexcept>

struct CheckedInteger {
    CheckedInteger(unsigned int value) : value{ value } { }
    
    CheckedInteger operator+(unsigned int other) const {
        CheckedInteger result{ value + other };
        if (result.value < value) throw new std::runtime_error("Overflow!");
        return result;
    }

    const unsigned int value;
};

void ex7_2() {
    CheckedInteger x{ 1 };
    unsigned int y{ 2 };
    printf("Result: %d\n", (x + y).value);
}

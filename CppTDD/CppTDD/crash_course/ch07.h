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
        if (result.value < value) throw new std::overflow_error("Overflow!");
        return result;
    }

    const unsigned int value;
};


void ex7_2() {
    CheckedInteger x{ 1 };
    unsigned int y{ 2 };
    printf("Result: %d\n", (x + y).value);
}


void ex7_3() {
    CheckedInteger x{ 100 };
    unsigned int y{ 200 };
    auto max = std::numeric_limits<unsigned int>::max();
    auto sum = x + y;
    printf("%d + %d = %d\n", x.value, y, sum.value);
    try {
        auto c = x + max;
        printf("%d\n", c.value);
    } catch (...) {
        printf("(%d + %d) Exception: %s\n", x.value, max, "huh?");
    }
}

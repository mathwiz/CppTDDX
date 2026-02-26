//
//  ch08.h
//  CppTDD
//
//  Created by Yohan Lee on 2/26/26.
//

#include <cstdio>


void ex8_1() {
    int x{};
    ++x;
    42;
    printf("%d\n", x);
}


struct Tracer {
    Tracer(const char* name) : name{ name } {
        printf("Tracer %s constructed.\n", name);
    }
    ~Tracer() {
        printf("Tracer %s destructed.\n", name);
    }
private:
    const char* const name;
};


void ex8_2() {
    Tracer main{ "main" };
    {
        printf("Block a\n");
        Tracer first{ "a1" };
        Tracer second{ "a2" };
    }
    {
        printf("Block b\n");
        Tracer first{ "b1" };
        Tracer second{ "b2" };
    }
}


void randomize(uint32_t&);

void ex8_3() {
    size_t iterations{};
    uint32_t number{ 0x4c4347 };
    while (number != 0x474343 ) {
        randomize(number);
        ++iterations;
    }
    printf("%zd iterations\n", iterations);
}

void randomize(uint32_t& x) {
    x = 0x3fffffff & (0x41c64e6d * x + 12345) % 0x80000000;
}

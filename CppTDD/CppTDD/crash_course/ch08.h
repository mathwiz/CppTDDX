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

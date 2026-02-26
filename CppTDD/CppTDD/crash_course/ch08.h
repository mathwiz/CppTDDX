//
//  ch08.h
//  CppTDD
//
//  Created by Yohan Lee on 2/26/26.
//

#include <cstdio>
#include <cstdint>


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


struct RandomNumberGenerator {
    explicit RandomNumberGenerator(uint16_t seed)
    : iterations{}, number{ seed } {}
    uint16_t next();
    size_t get_iterations() const;
private:
    size_t iterations;
    uint16_t number;
};

void ex8_4() {
    RandomNumberGenerator rng{ 0752 };
    while (rng.next() != 0) {
        //do nothing
    }
    printf("%zd\n", rng.get_iterations());
}

uint16_t RandomNumberGenerator::next() {
    ++iterations;
    number = 0177 & (055 * number + 0123) % 256;
    return number;
}

size_t RandomNumberGenerator::get_iterations() const {
    return iterations;
}

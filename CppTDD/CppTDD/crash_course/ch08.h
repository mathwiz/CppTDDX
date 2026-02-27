//
//  ch08.h
//  CppTDD
//
//  Created by Yohan Lee on 2/26/26.
//

#include <cstdio>
#include <cstdint>
#include <stdexcept>


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


namespace Primate::Hominid {
enum class Australopithicus {
    animensis,
    afarensis,
    africanus,
    garhi,
};
enum class Homo {
    erectus,
    habilis,
    sapiens
};
}


void ex8_5() {
    const auto specimen{ Primate::Hominid::Homo::erectus };
    printf("Homo: %d\n", specimen);
    const auto specimen2{ Primate::Hominid::Australopithicus::animensis };
    printf("Australopithicus: %d\n", specimen2);
}


void ex8_6() {
    using Primate::Hominid::Homo;
    using Primate::Hominid::Australopithicus;
    const auto specimen{ Homo::habilis };
    printf("Homo: %d\n", specimen);
    const auto specimen2{ Australopithicus::afarensis };
    printf("Australopithicus: %d\n", specimen2);
}


void ex8_7() {
    using namespace Primate::Hominid;
    const auto specimen{ Homo::sapiens };
    printf("Homo: %d\n", specimen);
    const auto specimen2{ Australopithicus::africanus };
    printf("Australopithicus: %d\n", specimen2);
}


using String = const char[255];
using HominidH = Primate::Hominid::Homo;
using HominidA = Primate::Hominid::Australopithicus;

void ex8_8() {
    const auto my_specimen{ HominidA::afarensis };
    if (my_specimen == HominidA::afarensis) {
        String linean_name{ "Australopithicus afarensis" };
        printf("My specimen: %s\n", linean_name);
    }
}


template <typename To, typename From>
struct NarrowCaster {
    To cast(From value) {
        const auto converted = static_cast<To>(value);
        const auto backwards = static_cast<From>(converted);
        if (value != backwards) throw std::runtime_error{ "Narrowed!" };
        return converted;
    }
};

template <typename From>
using short_caster = NarrowCaster<short, From>;


void ex8_9() {
    try {
        short_caster<int> caster;
        const auto cyclic_short = caster.cast(142857);
        printf("cyclic_short: %d\n", cyclic_short);
    } catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }
}


struct TextFile {
    bool success;
    const char* data;
    size_t n_bytes;
};


TextFile read_text_file(const char* path) {
    const static char contents[]{ "Sometimes the goat is you." };
    return TextFile{
        true,
        contents,
        sizeof(contents)
    };
}

void ex8_11() {
    const auto [success, contents, length] = read_text_file("README.md");
    if (success) {
        printf("Read %zd bytes: %s\n", length, contents);
    } else {
        printf("How did you get here?");
    }
}

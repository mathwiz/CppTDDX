//
//  ch07.h
//  CppTDD
//
//  Created by Yohan Lee on 2/22/26.
//

#include <stdexcept>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <new>
#include <string>


struct CheckedInteger {
    CheckedInteger(unsigned int value) : value{ value } { }
    
    CheckedInteger operator+(unsigned int other) const {
        CheckedInteger result{ value + other };
        if (result.value < value) throw std::overflow_error("Overflow!");
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
    } catch (const std::overflow_error& e) {
        printf("(%d + %d) Exception: %s\n", x.value, max, e.what());
    }
}


struct Bucket {
    const static size_t data_size{ 4096 };
    std::byte data[data_size];
};

struct Heap {
    void* allocate(size_t bytes) {
        if (bytes > Bucket::data_size) throw std::bad_alloc();
        for (size_t i{}; i < n_heap_buckets; i++) {
            if (!bucket_used[i]) {
                bucket_used[i] = true;
                return buckets[i].data;
            }
        }
        throw std::bad_alloc();
    }
    
    void free(void* p) {
        for (size_t i{}; i < n_heap_buckets; i++) {
            if (buckets[i].data == p) {
                bucket_used[i] = false;
                return;
            }
        }
    }
    
    static const size_t n_heap_buckets{ 10 };
    Bucket buckets[n_heap_buckets]{};
    bool bucket_used[n_heap_buckets]{};
};


Heap heap;

void* operator new(size_t n_bytes) {
    return heap.allocate(n_bytes);
}

void operator delete(void* p) {
    return heap.free(p);
}


void ex7_6() {
    printf("Buckets:    %p\n", heap.buckets);
    auto breakfast = new unsigned int{ 0xC0FFEE };
    auto dinner = new unsigned int{ 0xDEADBEEF };
    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    printf("Dinner: %p 0x%x\n", dinner, *dinner);
    delete breakfast;
    delete dinner;
    try {
        while(true) {
            new char;
            printf("Allocated a char.\n");
        }
    } catch (const std::bad_alloc& e) {
        printf("std::bad_alloc caught.\n");
    }
}


struct Point {
    Point() : x{}, y{}, z{} {
        printf("Point at %p constructed.\n", this);
    }
    ~Point() {
        printf("Point at %p destructed.\n", this);
    }
    
    double x, y, z;
};


void ex7_7() {
    const auto point_size = sizeof(Point);
    std::byte data[3 * point_size];
    printf("Data starts at %p.\n", data);
    auto point1 = new(&data[0 * point_size]) Point{};
    auto point2 = new(&data[1 * point_size]) Point{};
    auto point3 = new(&data[2 * point_size]) Point{};
    point1->~Point();
    point2->~Point();
    point3->~Point();
}


void ex7_8() {
    //0b1111'1111'1 = 511
    unsigned int w = 0b1111'1111'1;
    printf("%d\n", w);
    uint8_t x = w; //255
    int8_t y = w;  //Implementation dependent
    printf("x = %u; y = %d\n", x, y);
}


void ex7_9() {
    double x = std::numeric_limits<float>::max();
    long double y = std::numeric_limits<double>::max();
    float z = std::numeric_limits<long double>::max();
    printf("x: %g \ny: %Lg \nz: %g\n", x, y, z);
}


void print_addr(void* x) {
    printf("%p\n", x);
}


void ex7_10() {
    int x{};
    print_addr(&x);
    print_addr(nullptr);
}


void ex7_11() {
    int32_t a = 100;
    int64_t b{ a };
    if (a == b) printf("Non-narrowing conversion.\n");
    //int32_t c{ b }; //compiler complains
}


void ex7_12() {
    int64_t b = std::numeric_limits<int64_t>::max();
    int32_t c(b); //narrowing conversion
    if (c != b) printf("Narrowing conversion.\n");
    printf("%lld\n%u\n", b, c);
}


void trainwreck(const char* read_only) {
    auto as_unsigned = (unsigned char*) read_only;
    *as_unsigned = 'b'; //Crash
}


void trainwreck2(const char* read_only) {
    //Does not compile
//    auto as_unsigned = reinterpret_cast<unsigned char*>(read_only);
//    *as_unsigned = 'b';
}


void ex7_13() {
    auto ezra = "Ezra";
    printf("Before trainwreck: %s\n", ezra);
    trainwreck(ezra);
    printf("After trainwreck: %s\n", ezra);
}


void ex7_14() {
    auto ezra = "Ezra";
    printf("Before trainwreck: %s\n", ezra);
    trainwreck2(ezra);
    printf("After trainwreck: %s\n", ezra);
}


struct ReadOnlyInt {
    ReadOnlyInt(int val) : val{ val } { }
    explicit operator int() const {
        return val;
    }
private:
    const int val;
};


void ex7_15() {
    ReadOnlyInt answer{ 42 };
    auto ten_answer = static_cast<int>(answer) * 10;
    printf("Ten answers = %d\n", ten_answer);
}


struct Color {
    std::string value() {
        return std::format("H={} S={} V={}", H, S, V);
    }
    float H, S, V;
};


constexpr uint8_t max(uint8_t a, uint8_t b) {
    return a > b ? a : b;
}

constexpr uint8_t max(uint8_t a, uint8_t b, uint8_t c) {
    return max(max(a, b), c);
}

constexpr uint8_t min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

constexpr uint8_t min(uint8_t a, uint8_t b, uint8_t c) {
    return min(min(a, b), c);
}

constexpr float modulo(float dividend, float divisor) {
    const auto quotient = dividend / divisor;
    return divisor * (quotient - static_cast<uint8_t>(quotient));
}


constexpr Color rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b) {
    Color c{};
    const float full = 255.0f;
    const auto c_max = max(r, g, b);
    c.V = c_max / full;
    
    const auto c_min = min(r, g, b);
    const auto delta = c.V - c_min / full;
    c.S = c_max == 0 ? 0 : delta / c.V;
    
    if (c_max == c_min) {
        c.H = 0;
        return c;
    }
    if (c_max == r) {
        c.H = (g / full - b / full) / delta;
    } else if (c_max == g) {
        c.H = (b / full - r / full) / delta + 2.0f;
    } else if (c_max == b) {
        c.H = (r / full - g / full) / delta + 4.0f;
    }
    c.H *= 60.0f;
    c.H = c.H >= 0.0f ? c.H : c.H + 360.0f;
    c.H = modulo(c.H, 360.0f);

    return c;
}


void ex7_17() {
    auto black   = rgb_to_hsv(0, 0, 0);
    auto white   = rgb_to_hsv(255, 255, 255);
    auto red     = rgb_to_hsv(255, 0, 0);
    auto green   = rgb_to_hsv(0, 255, 0);
    auto blue    = rgb_to_hsv(0, 0, 255);
    
    std::cout << black.value() << std::endl;
    std::cout << white.value() << std::endl;
    std::cout << red.value() << std::endl;
    std::cout << green.value() << std::endl;
    std::cout << blue.value() << std::endl;
}


int foo(volatile int& x) {
    x = 10;
    x = 20;
    auto y = x;
    y = x;
    return y;
}


void ex7_18() {
    int a{ 0 };
    printf("%d\n", foo(a));
}

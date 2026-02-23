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

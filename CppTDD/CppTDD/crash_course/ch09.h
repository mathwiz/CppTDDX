//
//  ch09.h
//  CppTDD
//
//  Created by Yohan Lee on 2/28/26.
//

#include <cstdio>
#include <cstdint>
#include <cstdarg>


struct BostonCorbett {
    virtual void shoot() final {
        printf("...God avenged Abraham Lincoln.\n");
    }
};


//No worky
//struct BostonCorbettJunior {
//    void shoot() override { }
//};


void ex9_1() {
    BostonCorbett senior;
    senior.shoot();
}


struct Distillate {
    int apply() volatile {
        return ++applications;
    }
private:
    int applications{};
};


void ex9_3() {
    volatile Distillate ethanol;
    printf("%d Tequila\n", ethanol.apply());
    printf("%d Tequila\n", ethanol.apply());
    printf("%d Tequila\n", ethanol.apply());
    printf("Floor!\n");
}


template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y) {
    return x + y;
}


void ex9_4() {
    auto my_double = add(100., -10);
    printf("decltype(double + int) = double: %f\n", my_double);
    auto my_uint = add(100U, -10);
    printf("decltype(uint + int) = uint: %u\n", my_uint);
    auto my_ulonglong = add(char{ 100 }, 11'222'999ull);
    printf("decltype(char + ulonglong) = ulonglong: %llu\n", my_ulonglong);
}


int sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    int result{};
    while (n--) {
        auto next_element = va_arg(args, int);
        result += next_element;
    }
    va_end(args);
    return result;
}


void ex9_5() {
    printf("Summing with explicit list size: %d.\n", sum(7, 1, 2, 3, 4, 5, 6, 7));
}


template <typename T>
constexpr T sum2(T x) {
    return x;
}

template <typename T, typename... Args>
constexpr T sum2(T x, Args... args) {
    return x + sum2(args...);
}


void ex9_8() {
    printf("Summing with recusion: %d.\n", sum2(1, 2, 3, 4, 5, 6, 7));
}


template <typename... T>
constexpr auto sum3(T... args) {
    return (... + args);
}


void ex9_9() {
    printf("Summing with fold: %d.\n", sum3(1, 2, 3, 4, 5, 6, 7));
}


float add(float a, float b) {
    return a + b;
}

float sub(float a, float b) {
    return a - b;
}


void ex9_10() {
    const float first{ 111 };
    const float second{ 222 };
    
    float(*op)(float, float) {};
    
    printf("op initialized to %p\n", op);
    
    //using address
    op = &add;
    printf("&add at %p\n", op);
    printf("%g + %g = %g\n", first, second, op(first, second));
    
    //using name
    op = sub;
    printf("&sub at %p\n", op);
    printf("%g - %g = %g\n", first, second, op(first, second));
}


struct CountIf {
    CountIf(char x) : x{ x } { }
    
    size_t operator()(const char* str) const {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == x) result++;
            index++;
        }
        return result;
    }
private:
    const char x;
};


void ex9_12() {
    CountIf s_counter{ 's' };
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    
    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
    
    CountIf f_counter{ 'f' };
    const char* buffalo_str =   "Buffalo buffalo Buffalo buffalo "
                                "Buffalo buffalo Buffalo buffalo ";
    auto buffalo = f_counter(buffalo_str);
    printf("%s f_counter: %zd\n", buffalo_str, buffalo);
}

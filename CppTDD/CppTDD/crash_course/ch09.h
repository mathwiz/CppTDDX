//
//  ch09.h
//  CppTDD
//
//  Created by Yohan Lee on 2/28/26.
//

#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <functional>


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


template <typename Fn>
void transform_using_lambda(Fn fn, const int* in, int* out, size_t length) {
    for (size_t i{}; i < length; i++) {
        out[i] = fn(in[i]);
    }
}


void ex9_15() {
    const size_t len{ 3 };
    int base[]{ 2, 4, 6 };
    int a[len], b[len], c[len];
    
    auto lambda1 = [](int x) { return x; };
    auto lambda2 = [](int x) { return 2 * x; };
    auto lambda3 = [](int x) { return x * x; };

    transform_using_lambda(lambda1, base, a, len);
    transform_using_lambda(lambda2, base, b, len);
    transform_using_lambda(lambda3, base, c, len);

    printf("Element 0: %d %d %d\n", a[0], b[0], c[0]);
    printf("Element 1: %d %d %d\n", a[1], b[1], c[1]);
    printf("Element 2: %d %d %d\n", a[2], b[2], c[2]);
}


void ex9_16() {
    auto incr_with_default = [](auto x, int y = 1) { return y + x; };
    printf("increment (10): %d\n", incr_with_default(10));
    printf("increment (10, 2): %d\n", incr_with_default(10, 2));
}


template <typename Fn, typename T>
void transform_using_generic_lambda(Fn fn, const T* in, T* out, size_t length) {
    for (size_t i{}; i < length; i++) {
        out[i] = fn(in[i]);
    }
}


void ex9_17() {
    const size_t len{ 3 };
    int base_int[]{ 2, 4, 6 };
    int a[len];
    float base_float[]{ 10.f, 20.f, 30.f };
    float b[len];

    auto translate = [](auto x) { return 10 * x + 5; };

    transform_using_generic_lambda(translate, base_int, a, len);
    transform_using_generic_lambda(translate, base_float, b, len);

    printf("Element 0: %d %f\n", a[0], b[0]);
    printf("Element 1: %d %f\n", a[1], b[1]);
    printf("Element 2: %d %f\n", a[2], b[2]);
}


void ex9_18() {
    char char_to_count{ 's' };
    auto s_counter = [char_to_count](const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == char_to_count) result++;
            index++;
        }
        return result;
    };
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    
    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
}


void ex9_19() {
    char char_to_count{ 's' };
    size_t ref_capture{};
    auto s_counter = [char_to_count, &ref_capture](const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == char_to_count) result++;
            index++;
        }
        ref_capture += result;
        return result;
    };
    
    printf("Tally ref capture: %zd\n", ref_capture);
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    printf("Tally ref capture: %zd\n", ref_capture);

    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
    printf("Tally ref capture: %zd\n", ref_capture);
}


void ex9_20() {
    char char_to_count{ 's' };
    size_t ref_capture{};
    printf("Default (unnamed) capture by reference.\n");
    auto s_counter = [&](const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == char_to_count) result++;
            index++;
        }
        ref_capture += result;
        return result;
    };
    
    printf("Tally ref capture: %zd\n", ref_capture);
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    printf("Tally ref capture: %zd\n", ref_capture);

    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
    printf("Tally ref capture: %zd\n", ref_capture);
}



void ex9_21() {
    char char_to_count{ 's' };
    printf("Default (unnamed) capture by value.\n");
    auto s_counter = [=](const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == char_to_count) result++;
            index++;
        }
        return result;
    };
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);

    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
}


void ex9_22() {
    char char_to_count{ 's' };
    size_t ref_capture{};
    printf("Default and named capture.\n");
    auto s_counter = [&, char_to_count](const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == char_to_count) result++;
            index++;
        }
        ref_capture += result;
        return result;
    };
    
    printf("Tally ref capture: %zd\n", ref_capture);
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    printf("Tally ref capture: %zd\n", ref_capture);

    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
    printf("Tally ref capture: %zd\n", ref_capture);
}


void ex9_23() {
    char char_to_count{ 's' };
    size_t ref_capture{};
    printf("Renaming capture.\n");
    auto s_counter = [&, the_char=char_to_count](const char* str) {
        size_t index{}, result{};
        while (str[index]) {
            if (str[index] == the_char) result++;
            index++;
        }
        ref_capture += result;
        return result;
    };
    
    printf("Tally ref capture: %zd\n", ref_capture);
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    printf("Tally ref capture: %zd\n", ref_capture);

    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
    printf("Tally ref capture: %zd\n", ref_capture);
}


struct LambdaFactory {
    LambdaFactory(char in) : to_count{ in }, tally{} { }
    
    auto make_lambda() {
        return [this](const char* str) {
            size_t index{}, result{};
            while (str[index]) {
                if (str[index] == to_count) result++;
                index++;
            }
            tally += result;
            return result;
        };
    }
    
    auto get_tally() { return tally; }
    
private:
    const char to_count;
    size_t tally;
};


void ex9_24() {
    char char_to_count{ 's' };
    printf("Capturing this.\n");
    LambdaFactory factory{ char_to_count };
    auto s_counter = factory.make_lambda();
    
    printf("Tally member variable: %zd\n", factory.get_tally());
    
    const char* sally_str = "Sally sells seashells by the seashore.";
    auto sally = s_counter(sally_str);
    printf("%s s_counter: %zd\n", sally_str, sally);
    printf("Tally member variable: %zd\n", factory.get_tally());

    const char* sailor_str = "Sailor went to the sea to see what he could see.";
    auto sailor = s_counter(sailor_str);
    printf("%s s_counter: %zd\n", sailor_str, sailor);
    printf("Tally member variable: %zd\n", factory.get_tally());
}


void ex9_25() {
    std::function<void()> fn;
    try {
        fn();
    } catch (const std::bad_function_call& e) {
        printf("%s\n", e.what());
    }
}

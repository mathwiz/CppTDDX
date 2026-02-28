//
//  ch09.h
//  CppTDD
//
//  Created by Yohan Lee on 2/28/26.
//

#include <cstdio>


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

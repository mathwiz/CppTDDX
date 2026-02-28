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

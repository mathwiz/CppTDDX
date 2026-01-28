//
//  ch04.h
//  CppTDD
//
//  Created by Yohan Lee on 1/28/26.
//

#include <cstdio>

static int rat_things_power = 200;

void power_up_rat_thing(int nuclear_isotopes) {
    rat_things_power = rat_things_power + nuclear_isotopes;
    const auto waste_heat = rat_things_power * 20;
    if (waste_heat > 10'000) {
        printf("Warning! Too darn hot!\n");
    }
}

void ex4_2() {
    printf("Rat-thing power %d\n", rat_things_power);
    power_up_rat_thing(100);
    printf("Rat-thing power %d\n", rat_things_power);
    power_up_rat_thing(500);
    printf("Rat-thing power %d\n", rat_things_power);
}

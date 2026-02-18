//
//  ch06.h
//  CppTDD
//
//  Created by Yohan Lee on 2/18/26.
//

#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <utility>

int carbon_thaw(const int& encased_solo) {
    //encased_solo++;
    auto& hibernation_sick_solo = const_cast<int&>(encased_solo);
    return ++hibernation_sick_solo;
}

void ex6_3() {
    printf("carbon_thaw %d\n", carbon_thaw(999));
}


short increment_as_short(void* target) {
    auto as_short = static_cast<short*>(target);
    *as_short = *as_short + 1;
    return *as_short;
}


void ex6_4() {
    short beast{ 665 };
    auto mark_of_the_beast = increment_as_short(&beast);
    printf("%d is the mark of the beast\n", mark_of_the_beast);
}


void ex6_5() {
    auto timer = reinterpret_cast<const unsigned long*>(0x1000);
    printf("Timer is %lu\n", *timer); //expect a crash unless 0x1000 is readable
}

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

void ex6_1() {
    printf("carbon_thaw %d\n", carbon_thaw(999));
}

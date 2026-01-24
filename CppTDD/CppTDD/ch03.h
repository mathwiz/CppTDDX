//
//  ch03.h
//  CppTDD
//
//  Created by Yohan Lee on 1/24/26.
//

#include <cstdio>

void ex3_1() {
    int gettysburg{1863};
    printf("gettysburg: %d\n", gettysburg);
    int *gettysburg_address = &gettysburg;
    printf("&gettysburg: %p\n", gettysburg_address);
}



void ex3_2() {
    int gettysburg{1863};
    int *gettysburg_address = &gettysburg;
    printf("Value at gettysburg_address: %d\n", *gettysburg_address);
    printf("gettysburg_address: %p\n", gettysburg_address);
    *gettysburg_address = 90210;
    printf("Value at gettysburg_address: %d\n", *gettysburg_address);
    printf("gettysburg_address: %p\n", gettysburg_address);
}


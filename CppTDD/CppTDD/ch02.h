//
//  ch02.h
//  CppTDD
//
//  Created by Yohan Lee on 1/21/26.
//

#include <cstdio>


void ex2_1() {
    unsigned short a = 0b10101010;
    printf("%hu\n", a);
    int b = 0123;
    printf("%d\n", b);
    unsigned long long d = 0xFFFFFFFFFFFFFFFF;
    printf("%llu\n", d);
}


void ex2_2() {
    unsigned int a = 3669732608;
    printf("Yabba %x!\n", a);
    unsigned int b = 69;
    printf("There are %u, %o leaves here.\n", b, b);
}

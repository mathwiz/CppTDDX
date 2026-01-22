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
    unsigned long long d = 0xFFFF'FFFF'FFFF'FFFF; // commenting quote marks
    printf("%llu\n", d);
}


void ex2_2() {
    unsigned int a = 3'669'732'608;
    printf("Yabba %x!\n", a);
    unsigned int b = 69;
    printf("There are %u, %o leaves here.\n", b, b);
}


void ex2_3() {
    double a = 6.022'140'76e23;
    printf("Avogadro's number: %le %lf %lg\n", a, a, a);
    float b = 22.0/7;
    printf("Nearly Pi: %e %f %g\n", b, b, b);
}


void ex2_4() {
    char a = 'M';
    wchar_t b = L'Z';
    printf("Chars surrounded by single quote: '%c' '%lc'\n", a, b);
}


void ex2_5() {
    bool a = true;
    bool b = false;
    printf("Booleans: %d %d\n", a, b);
}


void ex2_6() {
    int a = 10;
    int b = 20;
    printf("%d\n", a == b);
    printf("%d\n", a != b);
    printf("%d\n", a <= b);
    printf("%d\n", a < b);
    printf("%d\n", a >= b);
    printf("%d\n", a > b);
}


void ex2_7() {
    bool a = true;
    bool b = false;
    printf("%d\n", ! b);
    printf("%d\n", a && b);
    printf("%d\n", a && !b);
    printf("%d\n", a || b);
    printf("%d\n", !a || b);
}


void ex2_8() {
    size_t size_type;
    size_type = sizeof(char);
    printf(" char: %zd\n", size_type);
    size_type = sizeof(short);
    printf("short: %zd\n", size_type);
    size_type = sizeof(int);
    printf("  int: %zd\n", size_type);
    size_type = sizeof(long);
    printf(" long: %zd\n", size_type);
    size_type = sizeof(long long);
    printf("llong: %zd\n", size_type);
}

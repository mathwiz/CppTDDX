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


void void_return() {
    printf("No return type\n");
    return ex2_8();
}


void ex2_9() {
    int arr[] = {1,2,3,4};
    printf("The third element is %d\n", arr[2]);
    arr[2] = (int)'T';
    printf("The third element is %d\n", arr[2]);
}


void ex2_10() {
    short arr[] = { 10, 20, 13, 4, 0 };
    unsigned short max = 0;
    size_t n = sizeof(arr) / sizeof(short);
    printf("elements: %lu\n", n);
    for(size_t i=0; i<n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    printf("The max element is %d\n", max);
}


void ex2_11() {
    unsigned long arr[] = { 10, 20, 13, 40, 100 };
    unsigned long max = 0;
    for(unsigned long i : arr) {
        if (i > max) max = i;
    }
    printf("The max element is %lu\n", max);
}


void ex2_12() {
    char alphabet[27];
    alphabet[26] = 0;
    for(int i=0; i<26; i++) {
        alphabet[i] = i + 97;
    }
    printf("%s\n", alphabet);
    for(int i=0; i<26; i++) {
        alphabet[i] = i + 65;
    }
    printf("%s\n", alphabet);
}


enum class Race {
    Dinan,
    Teklan,
    Ivyn,
    Moiran,
    Camite,
    Julian,
    Aidan
};


void ex2_15() {
    Race race = Race::Aidan;
    switch(race) {
        case Race::Dinan: {
            printf("Dinan");
        } break;
        case Race::Teklan: {
            printf("Teklan");
        } break;
        case Race::Ivyn: {
            printf("Ivyn");
        } break;
        case Race::Moiran: {
            printf("Mairan");
        } break;
        case Race::Camite: {
            printf("Camite");
        } break;
        case Race::Julian:
        case Race::Aidan: {
            printf("%d", race);
        } break;
        default: {
            printf("Error: unknown race!");
        }
    }
    printf("\n");
}


struct Book {
    char name[256];
    int year;
    int pages;
    bool hardcover;
};

void ex2_16() {
    Book b;
    b.name[0] = 'X';
    b.name[1] = 'O';
    b.pages = 271;
    b.hardcover = false;
    printf("%s is a %d page book which is a hardcover (Y=1, N=0): %d\n",
           b.name,
           b.pages,
           b.hardcover);
}


union Variant {
    char string[10];
    int integer;
    double floating_point;
};

void ex2_18() {
    Variant v;
    v.integer = 42;
    printf("Union integer: %d\n", v.integer);
    v.floating_point = 1.0 / 11;
    printf("Union floating_point: %f\n", v.floating_point);
    printf("Union integer: %d\n", v.integer);
}


struct ClockOfTheLongNow {
    ClockOfTheLongNow() {
    }
    ClockOfTheLongNow(int y) {
        if(!set_year(y)) {
            year = DEFAULT * -1;
        }
    }
    void add_year() {
        year++;
    }
    bool set_year(int new_year) {
        if (new_year < 2026) return false;
        year = new_year;
        return true;
    }
    int get_year() {
        return year;
    }
private:
    int DEFAULT = 2000;
    int year = DEFAULT;
};

void ex2_19() {
    ClockOfTheLongNow clock;
    clock.set_year(2026);
    printf("year: %d\n", clock.get_year());
    clock.set_year(2025);
    printf("year: %d\n", clock.get_year());
    clock.add_year();
    printf("year: %d\n", clock.get_year());
}


void ex2_21() {
    ClockOfTheLongNow clock;
    if(!clock.set_year(2025)) {
        clock.set_year(2026);
    }
    printf("year: %d\n", clock.get_year());
    clock.add_year();
    printf("year: %d\n", clock.get_year());
}


void ex2_22() {
    ClockOfTheLongNow clock;
    printf("year: %d\n", clock.get_year());
}


void ex2_23() {
    ClockOfTheLongNow clock;
    printf("year: %d\n", clock.get_year());
    ClockOfTheLongNow clock1{2020};
    printf("year: %d\n", clock1.get_year());
    ClockOfTheLongNow clock2{2026};
    printf("year: %d\n", clock2.get_year());
    ClockOfTheLongNow clock3(2027);
    printf("year: %d\n", clock3.get_year());
}


struct PodStruct {
    int a{-1};
    char b[256]{'a', 'b', 'c'};
    bool c{true};
};

void ex2_24() {
    PodStruct pod1{};
    PodStruct pod2 = {};
    PodStruct pod3{ 42, "Hi" };
    PodStruct pod4{ 43, "Hello", false };
    printf("POD %d '%s' %d\n", pod1.a, pod1.b, pod1.c);
    printf("POD %d '%s' %d\n", pod2.a, pod2.b, pod2.c);
    printf("POD %d '%s' %d\n", pod3.a, pod3.b, pod3.c);
    printf("POD %d '%s' %d\n", pod4.a, pod4.b, pod4.c);
}


struct Taxonomist {
    Taxonomist() {
        printf("(no arg)\n");
    }
    Taxonomist(char x) {
        printf(" char: %c\n", x);
    }
    Taxonomist(int x) {
        printf("  int: %d\n", x);
    }
    Taxonomist(float x) {
        printf("float: %f\n", x);
    }
};

void ex2_25() {
    Taxonomist tax1;
    Taxonomist tax2 = { 'c' };
    Taxonomist tax3{ 42 };
    Taxonomist tax4{ 6.02e23f };
    Taxonomist tax5{ 'g' };
    Taxonomist tax6{ 'l' };
    Taxonomist tax7{};
    Taxonomist tax8();
}

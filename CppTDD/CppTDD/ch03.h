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

void ex3_3() {
    ClockOfTheLongNow clock{};
    ClockOfTheLongNow* clock_ptr = &clock;
    printf("Clock address: %p\n", clock_ptr);
    printf("Clock year: %d\n", clock_ptr->get_year());
    clock_ptr->set_year(2026);
    printf("Clock year: %d\n", clock_ptr->get_year());
}

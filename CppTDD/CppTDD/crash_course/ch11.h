//
//  ch11.h
//  CppTDD
//
//  Created by Yohan Lee on 3/23/26.
//

#include "unit_test.h"

void set_up() {
}

void run_all_tests() {
    set_up();
    run_test(set_up, "nil");
}

void ex11_all() {
    run_all_tests();
}

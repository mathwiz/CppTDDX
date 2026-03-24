//
//  ch11.h
//  CppTDD
//
//  Created by Yohan Lee on 3/23/26.
//

#include <memory>

#include "unit_test.h"


struct DeadMenOfDunharrow {
    DeadMenOfDunharrow(const char* m="")
    : message{ m } {
        oaths_to_fulfill++;
    }
    
    ~DeadMenOfDunharrow() {
        oaths_to_fulfill--;
    }
    
    const char* message;
    static int oaths_to_fulfill;
};

int DeadMenOfDunharrow::oaths_to_fulfill{};

using UniqueOathbreakers = std::unique_ptr<DeadMenOfDunharrow>;



void implicit_bool_conversion() {
    
}

// * Testing * //

void set_up() {
    auto my_ptr = std::make_unique<int>(808);
    std::unique_ptr<int> my_ptr2{ new int{ 811 } };
}

void run_all_tests() {
    set_up();
    run_test(implicit_bool_conversion, "implicit_bool_conversion");
}

void ex11_all() {
    run_all_tests();
}

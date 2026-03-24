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

void bool_conversion_when_full() {
    UniqueOathbreakers aragorn{ new DeadMenOfDunharrow{} };
    assert_that(static_cast<bool>(aragorn), "pointer exists");
}

void bool_conversion_when_empty() {
    UniqueOathbreakers aragorn;
    assert_that(!static_cast<bool>(aragorn), "pointer does not exist");
}

void raii_wrapper() {
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 0, "zero before;");
    UniqueOathbreakers aragorn{ new DeadMenOfDunharrow{} };
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 1, "now one");
    UniqueOathbreakers legolas{ new DeadMenOfDunharrow{} };
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 2, "now two?");
}

void pointer_semantics() {
    auto message = "The way is shut";
    UniqueOathbreakers aragorn{ new DeadMenOfDunharrow{ message } };
    assert_that((*aragorn).message == message, "operator*");
    assert_that((aragorn)->message == message, "operator->");
    assert_that(aragorn.get() != nullptr, "get()");
    UniqueOathbreakers legolas{};
    assert_that(legolas == nullptr, "empty");
}

void swapping() {
    auto message1 = "First";
    auto message2 = "Second";
    UniqueOathbreakers aragorn{ new DeadMenOfDunharrow{ message1 } };
    UniqueOathbreakers legolas{ new DeadMenOfDunharrow{ message2 }};
    aragorn.swap(legolas);
    assert_that(legolas->message = message1, "second after swap");
    assert_that(aragorn->message = message2, "first after swap");
}

void reset() {
    auto message = "Weird, it is";
    UniqueOathbreakers aragorn{ new DeadMenOfDunharrow{ } };
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 1, "now one");
    aragorn.reset();
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 0, "back to zero?");
    auto new_dead_men = new DeadMenOfDunharrow{ message };
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 1, "back to one?");
    aragorn.reset(new_dead_men);
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 1, "why still one?");
    assert_that(aragorn->message = new_dead_men->message, "why?");
    assert_that(aragorn.get() == new_dead_men, "get()");
}

void exclusive_ownership() {
    
}

// * Testing * //

void set_up() {
    auto my_ptr = std::make_unique<int>(808);
    std::unique_ptr<int> my_ptr2{ new int{ 811 } };
}

void run_all_tests() {
    set_up();
    run_test(bool_conversion_when_full, "bool_conversion_when_full");
    run_test(bool_conversion_when_empty, "bool_conversion_when_empty");
    run_test(raii_wrapper, "raii_wrapper");
    run_test(pointer_semantics, "pointer_semantics");
    run_test(swapping, "swapping");
    run_test(reset, "reset");
    run_test(exclusive_ownership, "exclusive_ownership");
}

void ex11_all() {
    run_all_tests();
}

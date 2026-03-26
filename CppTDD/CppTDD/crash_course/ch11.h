//
//  ch11.h
//  CppTDD
//
//  Created by Yohan Lee on 3/23/26.
//

#include <cstdio>
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
using SharedOathbreakers = std::shared_ptr<DeadMenOfDunharrow>;

using FileGuard = std::unique_ptr<FILE, int(*)(FILE*)>;

void say_hello(FileGuard file) {
    fprintf(file.get(), "HELLO DAVE");
}

int file_handles() {
    auto file = fopen("HAL9000", "w");
    if (!file) return errno;
    FileGuard file_guard{ file, fclose };
    say_hello(std::move(file_guard));
    return 0;
}

// * Testing * //


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
    auto aragorn = std::make_unique<DeadMenOfDunharrow>();
    auto son_of_aragorn{ std::move(aragorn) };
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 1, "one");
}

void assignment() {
    auto aragorn = std::make_unique<DeadMenOfDunharrow>();
    auto son_of_aragorn = std::make_unique<DeadMenOfDunharrow>();
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 2, "now two");
    son_of_aragorn = std::move(aragorn);
    assert_that(DeadMenOfDunharrow::oaths_to_fulfill == 1, "back to one");
}

void unique_arrays() {
    std::unique_ptr<int[]> squares{ new int[5]{ -1, 4, 9, 16, 25 } };
    squares[0] = 1;
    assert_that(squares[0] == 1, "index 0");
    assert_that(squares[1] == 4, "index 1");
    assert_that(squares[2] == 9, "index 2");
}

void deleters() {
    auto my_deleter = [](int* x) {
        printf("Deleting an int at %p.\n", x);
        delete x;
    };
    std::unique_ptr<int, decltype(my_deleter)> my_up {
        new int,
        my_deleter
    };
}


void set_up() {
    auto u_ptr = std::make_unique<int>(808);
    std::unique_ptr<int> u_ptr2{ new int{ 811 } };
    auto s_ptr = std::make_shared<int>(808);
    std::shared_ptr<int> s_ptr2{ new int{ 811 } };
    std::shared_ptr<int> shared_with_constructor_deleter_allocator{
        new int{ 10 },
        [](int* x) { delete x; },
        std::allocator<int>{}
    };
    auto shared_with_custom_allocator =
    std::allocate_shared<int>(std::allocator<int>{}, 10);
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
    run_test(assignment, "assignment");
    run_test(unique_arrays, "unique_arrays");
    run_test(deleters, "deleters");
}

void ex11_all() {
    run_all_tests();
}

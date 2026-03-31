//
//  ch12.h
//  CppTDD
//
//  Created by Yohan Lee on 3/26/26.
//

#include <optional>

#include "unit_test.h"


struct TheMatrix {
    TheMatrix(int x) : iteration { x } { }
    const int iteration;
};

enum Pill { Red, Blue };

std::optional<TheMatrix> take(Pill pill) {
    if (pill == Pill::Blue) return TheMatrix{ 3 };
    return std::nullopt;
}

struct Socialite { const char* name; };

struct Valet { const char* name; };

Socialite bertie{ "Wilberforce" };
Valet reginald{ "Jeeves" };


// * testing * //

void test_optional() {
    if (auto matrix_opt = take(Pill::Blue)) {
        assert_that(matrix_opt->iteration == 3, "optional ref");
        auto& matrix = matrix_opt.value();
        assert_that(matrix.iteration == 3, "optional value");
    } else {
        assert_that(false, "optional unexpectly null");
    }
    
    auto matrix_opt = take(Pill::Red);
    assert_that(matrix_opt == std::nullopt, "optional ref");
    if (matrix_opt) {
        printf("should never get here...attempting invalid optional access\n");
        matrix_opt.value();
    }
}


void test_pair() {
    std::pair<Socialite, Valet> inimitable_duo{ bertie, reginald };
    assert_that(inimitable_duo.first.name == bertie.name, "first");
    assert_that(inimitable_duo.second.name == reginald.name, "second");

    auto& [master, servant] = inimitable_duo;
    assert_that(master.name == bertie.name, "structured binding 1");
    assert_that(servant.name == reginald.name, "structured binding 2");
}

void set_up() {

}

void run_all_tests() {
    run_test(test_optional, "test_optional");
    run_test(test_pair, "test_pair");
}

void ex12_all() {
    run_all_tests();
}

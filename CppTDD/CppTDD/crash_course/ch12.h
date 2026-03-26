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


// * testing * //

void optional() {
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

void set_up() {
    
}

void run_all_tests() {
    run_test(optional, "optional");
}

void ex12_all() {
    run_all_tests();
}

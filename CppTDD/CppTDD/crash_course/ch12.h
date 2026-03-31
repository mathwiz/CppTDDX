//
//  ch12.h
//  CppTDD
//
//  Created by Yohan Lee on 3/26/26.
//

#include <optional>
#include <any>
#include <variant>

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

struct Acquaintance { const char* name; };

Socialite bertie{ "Wilberforce" };
Valet reginald{ "Jeeves" };
Acquaintance tuppence{ "Hildebrand" };

struct EscapeCapsule {
    EscapeCapsule(double x) : weight_kg{ x } { }
    double weight_kg;
};

struct BugblatterBeast {
    BugblatterBeast() : is_ravenous{ true }, weight_kg{ 20'000 } { }
    bool is_ravenous;
    double weight_kg;
};


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

void test_tuple() {
    using Trio = std::tuple<Socialite, Valet, Acquaintance>;
    Trio truculent_trio{ bertie, reginald, tuppence };

    auto& bertie_ref = std::get<0>(truculent_trio);
    assert_that(bertie_ref.name == bertie.name, "bertie");

    auto& tuppy_ref = std::get<Acquaintance>(truculent_trio);
    assert_that(tuppy_ref.name == tuppence.name, "bertie");
}

void test_any() {
    std::any my_any;
    my_any.emplace<EscapeCapsule>(600);
    auto capsule = std::any_cast<EscapeCapsule>(my_any);
    assert_value(capsule.weight_kg, 600.0, 0.01, "double comparison");
    try {
        std::any_cast<double>(my_any);
        assert_that(false, "should not get here");
    } catch (std::bad_any_cast e) {
        assert_that(true, "expected exception");
    }
}

void test_variant() {
    std::variant<BugblatterBeast, EscapeCapsule> my_variant;
    assert_that(my_variant.index() == 0, "index 0 exists");
    
    my_variant.emplace<EscapeCapsule>(600);
    auto capsule = std::get<EscapeCapsule>(my_variant);
    assert_value(capsule.weight_kg, 600.0, 0.01, "double comparison");
    assert_value(std::get<1>(my_variant).weight_kg, 600.0, 0.01, "double comparison");

    try {
        std::get<0>(my_variant);
        assert_that(false, "should not get here");
    } catch (std::bad_variant_access e) {
        assert_that(true, "expected exception");
    }
    
    auto lbs = std::visit([](auto& x) { return 2.2 * x.weight_kg; }, my_variant);
    assert_value(lbs, 1320.0, 0.01, "apply callable to variant");
}

void set_up() {

}

void run_all_tests() {
    run_test(test_optional, "test_optional");
    run_test(test_pair, "test_pair");
    run_test(test_tuple, "test_tuple");
    run_test(test_any, "test_any");
    run_test(test_variant, "test_variant");
}

void ex12_all() {
    run_all_tests();
}

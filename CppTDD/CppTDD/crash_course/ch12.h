//
//  ch12.h
//  CppTDD
//
//  Created by Yohan Lee on 3/26/26.
//

#include <optional>
#include <any>
#include <variant>
#include <chrono>
#include <thread>
#include <complex>
#include <random>
#include <limits>
#include <ratio>

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

struct Stopwatch {
    Stopwatch(std::chrono::nanoseconds& result)
    : result{ result },
    start{ std::chrono::high_resolution_clock::now() } { }
    
    ~Stopwatch() {
        result = std::chrono::high_resolution_clock::now() - start;
    }
private:
    std::chrono::nanoseconds& result;
    const std::chrono::time_point<std::chrono::high_resolution_clock> start;
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
    assert_that(my_variant.index() == 0, "index 0");
    
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

void test_chrono() {
    auto sys_now = std::chrono::system_clock::now();
    auto hi_res_now = std::chrono::high_resolution_clock::now();
    auto steady_now = std::chrono::steady_clock::now();
    assert_that(sys_now.time_since_epoch().count() > 0, "system clock");
    assert_that(hi_res_now.time_since_epoch().count() > 0, "high resolution clock");
    assert_that(steady_now.time_since_epoch().count() > 0, "steady clock");
    
    using namespace std::literals::chrono_literals;
    auto one_s = std::chrono::seconds(1);
    auto thousands_ms = 1000ms;
    assert_that(one_s == thousands_ms, "chrono literals");
    
    auto billion_ns_as_s = duration_cast<std::chrono::seconds>(2'000'000'000ns);
    assert_that(billion_ns_as_s.count() == 2, "duration cast");
}

void test_sleep() {
    using namespace std::literals::chrono_literals;
    
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(100ms);
    auto end = std::chrono::system_clock::now();
    assert_that(end - start >= 100ms, "time delay");
}

void test_stopwatch() {
    const size_t n = 1'000'000;
    std::chrono::nanoseconds elapsed;
    {
        Stopwatch stopwatch{ elapsed };
        volatile double result{ 1.23e45 };
        for (double i = 1; i < n; i++) {
            result /= i;
        }
    }
    auto time_per_division = elapsed.count() / double{ n };
    printf("Took %gns per division.\n", time_per_division);
}

void test_complex() {
    using cmplx = std::complex<double>;
    cmplx a{0.5, 14.13};
    assert_value(std::real(a), 0.5, 0.00001, "real");
    assert_value(std::imag(a), 14.13, 0.00001, "imaginary");
}

void test_pseudorandom() {
    //Mersenne twister is consistent for seed
    std::mt19937 mt_engine{ 91586 };
    printf("%d\n", mt_engine());
    printf("%d\n", mt_engine());
    printf("%d\n", mt_engine());
}

void test_random() {
    std::random_device rd_engine{};
    printf("%d\n", rd_engine());
}

void test_randomdist() {
    std::mt19937_64 mt_engine{ 102787 };
    std::uniform_int_distribution<int> int_d{ 0, 10 };
    const size_t n{ 32 };
    for (size_t i{}; i < n; i++) {
        printf("%d ", int_d(mt_engine));
    }
    printf("\n");
}

void test_limits() {
    auto lim = std::numeric_limits<int>::min();
    printf("  minimum: %d\n", lim);
    printf("underflow: %d\n", lim - 1);
}

void test_ratio() {
    using a = std::ratio<3, 4>;
    using b = std::ratio<6, 12>;
    using c = std::ratio_multiply<a, b>;
    assert_that(c::num == 3, "numerator");
    assert_that(c::den == 8, "denominator");
}

void set_up() {
}

void run_all_tests() {
    run_test(test_optional, "test_optional");
    run_test(test_pair, "test_pair");
    run_test(test_tuple, "test_tuple");
    run_test(test_any, "test_any");
    run_test(test_variant, "test_variant");
    run_test(test_chrono, "test_chrono");
    run_test(test_sleep, "test_sleep");
    //run_test(test_stopwatch, "test_stopwatch");
    run_test(test_complex, "test_complex");
    //run_test(test_pseudorandom, "test_pseudorandom");
    //run_test(test_random, "test_random");
    //run_test(test_randomdist, "test_randomdist");
    //run_test(test_limits, "test_limits");
    run_test(test_ratio, "test_ratio");
}

void ex12_all() {
    run_all_tests();
}

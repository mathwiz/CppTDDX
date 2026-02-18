//
//  ch06.h
//  CppTDD
//
//  Created by Yohan Lee on 2/18/26.
//

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <utility>

int carbon_thaw(const int& encased_solo) {
    //encased_solo++;
    auto& hibernation_sick_solo = const_cast<int&>(encased_solo);
    return ++hibernation_sick_solo;
}

void ex6_3() {
    printf("carbon_thaw %d\n", carbon_thaw(999));
}


short increment_as_short(void* target) {
    auto as_short = static_cast<short*>(target);
    *as_short = *as_short + 1;
    return *as_short;
}


void ex6_4() {
    short beast{ 665 };
    auto mark_of_the_beast = increment_as_short(&beast);
    printf("%d is the mark of the beast\n", mark_of_the_beast);
}


void ex6_5() {
    auto timer = reinterpret_cast<const unsigned long*>(0x1000);
    //expect a crash unless 0x1000 is readable
    //printf("Timer is %lu\n", *timer);
}


template <typename To, typename From>
To narrow_cast(From value) {
    const auto converted = static_cast<To>(value);
    const auto backwards = static_cast<From>(converted);
    if (value != backwards) throw std::runtime_error{ "Narrowed!" };
    return converted;
}


void ex6_7() {
    int perfect{ 496 };
    const auto perfect_short = narrow_cast<short>(perfect);
    printf("perfect_short: %d\n", perfect_short);
    try {
        int cyclic{ 142857 };
        const auto cyclic_short = narrow_cast<short>(cyclic);
        printf("cyclic_short: %d\n", cyclic_short);
    } catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }
}


double double_mean(const double* values, size_t length) {
    double result{};
    for(size_t i{}; i<length; i++) {
        result += values[i];
    }
    return result / length;
}

void ex6_8() {
    const double vals[] = { 1.5, 2, 3, 4, 5, 6 };
    printf("Mean is: %f\n", double_mean(vals, 6));
}


template<typename T>
T mean(const T* values, size_t length) {
    T result{};
    for(size_t i{}; i<length; i++) {
        result += values[i];
    }
    return result / length;
}


void ex6_11() {
    const double nums_d[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
    const auto result1 = mean<double>(nums_d, 6);
    printf("double: %f\n", result1);
    
    const float nums_f[] { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    const auto result2 = mean<float>(nums_f, 6);
    printf("float: %f\n", result2);

    const size_t nums_c[] { 1, 2, 3, 4, 5, 6 };
    const auto result3 = mean<size_t>(nums_c, 6);
    printf("size_t: %zd\n", result3);
}


void ex6_13() {
    printf("Using type inference\n");
    const double nums_d[] { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
    const auto result1 = mean(nums_d, 6);
    printf("double: %f\n", result1);
    
    const float nums_f[] { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    const auto result2 = mean(nums_f, 6);
    printf("float: %f\n", result2);

    const size_t nums_c[] { 1, 2, 3, 4, 5, 6 };
    const auto result3 = mean(nums_c, 6);
    printf("size_t: %zd\n", result3);
}

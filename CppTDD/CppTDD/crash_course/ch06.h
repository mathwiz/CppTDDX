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
#include <type_traits>
#include <numeric>
#include <vector>
#include <iostream>
#include <concepts>


template <typename X, typename Y, typename Z>
struct MyTemplateClass {
    X foo(Y&);
private:
    Z* member;
};


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


template <typename T>
struct SimpleUniquePointer {
    SimpleUniquePointer() = default;
    
    SimpleUniquePointer(T* pointer)
      : pointer{ pointer } {}
    
    ~SimpleUniquePointer() {
        if(pointer)
            delete pointer;
    }
  
    SimpleUniquePointer(const SimpleUniquePointer&) = delete;
  
    SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;
  
    SimpleUniquePointer(SimpleUniquePointer&& other) noexcept
      : pointer{ other.pointer } {
          other.pointer = nullptr;
    }
  
    SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept {
        if(pointer)
            delete pointer;
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    T* get() {
        return pointer;
    }

private:
    T* pointer;
};


struct Tracer {
    Tracer(const char* name) : name{ name } {
        printf("%s constructed.\n", name);
    }

    ~Tracer() {
        printf("%s destructed.\n", name);
    }
    
private:
    const char* const name;
};


void consumer(SimpleUniquePointer<Tracer> consumer_ptr) {
    printf("(cons) consumer_ptr: 0x%p\n", consumer_ptr.get());
}


void ex6_15() {
    auto ptr_a = SimpleUniquePointer(new Tracer{ "ptr_a" });
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
    consumer(std::move(ptr_a));
    printf("Now a nullptr after destruction.\n");
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
}


template <typename T>
T square(T x) {
    return x * x;
}

void ex6_17() {
    double d{ 67.0 };
    auto result1 = square(d);
    printf("Square: %f\n", result1);
    int i{ 6 };
    auto result2 = square(i);
    printf("Square: %d\n", result2);
    char c{ 'Q' };
    printf("No way! Must support operator '*'\n");
//    auto result3 = square(&c);
//    printf("Square: %s\n", result3);
}


constexpr const char* as_str(bool x) {
    return x ? "True" : "False";
}

void ex6_18() {
    printf("%s\n", as_str(std::is_integral<int>::value));
    printf("%s\n", as_str(std::is_integral<const int>::value));
    printf("%s\n", as_str(std::is_integral<char>::value));
    printf("%s\n", as_str(std::is_integral<uint64_t>::value));
    printf("%s\n", as_str(std::is_integral<int&>::value));
    printf("%s\n", as_str(std::is_integral<int*>::value));
    printf("%s\n", as_str(std::is_integral<float>::value));
}


/*
 * Usage: template <Averageable T>
 *        T mean(const T* values, size_t length) {
 *
 template <typename T>
 concept Averageable =
     std::is_default_constructible<T>::value &&
     std::is_copy_constructible<T>::value &&
     requires(T a, T b) {
     { a + b } -> T;
     { a / b } -> T;
   };
*/

/*
 * Examples from https://www.cppstories.com/2021/concepts-intro/
 */
template <class T>
concept integral = std::is_integral_v<T>;


template <typename T>
concept ILabel = requires(T v)
{
    {v.buildHtml()} -> std::convertible_to<std::string>;
};


template <typename T>
requires std::integral<T> || std::floating_point<T>
constexpr double Average(std::vector<T> const &vec) {
    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}

void concept_example() {
    std::vector ints { 1, 2, 3, 4, 5, 6, 17};
    std::cout << Average(ints) << '\n';
}


template<typename T>
requires std::is_copy_constructible_v<T>
T get_copy(T* pointer) {
    if(!pointer) throw new std::runtime_error("Null pointer");
    return *pointer;
}

struct Highlander {
    Highlander() = default;
    Highlander(const Highlander&) = delete;
};


void ex6_28() {
    Highlander conor;
    auto conor_ptr = &conor;
    printf("Pointer: %d\n", conor_ptr);
    //does not compile
    //auto conor_copy = get_copy(conor_ptr);
}

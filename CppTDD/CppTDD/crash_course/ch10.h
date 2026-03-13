//
//  ch10.h
//  CppTDD
//
//  Created by Yohan Lee on 3/12/26.
//

#include "unit_test.h"


struct SpeedUpdate {
    double velocity_mps;
};

struct CarDetected {
    double distance_m;
    double velocity_mps;
};

struct BrakeCommand {
    double time_to_collision_s;
};

struct ServiceBus {
    void publish(const BrakeCommand&);
};

template <typename T>
struct AutoBrake {
    AutoBrake(const T& publish) :
    speed_mps{},
    collision_threshold_s{ 5 },
    publish{ publish } { }
    void observe(const SpeedUpdate&) { }
    void observe(const CarDetected&) { }
    void set_collision_threshold_s(double s) {
        collision_threshold_s = s;
    }
    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {
        return speed_mps;
    }
private:
    double collision_threshold_s;
    double speed_mps;
    const T& publish;
};


// * Test set up * //

AutoBrake default_auto_brake{ [](const BrakeCommand&) {} };


// * Test functions * //

void test_initial_speed_is_zero() {
    assert_that(default_auto_brake.get_speed_mps() == 0L, "speed not equal to 0");
}

void test_initial_sensitivity_is_five() {
    assert_that(default_auto_brake.get_collision_threshold_s() == 5L, "initial sensitivity is not 5");
}

void run_all_tests() {
    run_test(test_initial_speed_is_zero, "initial speed is zero");
    run_test(test_initial_sensitivity_is_five, "initial sensitivity is five");
}


// * Examples * //

void ex10_5() {
    assert_that(2 + 2 == 4, "so true!");
    assert_that(2 + 2 == 5, "no sir!");
}

void ex10_6() {
    test_initial_speed_is_zero();
}

void ex10_8() {
    run_all_tests();
}

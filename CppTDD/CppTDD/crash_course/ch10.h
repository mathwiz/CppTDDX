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
    
    void observe(const SpeedUpdate& x) {
        speed_mps = x.velocity_mps;
    }
    
    
    void observe(const CarDetected&) { }
    void set_collision_threshold_s(double s) {
        if (s < 1) throw std::runtime_error{ "collision_threshold less than 1" };
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

void set_up() {
}

void test_initial_speed_is_zero() {
    assert_that(default_auto_brake.get_speed_mps() == 0L, "speed not equal to 0");
}

void test_initial_sensitivity_is_five() {
    assert_that(default_auto_brake.get_collision_threshold_s() == 5L, "initial sensitivity is not 5");
}

void test_sensitivity_greater_than_one() {
    try {
        default_auto_brake.set_collision_threshold_s(0.5L);
    } catch (const std::exception&) {
        return;
    }
    assert_that(false, "no exception thrown");
}

void test_speed_is_saved() {
    default_auto_brake.observe(SpeedUpdate{ 100L });
    assert_that(100L == default_auto_brake.get_speed_mps(), "speed not saved to 100");
    default_auto_brake.observe(SpeedUpdate{ 50L });
    assert_that(50L == default_auto_brake.get_speed_mps(), "speed not saved to 50");
    default_auto_brake.observe(SpeedUpdate{ 0L });
    assert_that(0L == default_auto_brake.get_speed_mps(), "speed not saved to 0");
}

void run_all_tests() {
    set_up();
    run_test(test_initial_speed_is_zero, "initial speed is 0");
    run_test(test_initial_sensitivity_is_five, "initial sensitivity is 5");
    run_test(test_sensitivity_greater_than_one, "sensitivity greater than 1");
    run_test(test_speed_is_saved, "speed is saved");
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

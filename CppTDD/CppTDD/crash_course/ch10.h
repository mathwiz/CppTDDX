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
    AutoBrake(const T& publish) : publish{ publish } { }
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


void test_initial_speed_is_zero() {
    AutoBrake auto_brake{ [](const BrakeCommand&) {} };
    assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal to zero");
}


void ex10_5() {
    assert_that(2 + 2 == 4, "so true!");
    assert_that(2 + 2 == 5, "no sir!");
}

void ex10_6() {
    test_initial_speed_is_zero();
}

void ex10_7() {
    run_test(test_initial_speed_is_zero, "initial speed is zero");
}

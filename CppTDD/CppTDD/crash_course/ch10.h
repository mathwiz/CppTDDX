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


using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;

struct IServiceBus {
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&) = 0;
    virtual void subscribe(SpeedUpdateCallback) = 0;
    virtual void subscribe(CarDetectedCallback) = 0;
};


struct AutoBrake {
    AutoBrake(IServiceBus& bus) :
    speed_mps{},
    collision_threshold_s{ 5 }
    {
        bus.subscribe([this](const SpeedUpdate& update) {
            speed_mps = update.velocity_mps;
        });
        bus.subscribe([this, &bus](const CarDetected& update) {
            const auto relative_velocity_mps = speed_mps - update.velocity_mps;
            const auto time_to_collision_s = update.distance_m / relative_velocity_mps;
            if (time_to_collision_s > 0 &&
                time_to_collision_s <= collision_threshold_s) {
                bus.publish(BrakeCommand{ time_to_collision_s });
            }
        });
    }
    
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
};



struct MockServiceBus : IServiceBus {
    void publish(const BrakeCommand& cmd) override {
        commands_published++;
        last_command = cmd;
    }
    
    void subscribe(SpeedUpdateCallback callback) override {
        su_callback = callback;
    }
    
    void subscribe(CarDetectedCallback callback) override {
        cd_callback = callback;
    }
    
    BrakeCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback su_callback;
    CarDetectedCallback cd_callback;
};


// * Test set up * //


// * Test functions * //

void set_up() {
}

void test_initial_speed_is_zero() {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
    assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal to 0");
}

void test_initial_sensitivity_is_five() {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
    assert_that(auto_brake.get_collision_threshold_s() == 5L, "initial sensitivity is not 5");
}

void test_sensitivity_greater_than_one() {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
    try {
        auto_brake.set_collision_threshold_s(0.5L);
    } catch (const std::exception&) {
        return;
    }
    assert_that(false, "no exception thrown");
}

void test_speed_is_saved() {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
    bus.su_callback(SpeedUpdate{ 100L });
    assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");
    bus.su_callback(SpeedUpdate{ 50L });
    assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");
    bus.su_callback(SpeedUpdate{ 0L });
    assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
}

void test_alert_when_imminent() {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
    auto_brake.set_collision_threshold_s(10L);
    bus.su_callback(SpeedUpdate{ 100L });
    bus.cd_callback(CarDetected{ 99L, 0L });
    assert_that(bus.commands_published == 1, "brake commands published not equal to 1");
}

void test_no_alert_when_not_imminent() {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };
    auto_brake.set_collision_threshold_s(2L);
    bus.su_callback(SpeedUpdate{ 100L });
    bus.cd_callback(CarDetected{ 999L, 50L });
    assert_that(bus.commands_published == 0, "brake commands published not equal to 0");
}

void run_all_tests() {
    set_up();
    run_test(test_initial_speed_is_zero, "initial speed is 0");
    run_test(test_initial_sensitivity_is_five, "initial sensitivity is 5");
    run_test(test_sensitivity_greater_than_one, "sensitivity greater than 1");
    run_test(test_speed_is_saved, "speed is saved");
    run_test(test_alert_when_imminent, "alert when imminent");
    run_test(test_no_alert_when_not_imminent, "no alert when not imminent");
}


// * Examples * //

void ex10_5() {
    assert_that(2 + 2 == 4, "so true!");
    assert_that(2 + 2 == 5, "no sir!");
}

void ex10_6() {
    test_initial_speed_is_zero();
}

void ex10_all() {
    run_all_tests();
}

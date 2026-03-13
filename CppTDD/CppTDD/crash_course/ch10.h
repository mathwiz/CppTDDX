//
//  ch10.h
//  CppTDD
//
//  Created by Yohan Lee on 3/12/26.
//


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

void ex10_8() {
    
}

//
//  ch04.h
//  CppTDD
//
//  Created by Yohan Lee on 1/28/26.
//

#include <cstdio>
#include <cstring>
#include <stdexcept>


static int rat_things_power = 200;

void power_up_rat_thing(int nuclear_isotopes) {
    rat_things_power = rat_things_power + nuclear_isotopes;
    const auto waste_heat = rat_things_power * 20;
    if (waste_heat > 10'000) {
        printf("Warning! Too darn hot!\n");
    }
}

void ex4_2() {
    printf("Rat-thing power %d\n", rat_things_power);
    power_up_rat_thing(100);
    printf("Rat-thing power %d\n", rat_things_power);
    power_up_rat_thing(500);
    printf("Rat-thing power %d\n", rat_things_power);
}


void power_up_rat_thing2(int nuclear_isotopes) {
    static int local_rat_things_power = 200;
    local_rat_things_power = local_rat_things_power + nuclear_isotopes;
    const auto waste_heat = local_rat_things_power * 20;
    if (waste_heat > 1e4) {
        printf("Warning! Again, too hot!\n");
    }
    printf("Rat-thing power %d\n", local_rat_things_power);
}

void ex4_3() {
    power_up_rat_thing2(100);
    power_up_rat_thing2(500);
}


struct RatThing {
    static int rat_things_power;
    static void power_up_rat_thing(int nuclear_isotopes) {
        rat_things_power = rat_things_power + nuclear_isotopes;
        const auto waste_heat = rat_things_power * 20;
        if (waste_heat > 1e4) {
            printf("Warning! Yet again, too hot!\n");
        }
        printf("Rat-thing power %d\n", rat_things_power);
    }
};

int RatThing::rat_things_power = 200;


void ex4_4() {
    RatThing::power_up_rat_thing(100);
    RatThing::power_up_rat_thing(500);
}


struct Tracer {
    Tracer(const char* n) : name{n} {
        printf("%s constructed.\n", name);
    }
    ~Tracer() {
        printf("%s destructed.\n", name);
    }
private:
    const char* const name;
};

static Tracer t1{"Static variable"};
thread_local Tracer t2{"Thread-local variable"};

void ex4_6() {
    printf("A\n");
    Tracer t3{"Automatic variable"};
    printf("B\n");
    const auto* t4 = new Tracer{"Dynamic variable"};
    printf("C\n");
    delete t4;
}


struct Groucho {
    void forget(int x) {
        if (x == 0xFACE) {
            throw std::runtime_error("I saw a 0xFACE!\n");
        }
        printf("Forgot 0x%x\n", x);
    }
};

void ex4_9() {
    Groucho groucho;
    try {
        groucho.forget(0xC0DE);
        groucho.forget(0xFACE);
        groucho.forget(0xC0FFEE);
    } catch (const std::runtime_error& e) {
        printf("runtime exception: %s \n", e.what());
    }
}


struct CyberdyneSeries800 {
    CyberdyneSeries800() {
        printf("I'm a friend of Sarah Conner.");
    }
    ~CyberdyneSeries800() {
        throw std::runtime_error("It is bad to throw from a destructor.");
    }
};

void ex4_13() {
    try {
        CyberdyneSeries800 t800;
        throw std::runtime_error("Come with me if you want to live.");
    } catch(const std::exception& e) {
        printf("Caught: %s\n", e.what());
    }
}


struct SimpleString {
    SimpleString(size_t max)
    : max_size{ max },
      length{} {
        if (max_size == 0) {
            throw std::runtime_error{ "Max size must be at least 1." };
        }
        buffer = new char[max_size];
        buffer[0] = 0;
    }
    
    SimpleString(const SimpleString& other)
    : max_size{ other.max_size },
      buffer{ new char[other.max_size] },
    length { other.length } {
        std::strncpy(buffer, other.buffer, max_size);
    }
    
    ~SimpleString() {
        delete[] buffer;
    }
    
    void print(const char* tag) const {
        printf("%s: %s", tag, buffer);
    }
    
    bool append_line(const char* x) {
        const auto x_len = strlen(x);
        if (x_len + length + 2 > max_size) return false;
        std::strncpy(buffer + length, x, max_size - length);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    }
private:
    size_t max_size;
    char* buffer;
    size_t length;
};

void ex4_16() {
    SimpleString string{ 115 };
    string.append_line("Starbuck, whaddya hear?");
    string.append_line("Nothin' but the rain.");
    string.print("A: ");
    string.append_line("Grab your gun and bring the cat in.");
    string.append_line("Aye-aye sir, coming home.");
    string.print("B: ");
    if (!string.append_line("Galactic!")) {
        printf("String was not big enough to append another message.");
    }
}


struct SimpleStringOwner {
    SimpleStringOwner(const char* x) :
    string{ 10 } {
        if (!string.append_line(x)) {
            throw std::runtime_error{ "Not enough memory!"};
        }
        string.print("Constructed: ");
    }
    ~SimpleStringOwner() {
        string.print("About to destroy: ");
    }
private:
    SimpleString string;
};

void ex4_19() {
    SimpleStringOwner x{ "x" };
    printf("x is alive\n");
}


void fn_c() {
    try {
        SimpleStringOwner c{ "cccccccccc" };
    } catch(const std::exception& e) {
        printf("Caught in fc_c: %s\n", e.what());
        throw e;
    }
}

void fn_b() {
    SimpleStringOwner b{ "b" };
    fn_c();
}

void ex4_21() {
    try {
        SimpleStringOwner a{ "a" };
        fn_b();
        SimpleStringOwner d{ "d" };
    } catch(const std::exception& e) {
        printf("Caught at top of stack: %s\n", e.what());
    }
}


struct HumptyDumpty {
    HumptyDumpty() {}
    bool is_together_again() {
        return is_together;
    }
    bool is_together;
};

struct Result {
    HumptyDumpty hd;
    bool success;
};

Result make_humpty() {
    HumptyDumpty hd{};
    bool is_valid{true};
    // Check that hd is valid and set is_valid
    return { hd, is_valid };
}

bool send_kings_horses_and_men() {
    auto [hd, success] = make_humpty();
    if (!success) return false;
    //Class invariants of hd are now guaranteed.
    hd.is_together = true;
    printf("HumptyDumpty is together again: %d\n", hd.is_together_again());
    return true;
}

void ex4_22() {
    send_kings_horses_and_men();
}


int add_one_to(int x) {
    x++;
    return x;
}

void ex4_23() {
    auto original = 1;
    auto result = add_one_to(original);
    printf("Original: %d; Result: %d\n", original, result);
}


struct Point {
    int x, y;
};

Point make_transpose(Point p) {
    int tmp = p.x;
    p.x = p.y;
    p.y = tmp;
    return p;
}

void ex4_26() {
    SimpleString a{ 50 };
    a.append_line("We apologize for the");
    SimpleString a_copy{ a };
    a.append_line("inconvenience.");
    a_copy.append_line("ignorance.");
    a.print("a");
    a_copy.print("a_copy");
}

void invoke_copy_constructor(SimpleString s) {
    s.append_line("This change is lost");
}

void ex4_27() {
    SimpleString a{ 20 };
    invoke_copy_constructor(a);
    a.print("Still empty");
}


void ex4_28() {
    SimpleString a{ 50 };
    a.append_line("Bad use of copy assignment.");
    SimpleString b{ 50 };
    b.append_line("My buffer is not deleted when I'm clobbered.");
    b = a;
    b.print("b");
}

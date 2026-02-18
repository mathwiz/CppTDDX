//
//  ch05.h
//  CppTDD
//
//  Created by Yohan Lee on 2/16/26.
//

#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <utility>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transaction(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    void log_transaction(long from, long to, double amount) override {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct FileLogger : Logger {
    void log_transaction(long from, long to, double amount) override {
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

enum class LoggerType {
    Console,
    File
};

struct Bank {
    Bank() : type { LoggerType::Console } { }
    
    void set_logger(LoggerType new_type) {
        type = new_type;
    }
    
    void make_transfer(long from, long to, double amount) {
        switch(type) {
            case LoggerType::Console: {
                consoleLogger.log_transaction(from, to, amount);
                break;
            }
            case LoggerType::File: {
                fileLogger.log_transaction(from, to, amount);
                break;
            }
            default: {
                throw std::logic_error("Unknown logger type encountered.");
            }
        }
    }
private:
    LoggerType type;
    FileLogger fileLogger;
    ConsoleLogger consoleLogger;
};


void ex5_1() {
    Bank bank;
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.40);
}


void ex5_2() {
    Bank bank;
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.40);
    bank.set_logger(LoggerType::File);
    bank.make_transfer(3000, 2000, 75.00);
}


struct BaseClass {
    int the_answer() const { return 42; }
    virtual const char* message() const {
        return "I am the BaseClass";
    }
    
    const char* member = "gold";
private:
    const char* holistic_detective = "Dirk Gently";
};

struct DerivedClass : BaseClass {
    const char* message() const override {
        return "I am the DerivedClass";
    }
};


void ex5_6() {
    DerivedClass x;
    printf("The answer: %d\n", x.the_answer());
    printf("The member: %s\n", x.member);
    //does not compile
    //printf("The holistic_detective: %s\n", x.holistic_detective);
}


void ex5_7() {
    BaseClass base;
    DerivedClass derived;
    BaseClass& baseRef = derived;
    printf("BaseClass: %s\n", base.message());
    printf("DerivedClass: %s\n", derived.message());
    printf("BaseClass ref: %s\n", baseRef.message());
}


struct BaseClass2 {
    int the_answer() const { return 42; }
    virtual const char* message() const = 0;
    
    const char* member = "gold";
private:
    const char* holistic_detective = "Dirk Gently";
};

struct DerivedClass2 : BaseClass2 {
    const char* message() const override {
        return "I am the DerivedClass2";
    }
};


void ex5_8() {
    // Not instantiable
    //BaseClass2 base;
    DerivedClass2 derived;
    BaseClass2& baseRef = derived;
    printf("DerivedClass2: %s\n", derived.message());
    printf("BaseClass2 ref: %s\n", baseRef.message());
}


struct BaseClass3 {
};

struct DerivedClass3 : BaseClass3 {
    DerivedClass3() {
        printf("DerivedClass3() invoked\n");
    }
    ~DerivedClass3() {
        printf("~DerivedClass3() invoked\n");
    }
};


void ex5_9() {
    printf("Constructing DerievedClass3\n");
    BaseClass3* baseRef{ new DerivedClass3() };
    printf("Deleting as a BaseClass3*\n");
    delete baseRef;
    printf("No destructor call\n");
}


struct BaseClass4 {
    virtual ~BaseClass4() = default;
};

struct DerivedClass4 : BaseClass4 {
    DerivedClass4() {
        printf("DerivedClass4() invoked\n");
    }
    ~DerivedClass4() {
        printf("~DerivedClass4() invoked\n");
    }
};


void ex5_10() {
    printf("Constructing DerievedClass4\n");
    BaseClass4* baseRef{ new DerivedClass4() };
    printf("Deleting as a BaseClass4*\n");
    delete baseRef;
}

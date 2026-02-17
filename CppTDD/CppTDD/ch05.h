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


struct ConsoleLogger {
    void log_transaction(long from, long to, double amount) {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct FileLogger {
    void log_transaction(long from, long to, double amount) {
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

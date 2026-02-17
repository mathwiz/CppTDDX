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
        printf("%ld -> %ld: %f\n", from, to, amount);
    }
};

struct Bank {
    void make_transfer(long from, long to, double amount) {
        logger.log_transaction(from, to, amount);
    }
    ConsoleLogger logger;
};

void ex5_1() {
    Bank bank;
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.40);
}

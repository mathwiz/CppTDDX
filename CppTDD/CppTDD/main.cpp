//
//  main.cpp
//  CppTDD
//
//  Created by Yohan Lee on 1/19/26.
//

#include <iostream>

#include "ch15.h"

int handle_args(int argc, const char * argv[]);


int main(int argc, const char * argv[]) {
    handle_args(argc, argv);
    run_all_tests();
    return EXIT_SUCCESS;
}

int handle_args(int argc, const char * argv[]) {
    using std::cout;
    using std::endl;
    cout << "Arguments: " << argc << endl;
    for (size_t i{}; i < argc; i++) {
        cout << argv[i];
        cout << endl;
    }
    return 0;
}

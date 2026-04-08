//
//  ch17.h
//  CppTDD
//
//  Created by Yohan Lee on 4/8/26.
//

#include <string>
#include <filesystem>
#include <iostream>

#include "unit_test.h"

using namespace std;
using namespace std::filesystem;

void test_path() {
    path empty;
    path shadow{ "/etc/shadow" };
    assert_that(empty.empty(), "1");
    assert_that(shadow == std::string{ "/etc/shadow" }, "2");
}

void test_path_decomposition() {
    const path kernel32{ "/Windows/System32/kernel32.dll" };
    cout
    << "Root name: " << kernel32.root_name()
    << "\nRoot directory: " << kernel32.root_directory()
    << "\nRoot path: " << kernel32.root_path()
    << "\nRelative path: " << kernel32.relative_path()
    << "\nParent path: " << kernel32.parent_path()
    << "\nFilename: " << kernel32.filename()
    << "\nStem: " << kernel32.stem()
    << "\nExtension: " << kernel32.extension()
    << endl;
}

void run_all_tests() {
    run_test(test_path, "test_path");
    run_test(test_path_decomposition, "test_path_decomposition");
}


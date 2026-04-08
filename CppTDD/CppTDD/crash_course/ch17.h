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

void test_path_modification() {
    path my_path{ R"(C:/Windows/System32/kernel32.dll)" };
    cout << my_path << endl;
    my_path.make_preferred();
    cout << my_path << endl;
    my_path.replace_filename("wind32kfull.sys");
    cout << my_path << endl;
    my_path.remove_filename();
    cout << my_path << endl;
    my_path.clear();
    cout << "Is empty: " << boolalpha << my_path.empty() << endl;
}

void test_path_composition() {
    try {
        const auto temp = temp_directory_path();
        const auto rel = relative(temp);
        cout << boolalpha
        << "Temporary dir path: " << temp
        << "\nTemporary dir absolute: " << temp.is_absolute()
        << "\nCurrent path: " << current_path()
        << "\nTemporary dir's relative path: " << rel
        << "\nRelative dir absolute: " << rel.is_absolute()
        << "\nChanging current dir to temp.";
        
        current_path(temp);
        cout << "\nCurrent dir: " << current_path() << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what();
    }
}

void run_all_tests() {
    //run_test(test_path, "test_path");
    //run_test(test_path_decomposition, "test_path_decomposition");
    //run_test(test_path_modification, "test_path_modification");
    run_test(test_path_composition, "test_path_composition");
}


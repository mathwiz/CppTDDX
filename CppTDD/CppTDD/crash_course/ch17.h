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
using namespace std::chrono;

void describe(const path& p) {
    cout << boolalpha << "Path: " << p << endl;
    try {
        cout << "Is directory: " << is_directory(p) << endl;
        cout << "Is regular file: " << is_regular_file(p) << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

void write_info(const path& p) {
    if (!exists(p)) {
        cout << p << " does not exist." << endl;
        return;
    }
    const auto last_write = last_write_time(p).time_since_epoch();
    const auto in_hours = duration_cast<hours>(last_write).count();
    cout << p << "\t" << in_hours << "\t" << file_size(p) << endl;
}

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

void test_path_inspection() {
    path win_path{ R"(C:/Windows/System32/kernel32.dll)" };
    describe(win_path);
    win_path.remove_filename();
    describe(win_path);
    
    path nix_path{ R"(/bin/bash)" };
    describe(nix_path);
    nix_path.remove_filename();
    describe(nix_path);
}

void test_path_manipulation() {
    path win_path{ R"(C:/Windows/System32/kernel32.dll)" };
    describe(win_path);
    win_path.remove_filename();
    describe(win_path);
    
    path nix_path{ R"(/bin/bash)" };
    describe(nix_path);
    nix_path.remove_filename();
    describe(nix_path);
}

void test_path_manipulation2() {
    const path win_path{ R"(./CppTDD)" };
    const auto readme_path = temp_directory_path() / "REAMDE";
    try {
        write_info(win_path);
        write_info(readme_path);

        cout
        << "Copying " << win_path.filename()
        << " to " << readme_path.filename()
        << endl;
        copy_file(win_path, readme_path);
        write_info(readme_path);

        cout
        << "Resizing " << readme_path.filename()
        << endl;
        resize_file(readme_path, 1024);
        write_info(readme_path);

        cout
        << "Removing " << readme_path.filename()
        << endl;
        remove(readme_path);
        write_info(readme_path);

    } catch (const exception& e) {
        cerr << "Error: " << e.what();
    }
}

void run_all_tests() {
    //run_test(test_path, "test_path");
    //run_test(test_path_decomposition, "test_path_decomposition");
    //run_test(test_path_modification, "test_path_modification");
    //run_test(test_path_composition, "test_path_composition");
    //run_test(test_path_inspection, "test_path_inspection");
    //run_test(test_path_manipulation, "test_path_manipulation");
    run_test(test_path_manipulation2, "test_path_manipulation2");
}


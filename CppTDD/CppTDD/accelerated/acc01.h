//
//  acc01.h
//  CppTDD
//
//  Created by Yohan Lee on 2/19/26.
//

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int FrameInput()
{
    cout << "Please enter your first name: ";
    string name; //define name
    cin >> name; //read into name
    
    //build the message that we intend to write
    const string greeting = "Greetings, " + name + "!";
    
    //build the second and fourth lines of the output
    const string spaces(greeting.size(), ' ');
    const string second = "* " + spaces + " *";
    
    //build the first and fifth lines of the output
    const string first(second.size(), '*');
    
    //write it all
    cout << endl;
    cout << first << endl;
    cout << second << endl;
    cout << "* " << greeting << " *" << endl;
    cout << second << endl;
    cout << first << endl;
    return 0;
}

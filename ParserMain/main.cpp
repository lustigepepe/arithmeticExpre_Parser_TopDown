//
//  main.cpp
//  Parser Task
//
//  Created by soWhat on 13.02.18.
//  Copyright © 2018 soWhat. All rights reserved.
//


#include "parser.hpp"

int main(int argc, const char * argv[])
{
    Parser pa;
    string inputStr;
    cout << "Please enter your arithmetic expressions: " << endl;
    getline(cin, inputStr);

    pa.threadAlloc(inputStr);
    cout << "------------------------" << endl;

    if(!pa.checkInput())
        return 0;
    
    if(pa.inputExist())
        cout << "The outcome is : " << pa.parseTDown() << endl;
    else
        cout << "The outcome is : " << 0 << endl;
    return 0;
}

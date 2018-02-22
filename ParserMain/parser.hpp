//
//  parser.hpp
//  Parser Task
//
//  Created by soWhat on 21.02.18.
//  Copyright © 2018 soWhat. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include "breakpoint.hpp"

using namespace std;

class Parser
{
    
    char * input = nullptr;
    int among = 0;
    char operant = '+';
    char preOperant = '+';
    int rememberTerm = 0;
    vector<BrackPoint> brack;
    void allocPoiStr(string& inputStr);
    void recognizeOperator(char temp, char secSign, bool& isInt);
    void operation(char temp, char secSign, bool& isInt);


public:
    Parser() = default;
    bool opValid(char ch);
    bool plusMinus(char ch);
    bool checkInput();
    void dissolveBrackets(BrackPoint& first, BrackPoint& second);
    char get();
    void raise();
    int parseTDown();
    bool inputExist();
    void threadAlloc(string& inputStr);
};

#endif /* parser_hpp */

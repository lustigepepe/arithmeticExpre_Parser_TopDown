//
//  parser.cpp
//  Parser Task
//
//  Created by soWhat on 21.02.18.
//  Copyright © 2018 soWhat. All rights reserved.
//

#include "parser.hpp"
#include <thread>

void Parser::allocPoiStr(string& inputStr)
{
    inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), ' '),
                   inputStr.end());
    auto toPointer = make_unique<char[]>(inputStr.length());
    strcpy(toPointer.get(), inputStr.c_str());
    input = toPointer.get();
}

void Parser::threadAlloc(string& inputStr)
{
    // because without thread allocPointStr is asynchrone
    // and then it's need a timeout
    thread alloc([&]{this->allocPoiStr(inputStr);});
    alloc.join();
}


bool Parser::opValid(const char ch)
{
    if(ch == '+'|| ch == '-' || ch == '/'|| ch == '*'|| ch == '(' || ch == ')')
        return true;
    return false;
}

bool Parser::plusMinus(const char ch)
{
    if(ch == '-' || ch == '+')
        return true;
    return false;
}

bool Parser::checkInput()
{
    char charOne;
    char charNext;
    int numberCount = 0;
    int len = (int)strlen(input);
    bool isSign = false;
    
    for(int i = 0; i < len; ++i)
    {
        charOne = input[i];
        charNext = input[i+1];
        int intOne = charOne-'0';
        int intNext = charNext-'0';
        
        if(intOne > -1 && intOne < 10)
        {
            if(intNext > -1 && intNext < 10)
            {
                cout << "literal is too large" << endl;
                return false;
            }
            numberCount++;
        }
        else
        if(!opValid(charOne))
        {
            cout << "sign is not valid" << endl;
            return false;
        }
        else
        if(!isSign && plusMinus(charOne))
            isSign = true;
    }
    
    if(numberCount == 1 && isSign)
    {
        cout << "sign is just a unary literal" << endl;
        return false;
    }
    return true;
}
void Parser::dissolveBrackets(BrackPoint& first, BrackPoint& second)
{
    if(first.operant == '*')
    {
        first.among = first.among * second.among;
    }
    else
    if(first.operant == '/')
    {
        first.among = first.among / second.among;
    }
    else
    if(first.operant == '+')
    {
        first.among += second.among;
    }
    else
    if(first.operant == '-')
        first.among -= second.among;
    first.operant = '+';
}

char Parser::get()
{
    return *input;
}

void Parser::raise()
{
    ++input;
}

void Parser::operation(const char temp,
                       const char secSign,
                       bool& isInt)
{
    if(isInt && operant == '+')
    {
        if(preOperant == '*')
        {
            among *= (temp - '0');
        }
        else
        if(preOperant == '/')
        {
            among /= (temp - '0');
        }
        else
            among += (temp - '0');
    }
    else
    if(isInt && operant == '-')
    {
        if(preOperant == '*')
        {
            among = among *- (temp - '0');
        }
        else
        if(preOperant == '/')
        {
            among = among /- (temp - '0');
        }
        else
            among -= (temp - '0');
        operant = '+';
        preOperant = '+';
    }
    else
    if(isInt && operant == '/')
    {
        among /= (temp - '0');
        operant = '+';
    }
    else
        if(isInt && operant == '*')
        {
            among *= (temp - '0');
            operant = '+';
        }
    
}
void Parser::recognizeOperator(const char temp,
                               const char secSign,
                               bool& isInt)
{
    if(temp == '+')
    {
        if(operant == '*')
        {
            operant = '*';
        }
        else
        if(operant == '/')
        {
            operant = '/';
        }
        else
        if(operant == '-')
        {
            operant = '-';
        }
        else
            operant = '+';
    }
    else
    if(temp == '-')
    {
        if(operant == '*')
        {
            preOperant = '*';
            operant = '-';
        }
        else
        if(operant == '/')
        {
            preOperant = '/';
            operant = '-';
        }
        else
        if(operant == '-')
        {
            operant = '+';
            preOperant = '+';
        }
        else
            operant = '-';
        }
        else
        if(temp == '/')
        {
            operant = '/';
        }
        else
        if(temp == '*')
        {
            operant = '*';
        }
        else
        if(temp == '(')
        {
            BrackPoint br;
            br.among = among;
            br.operant = operant;
            brack.push_back(br);
            
            among = 0;
            operant = '+';
            preOperant = '+';
        }
        else
        if(temp == ')')
        {
            int count = 0;
            while(true) {
                if(input[count] == ')')
                    count++;
                else
                    break;
            }
            BrackPoint br;
            br.among = among;
            br.operant = operant;
            br.preOperant = preOperant;
            brack.push_back(br);
            for (int i = count; i > 0; --i)
            {
                int size = (int)brack.size();
                dissolveBrackets(brack[size-2], brack[size-1]);
                brack.pop_back();
            }
            among = brack.back().among;
            operant = brack.back().operant;
            preOperant = brack.back().preOperant;
            brack.pop_back();
            
        }
        else
        {
        isInt = true;
        rememberTerm++;
        if (rememberTerm == 2)
        {
            if(secSign == '*' || secSign == '/')
            {
                if(!(operant == '*' || operant == '/' || preOperant == '*' || preOperant == '/'))
                {
                    if (operant == '+' || operant == '-')
                    {
                        BrackPoint bp;
                        bp.among = among;
                        bp.operant = operant;
                        brack.push_back(bp);
                        operant = '+';
                        among = 0;
                    }
                }
            }
            rememberTerm = 1;
        }
    }
}

int Parser::parseTDown()
{
    char temp = get();
    char secSign = *(input+1);
    bool isInt = false;

    recognizeOperator(temp, secSign, isInt);
    operation(temp, secSign, isInt);
    if(*(input+1) != '\0')
    {
        raise();
        parseTDown();
    }
    else
    {
        if(brack.size() > 0)
        {
            BrackPoint br;
            br.among = among;
            br.operant = operant;
            brack.push_back(br);
            int size = (int)brack.size();
            for (int i = size; i > 1; --i) {
                dissolveBrackets(brack[i - 2], brack[i - 1]);
                brack.pop_back();
            }
            among = brack.front().among;
        }
    }
    return among;
}

bool Parser::inputExist()
{
    if(strlen(input) > 0)
        return true;
    return false;
}

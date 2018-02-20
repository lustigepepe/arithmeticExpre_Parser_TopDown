//
//  main.cpp
//  Parser Task
//
//  Created by soWhat on 13.02.18.
//  Copyright © 2018 soWhat. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

using namespace std;


char * input = nullptr;

bool opValid(char ch)
{
    if(ch == '+'|| ch == '-' || ch == '/'|| ch == '*'|| ch == '(' || ch == ')')
        return true;
    return false;
}

bool plusMinus(char ch)
{
    if(ch == '-' || ch == '+')
        return true;
    return false;
}

bool checkInput(const char* _input )
{
    char charOne;
    char charNext;
    int numberCount = 0;
    int len = (int)strlen(_input);
    bool isSign = false;
    
    for(int i = 0; i < len; ++i)
    {
        charOne = _input[i];
        charNext = _input[i+1];
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
            cout << "sign is not valid" << endl;
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


struct BrackPoint
{
    int among = 0;
    char operant = '+';
    char preOperant = '+';
    int rememberTerm = 0;
};

void dissolveBrackets(BrackPoint& first, BrackPoint& second)
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

char get()
{
    return *input;
}

void raise()
{
    ++input;
}

int among = 0;
char operant = '+';
char preOperant = '+';
int rememberTerm = 0;

vector<BrackPoint> brack;
char thirdSign;
int parseTDown()
{
    char temp = get();
    char secSign = *(input+1);
    bool isInt = false;

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

int main(int argc, const char * argv[])
{
    string inputStr;
    cout << "Please enter your arithmetic expressions: " << endl;
    getline(cin, inputStr);

    inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), ' '),
                   inputStr.end());

    auto toPointer = make_unique<char[]>(inputStr.length());
    strcpy(toPointer.get(), inputStr.c_str());
    input = toPointer.get();

    cout << "------------------------" << endl;
    
    if(!checkInput(input))
        return 0;
    
    if(strlen(input) > 0)
        cout << "The outcome is : " << parseTDown() << endl;
    else
        cout << "The outcome is : " << 0 << endl;

    
    

    return 0;
}

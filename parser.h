#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include <regex>

#include<variable.h>
#include<function.h>


using namespace std;

class Parser
{
public:
    Parser();
    Parser(string &&str);

    map<string,int> getOperators();
    map<string,int> getOperations();

private:
    void findVariables();
    void findOperators();

    string _str;

    map<string,int> _operators;
    map<string,int> _operations;

};

#endif // PARSER_H

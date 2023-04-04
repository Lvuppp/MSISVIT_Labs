#ifndef FUNCTION_H
#define FUNCTION_H
#include <vector>
#include<string>


using namespace std;

class Function
{
public:
    Function(string type,string name,vector<Function> overloadFuncs,vector<string> funcArgs): _funcName(name),_funcType(type),_overloadFuncs(overloadFuncs),_funcArgs(funcArgs){};
    Function(string type,string name,vector<string> funcArgs): _funcName(name),_funcType(type),_funcArgs(funcArgs){};
    string getPrototype();
    string getOverloadsFunc();
    string getName();
    string getType();

private:
    string _funcName;
    string _funcType;

    vector<Function> _overloadFuncs;
    vector<string> _funcArgs;
};


#endif // FUNCTION_H

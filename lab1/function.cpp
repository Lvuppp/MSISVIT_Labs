#include "function.h"

string Function::getName()
{
    return _funcName;
}

string Function::getType()
{
    return _funcType;
}

string Function::getPrototype()
{
    string args = "";
    for(auto i : _funcArgs){
        args += i + ", ";
    }

    return _funcType + " " + _funcName + " (" + args + ");";
}

string Function::getOverloadsFunc()
{
    string str;
    for(auto i = 0; i < _overloadFuncs.size(); i++){
        str += " " + _overloadFuncs[i].getPrototype() + "\n";
    }
    return str;
}

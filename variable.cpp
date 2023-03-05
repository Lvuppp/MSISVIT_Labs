#include "variable.h"

string Variable::getType()
{
    return _type;
}

string Variable::getPositions()
{
    string tmp;
    for(auto i = 0; i < _changingPos.size();i++){
        stringstream ss,ss2;
        ss << _changingPos[i].first;
        ss2 << _changingPos[i].second;

        tmp += ss.str() + " " + ss2.str() + "\n";
    }
    return tmp;
}

string Variable::getName()
{
    return _name;
}

string Variable::getDefaulValue()
{
    if(_defaultValue == "")
        return "NONE";
    return _defaultValue;
}

string Variable::getVisibilityArea()
{
    if(_isGlobal)
        return "(global)";
    return "(local)";
}

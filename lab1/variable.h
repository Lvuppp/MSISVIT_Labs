#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <vector>
#include<sstream>
using namespace std;

class Variable
{
public:
    Variable(string type, string name,  vector<pair<int,int>> changingPos,string defaultValue,bool isGlobal = false):
        _type(type),_name(name),_defaultValue(defaultValue),_changingPos(changingPos),_isGlobal(isGlobal){};
    string getType();
    string getName();
    string getDefaulValue();
    string getPositions();
    string getVisibilityArea();
private:
    string _type;
    string _name;
    string _defaultValue;
    vector<pair<int,int>> _changingPos;
    bool _isGlobal;

};



#endif // VARIABLE_H

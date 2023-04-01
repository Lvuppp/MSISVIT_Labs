#include "parser.h"
#include <QApplication>

Parser::Parser(string &&str) : _str(str)
{
    findVariables();
    findOperators();
}

map<string,int> Parser::getOperators()
{
    return _operators;
}

map<string,int> Parser::getOperations()
{
    return _operations;
}

void Parser::findOperators()
{
    regex reg("fail|max|min|abs|sqrt|delete|continue|break|return|if|else|for|do|while|"
              "\\+\\+|--|!=|==|<=|>=|<<|>>|&&|\\|\\||[\\+\\-\\*/%&\\|\\^~!=<>\\;]");
    string operatios = "\\+\\+|--|!=|==|&&|\\|\\||[\\+\\-\\*/%&\\|\\^~!<>]";
    smatch tmp,tmp2,tmp3,tmp4,tmp5;
    string str = _str;

    while(regex_search(str,tmp,reg)){
        if(_operations.count(tmp[0].str()) > 0){
            _operations[tmp[0].str()]++;
        }
        else{
            _operations.emplace(std::make_pair(tmp[0].str(),1));
        }

        str = tmp.suffix();
    }

    regex reg2("(\\w+)\\s*\\((.*)\\)");
    str = _str;
    while(regex_search(str,tmp2,reg2)){

        if(_operations.count(tmp2[1].str()) > 0){
            _operations[tmp2[1].str()]++;
        }
        else{
            _operations.emplace(std::make_pair(tmp2[1].str(),1));
        }

        str = tmp2.suffix();
    }

    int amountOfFigureBrackets = 0;

    regex reg3("\\((.*)\\)");
    regex reg5("(\\(.+?\\s*(&&|\\|\\|)\\s*.+?\\))");
    str = _str;
    while(regex_search(str,tmp3,reg3)){
        auto strTmp = tmp3[1].str();
        while(regex_search(strTmp,tmp5,reg5)){
            qDebug() << QString::fromStdString(tmp5[1].str());
            if(_operations.count("(..)") == 0){
                _operations.emplace(std::make_pair("(..)",1));
            }
            else{
                _operations["(..)"]++;
            }

            strTmp = tmp5.suffix();
        }

        str = tmp3.suffix();
    }

    for (auto i = 0; i < _str.length(); ++i) {

        if(_str[i] == '{'){
            amountOfFigureBrackets++;
        }
    }

    if(amountOfFigureBrackets > 0){
        _operations.emplace(std::make_pair("{..}",amountOfFigureBrackets));
    }
}


void Parser::findVariables()
{
    regex reg("((auto|int|float|double|short|long\\slong|char|bool|void|string|vector<.+>)\\**\\s(\\w+)(\\s*=.+)*\\s*(;|,))");
    smatch tmp,tmp2,tmp3,tmp4;
    string str = _str;
    string operatios = "\\+\\+|--|!=|==|<=|>=|<<|>>|&&|\\|\\||[\\+\\-\\*/%&\\|\\^~!=<>\\,\\;]";

    while(regex_search(str,tmp,reg)){
        regex reg2("(\\s*|" + operatios+ ")" + tmp[3].str()+"(\\s+|" + operatios+ ")");
        string tmpStr = tmp.suffix();

        if(_operators.count(tmp[3].str()) == 0){
            _operators.emplace(std::make_pair(tmp[3].str(),1));

            while(regex_search(tmpStr,tmp2,reg2)){
                _operators[tmp[3].str()]++;
                tmpStr  = tmp2.suffix();
            }
        }

        str = tmp.suffix();
    }

    str = _str;
    regex reg2("\\s*(\\d+)\\s*");

    while(regex_search(str,tmp3,reg2)){
        if(_operators.count(tmp3[1].str()) > 0){
            _operators[tmp3[1].str()]++;
        }
        else{
            _operators.emplace(std::make_pair(tmp3[1].str(),1));
        }
        str = tmp3.suffix();
    }
    str = _str;

    regex reg3("\\s*('.')|(\".+\")\\s*");

    while(regex_search(str,tmp4,reg3)){
        if(_operators.count(tmp4[0].str()) > 0){
            _operators[tmp4[0].str()]++;
        }
        else{
            _operators.emplace(std::make_pair(tmp4[0].str(),1));
        }
        str = tmp4.suffix();
    }
}

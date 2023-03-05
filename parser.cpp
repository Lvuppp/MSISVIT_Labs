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

//void Parser::findFunctions()
//{
//    smatch sm, sm2,sm3,sm4;

//    string str = _str;
//    regex reg("(int|float|double|short|long\\slong|char|bool|void|string)\\s+(\\w+)\\s*\\((.*)\\)");
//    regex reg2("(int|float|double|short|long\\slong|char|bool|void|string)\\s+\\w*,?");

//    while(regex_search(str,sm,reg)){
//        bool isOverload = false;

//        for(auto i = 0; i < _functions.size(); i++){
//            if(sm[2].str() == _functions[i].getName()){
//                isOverload = true;
//                break;
//            }
//        }

//        if(isOverload){
//            str = sm.suffix();
//            continue;
//        }

//        regex reg2( "(int|float|double|short|long\\slong|char|bool|void|string)");
//        regex reg3( "(int|float|double|short|long\\slong|char|bool|void|string)\\s+"+ sm[2].str() +"\\s*\\((.*)\\)");
//        vector<pair<int,int>> pos;
//        vector<string> args,overloadArgs;
//        vector<Function> overloadsFunctions;
//        string tmp =sm[3].str();
//        auto strTmp = QString::fromStdString(str).split('\n');
//        int overloadsCount = 0 ;

//        while(regex_search(tmp,sm2,reg2)){
//            args.push_back(sm2[1].str());
//            tmp = sm2.suffix();
//        }

//        for(auto i = 0; i < strTmp.length(); i++){
//            auto line = strTmp[i].toStdString();

//            while(regex_search(line,sm3,reg3)){
//                if(overloadsCount != 0){
//                    pos.push_back(make_pair(i+1,sm2.position() + 1));

//                    string tmp1 = sm3[2].str();
//                    overloadArgs.clear();

//                    while(regex_search(tmp1,sm4,reg2)){
//                        overloadArgs.push_back(sm4[1].str());
//                        tmp1 = sm4.suffix();
//                    }

//                    overloadsFunctions.push_back(Function(sm3[1].str(),sm[2].str(),overloadArgs));
//                }
//                overloadsCount++;
//                line = sm3.suffix();
//            }
//        }
//        _functions.push_back(Function(sm[1].str(), sm[2].str(),overloadsFunctions,args));
//        str = sm.suffix();
//    }

//}

void Parser::findOperators()
{
    regex reg("max|min|abs|sqrt|delete|continue|break|return|if|else|for|do|while|"
              "\\+\\+|--|!=|==|<=|>=|<<|>>|&&|\\|\\||[\\+\\-\\*/%&\\|\\^~!=<>]");
    smatch tmp,tmp2;
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
        qDebug() << QString::fromStdString(tmp2[1].str());

        if(_operations.count(tmp2[1].str()) > 0){
            _operations[tmp2[1].str()]++;
        }
        else{
            _operations.emplace(std::make_pair(tmp2[1].str(),1));
        }

        str = tmp2.suffix();
    }

    int amountOfFigureBrackets = 0,amountOfCircleBrakcets = 0;

    for (auto i = 0; i < _str.length(); ++i) {
        if(_str[i] == '('){
            amountOfCircleBrakcets++;
        }
        if(_str[i] == '{'){
            amountOfFigureBrackets++;
        }
    }

    if(amountOfFigureBrackets > 0){
        _operations.emplace(std::make_pair("(..)",amountOfCircleBrakcets));
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
    string operatios = "\\+\\+|--|!=|==|<=|>=|<<|>>|&&|\\|\\||[\\+\\-\\*/%&\\|\\^~!=<>,;]";

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
    regex reg2("(\\s*|" + operatios+ ")(\\d+|\"\\w*\"|\'w*\')(\\s+|" + operatios+ ")");

    while(regex_search(str,tmp3,reg2)){

        if(_operators.count(tmp3[2].str()) > 0){
            _operators[tmp3[2].str()]++;
        }
        else{
            _operators.emplace(std::make_pair(tmp3[2].str(),1));
        }
        str = tmp3.suffix();
    }


}

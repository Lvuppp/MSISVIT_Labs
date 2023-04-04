#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <stack>
#include <regex>
#include<string>


class Calculator
{
public:

    static int countOperators(const QString& code);
    static int countConditionalOperators(const QString& code);
    static QString calculate(const QString& code);
};

#endif // CALCULATOR_H

#include "calculator.h"
#include <QRegularExpression>
#include <string_view>

QString Calculator::calculate(const QString& code)
{
    int numConditionals = 0;
    int numOperators = 0;
    int numSwitchCases = 0;

    std::stack<char> stack;
    std::string str = code.toStdString();
    QRegularExpression reg("\\s*(if.*|else)\\s*\\{(.*)\\}\\s*");
    QRegularExpressionMatch outsideIf, insideIf;
    int maxDepth = 0;
    int pos = 0;
    QRegularExpressionMatchIterator it = reg.globalMatch(code);
    while (it.hasNext())
    {
        QString tmpStr = outsideIf.captured(2);
        int depth = 1;
        int innerPos = 0;
        while ((insideIf = reg.match(tmpStr, innerPos)).hasMatch()) {
            depth++;
            tmpStr = insideIf.captured(2);
            innerPos = insideIf.capturedEnd();
        }
        if (depth > maxDepth) {
            maxDepth = depth;
        }
        pos = outsideIf.capturedEnd();
    }



//           // Count conditionals
    QRegularExpression conditionalRegex("\\b(if|for|case)\\b");
    numConditionals = code.count(conditionalRegex);

//           // Count all operators
    QRegularExpression operatorRegex("[;{}]");
    numOperators = code.count(operatorRegex);

//           // Count switch cases
//    QRegularExpression switchRegex("\\b(switch)\\b.*?{.*?\\b(case|default)\\b");
//    QRegularExpressionMatchIterator switchMatches = switchRegex.globalMatch(code);
//    while (switchMatches.hasNext()) {
//        QRegularExpressionMatch match = switchMatches.next();
//        numSwitchCases += match.capturedTexts().count() - 1;
//    }

//           // Calculate the ratio of conditionals to operators
    double ratioConditionals = (double)(numConditionals) / numOperators;

    QString result = QString("Абсолютная сложность: %1\nОтносительная сложность: %2\nМаксимальная вложенность: %3")
                             .arg(numConditionals).arg(ratioConditionals).arg(maxDepth);
    return result;
}


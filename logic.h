#ifndef LOGIC_H
#define LOGIC_H
#include<string>
int precedence(char op);
double applyOperator(double a, double b, char op);
double calculateExpression(const std::string& expression);
#endif // LOGIC_H

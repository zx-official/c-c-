#include "logic.h"
#include <stack>
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0.0;  // 处理未知运算符
    }
}

double calculateExpression(const std::string& expression) {
    std::stack<double> values;
    std::stack<char> operators;

    for (size_t i = 0; i < expression.size(); ++i) {
        if (std::isspace(expression[i])) {
            // 忽略空格
            continue;
        } else if (std::isdigit(expression[i]) || (expression[i] == '-' && i == 0)) {
            // 解析数字
            size_t j = i;
            while (j < expression.size() && (std::isdigit(expression[j]) || expression[j] == '.')) {
                ++j;
            }
            double value = std::stod(expression.substr(i, j - i));
            values.push(value);
            i = j - 1;  // 更新索引位置
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.pop();  // 弹出左括号
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        values.push(applyOperator(a, b, op));
    }

    return values.top();
}

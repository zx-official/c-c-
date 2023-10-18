#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>
#include <QDebug>
#include <string>
#include <sstream>
#include <logic.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Expression = "";
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
//int precedence(char op) {
//    if (op == '+' || op == '-') return 1;
//    if (op == '*' || op == '/') return 2;
//    return 0;
//}

//double applyOperator(double a, double b, char op) {
//    switch (op) {
//        case '+': return a + b;
//        case '-': return a - b;
//        case '*': return a * b;
//        case '/': return a / b;
//        default: return 0.0;  // 处理未知运算符
//    }
//}

//double calculateExpression(const std::string& expression) {
//    std::stack<double> values;
//    std::stack<char> operators;

//    for (size_t i = 0; i < expression.size(); ++i) {
//        if (std::isspace(expression[i])) {
//            // 忽略空格
//            continue;
//        } else if (std::isdigit(expression[i]) || (expression[i] == '-' && i == 0)) {
//            // 解析数字
//            size_t j = i;
//            while (j < expression.size() && (std::isdigit(expression[j]) || expression[j] == '.')) {
//                ++j;
//            }
//            double value = std::stod(expression.substr(i, j - i));
//            values.push(value);
//            i = j - 1;  // 更新索引位置
//        } else if (expression[i] == '(') {
//            operators.push(expression[i]);
//        } else if (expression[i] == ')') {
//            while (!operators.empty() && operators.top() != '(') {
//                char op = operators.top();
//                operators.pop();
//                double b = values.top();
//                values.pop();
//                double a = values.top();
//                values.pop();
//                values.push(applyOperator(a, b, op));
//            }
//            operators.pop();  // 弹出左括号
//        } else {
//            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
//                char op = operators.top();
//                operators.pop();
//                double b = values.top();
//                values.pop();
//                double a = values.top();
//                values.pop();
//                values.push(applyOperator(a, b, op));
//            }
//            operators.push(expression[i]);
//        }
//    }

//    while (!operators.empty()) {
//        char op = operators.top();
//        operators.pop();
//        double b = values.top();
//        values.pop();
//        double a = values.top();
//        values.pop();
//        values.push(applyOperator(a, b, op));
//    }

//    return values.top();
//}

void MainWindow::on_pushButton_1_clicked()
{
        QString key = "1";
        ui->input_text->insertPlainText(key);
}



void MainWindow::on_pushButton_2_clicked()
{
    QString key = "2";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString key = "3";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_4_clicked()
{
    QString key = "4";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_5_clicked()
{
    QString key = "5";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_6_clicked()
{
    QString key = "6";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_7_clicked()
{
    QString key = "7";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_8_clicked()
{
    QString key = "8";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_9_clicked()
{
    QString key = "9";
    ui->input_text->insertPlainText(key);
}



void MainWindow::on_pushButton_div_clicked()
{
    QString key = "/";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_multi_clicked()
{
    QString key = "*";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_sub_clicked()
{
    QString key = "-";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_equal_clicked()
{
//    QString key = "=";
//    ui->input_text->insertPlainText(key);
    Expression = ui->input_text->toPlainText();
    qDebug()<<Expression<<endl;
    double result = calculateExpression(Expression.toStdString());
    qDebug()<<result<<endl;
    ui->input_text->setText(QString::number(result));

}


void MainWindow::on_pushButton_doat_clicked()
{
    QString key = ".";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_add_clicked()
{
    QString key = "+";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_left_clicked()
{
    QString key = "(";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_right_clicked()
{
    QString key = ")";
    ui->input_text->insertPlainText(key);
}


void MainWindow::on_pushButton_clear_clicked()
{
    Expression = "";
    ui->input_text->setText(Expression);
}


void MainWindow::on_pushButton_backspace_clicked()
{
    Expression = ui->input_text->toPlainText();
    Expression.chop(1);
    ui->input_text->setText(Expression);

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stack>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_div_clicked();

    void on_pushButton_multi_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_doat_clicked();

    void on_pushButton_add_clicked();


    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_backspace_clicked();

private:
    Ui::MainWindow *ui;
    QString Expression; //表达式
};
#endif // MAINWINDOW_H

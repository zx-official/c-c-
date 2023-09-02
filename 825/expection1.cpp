#include <iostream>
#include <stdexcept> // 包含标准异常类的头文件
using namespace std;

int main() {
    int a, b;
    a = 8;
    b = 0;
    try {
        if (b == 0) {
            // 抛出 runtime_error 异常对象
            throw runtime_error("Divided by Zero!");
        } else {
            double c = a / b;
            cout << c << endl;
        }
    } catch (const exception& e) {
        // 捕获异常，并输出异常信息
        cout << "Exception caught: " << e.what() << endl;
    }
    
    return 0;
}

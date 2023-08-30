#include <iostream>

class MyCustomClass {
public:
    int value;

    MyCustomClass(int val) : value(val) {}

    // 重载 << 运算符，以输出 MyCustomClass 对象
    friend std::ostream& operator<<(std::ostream& os, const MyCustomClass& obj) {
        os << "Value: " << obj.value;
        return os;
    }
};

int main() {
    MyCustomClass obj(42);
    MyCustomClass obj1(421);
    std::cout << obj <<obj1<< std::endl; // 输出自定义对象

    return 0;
}

#include <iostream>

class MyClass {
public:
    int value;

    MyClass(int val) : value(val) {}
};

// 函数返回值为引用类型
MyClass& modifyValue(MyClass& obj) {
    obj.value *= 2; // 修改传入对象的值
    return obj;     // 返回原始对象的引用
}

int main() {
    MyClass obj(3);
    modifyValue(obj);
    std::cout << " value: " << obj.value << std::endl;

    modifyValue(obj).value = 10; // 通过返回的引用修改对象的值

    std::cout << "Modified value: " << obj.value << std::endl;

    return 0;
}

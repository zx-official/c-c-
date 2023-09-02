# include <iostream>
using namespace std;

class Sample {
private:
    int x;

public:
    Sample(int val = 0) { x = val; cout << "构造" << x << endl; }
    Sample(const Sample& obj) { x = obj.x; cout << "拷⻉构造" << x << endl; }
    ~Sample() { cout << "析构" << x << endl; }
    void operator++() { x++; }

    // 重载 + 运算符
    Sample operator+(int val) {
        Sample result(x + val);
        cout << "重载 + 运算符" << endl;
        return result;
    }
};

void foo(Sample i);

int main() {
    Sample s1, s2(1);
    foo(s1);
    foo(2);
    return 0;
}

void foo(Sample i) {
    static Sample s3 = i + 1;
    ++s3;
}

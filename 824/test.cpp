#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base Constructor" << std::endl;
    }
};

class VirtualDerived : virtual public Base {
public:
    VirtualDerived() {
        std::cout << "VirtualDerived Constructor" << std::endl;
    }
};

class IntermediateDerived : virtual public Base {
public:
    IntermediateDerived() {
        std::cout << "IntermediateDerived Constructor" << std::endl;
    }
};

class MostDerived : public VirtualDerived, public IntermediateDerived {
public:
    MostDerived() {
        std::cout << "MostDerived Constructor" << std::endl;
    }
};

int main() {
    MostDerived obj;
    return 0;
}

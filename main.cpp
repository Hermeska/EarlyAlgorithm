#include <iostream>
#include "test.cpp"
#pragma  once
int main() {

    Test test;
    test.RunAllTests();
    std::cout << "All tests passed." << std::endl;
}

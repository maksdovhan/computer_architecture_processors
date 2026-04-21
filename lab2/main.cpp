#include <iostream>
#include "calculator.h"

int main() {
    Calculator calc;

    std::cout << "5.2 + 3.1 = " << calc.Add(5.2, 3.1) << std::endl;
    std::cout << "5.2 - 3.1 = " << calc.Sub(5.2, 3.1) << std::endl;
    return 0;
}

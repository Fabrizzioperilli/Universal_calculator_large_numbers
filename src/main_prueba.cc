#include <iostream>
#include "../include/Number.h"

int main()
{
    Number* n = n->create(10, "123");
    Number* n2 = n2->create(10, "123");

    Number* n3 = n->Add(n2);
    std::cout << *n3 << std::endl;
    
    std::cout << *n->Module(n2)<< std::endl;
    std::cout << *n->Subtract(n2) << std::endl;
    std::cout << *n->Divide(n2) << std::endl;
    std::cout << *n->Multiply(n2) << std::endl;

    return 0;
}
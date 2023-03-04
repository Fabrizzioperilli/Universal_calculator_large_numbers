#include <iostream>
#include "../include/Number.h"

int main()
{
    Number* n = n->create(10, "123");
    Number* n2 = n2->create(10, "123");
    std::cout << *n->Add(n2) << std::endl;

    Number* bin = bin->create(2, "010");
    Number* bin2 = bin2->create(2, "001");
  
    std::cout << *bin->Add(bin2) << std::endl;
    
    // std::cout << *n->Module(n2)<< std::endl;
    // std::cout << *n->Subtract(n2) << std::endl;
    // std::cout << *n->Divide(n2) << std::endl;
    // std::cout << *n->Multiply(n2) << std::endl;

    return 0;
}
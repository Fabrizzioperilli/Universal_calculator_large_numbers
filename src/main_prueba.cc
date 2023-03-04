#include <iostream>
#include "../include/Number.h"

int main()
{

    try
    {
        Number *n = n->create(19, "123");
        Number *n2 = n2->create(10, "5");
        Number *bin = bin->create(2, "0100");
        Number *bin2 = bin2->create(2, "001");

        std::cout << *n << " + " << *n2 << " = " << *n->Add(n2) << std::endl;
        std::cout << *n << " - " << *n2 << " = " << *n->Subtract(n2) << std::endl;
        std::cout << *n << " * " << *n2 << " = " << *n->Multiply(n2) << std::endl;
        std::cout << *n << " / " << *n2 << " = " << *n->Divide(n2) << std::endl;
        std::cout << *n << " % " << *n2 << " = " << *n->Module(n2) << std::endl;
        std::cout << *n << " ^ " << *n2 << " = " << *n->Pow(n2) << std::endl;

        std::cout << *bin << " + " << *bin2 << " = " << *bin->Add(bin2) << std::endl;
        std::cout << *bin << " - " << *bin2 << " = " << *bin->Subtract(bin2) << std::endl;
        std::cout << *bin << " * " << *bin2 << " = " << *bin->Multiply(bin2) << std::endl;
        std::cout << *bin << " / " << *bin2 << " = " << *bin->Divide(bin2) << std::endl;
        std::cout << *bin << " % " << *bin2 << " = " << *bin->Module(bin2) << std::endl;
        std::cout << *bin << " ^ " << *bin2 << " = " << *bin->Pow(bin2) << std::endl;
    }
    catch (BigIntBadDigit &e)
    {
        std::cout <<"Exception--> " << e.what() << std::endl;
        std::cout << e.getErrorMessage() << " -- " << e.getLocation() <<  std::endl;

    }
    catch (BigIntBaseNotImplemented &e)
    {
        std::cout <<"Exception--> " << e.what() << std::endl;
        std::cout << e.getErrorMessage() << " -- " << e.getLocation() <<  std::endl;
    }
    catch (BigIntDivisionByZero &e)
    {
        std::cout <<"Exception--> " << e.what() << std::endl;
        std::cout << e.getErrorMessage() << " -- " << e.getLocation() <<  std::endl;
    }
    catch (BigIntException &e)
    {
        std::cout <<"Exception--> " << e.what() << std::endl;
        std::cout << e.getErrorMessage() << " -- " << e.getLocation() <<  std::endl;
    }

    return 0;
}
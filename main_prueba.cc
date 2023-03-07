#include <iostream>
#include "../include/Number.h"

int main()
{

    try
    {
        Number *n = n->create(10, "123");
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

    BigInt<2> bin("1010");
    BigInt<8> oct("123");
    BigInt<10> dec("123");
    BigInt<16> hex("D");
    std::cout << bin << " (Bin) = " << bin.operator BigInt<2UL>().operator BigInt<8UL>() << std::endl;
    std::cout << dec << " (Oct) = " << dec.operator BigInt<8UL>() << std::endl;
    std::cout << hex << " (Dec) = " << hex.operator BigInt<10UL>() << std::endl;
    std::cout << oct << " (Hex) = " << oct.operator BigInt<16UL>() << std::endl;
    std::cout << hex << " (Bin) = " << hex.operator BigInt<2UL>() << std::endl;
    
    return 0;
}
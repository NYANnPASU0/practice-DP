#include "BIG_RATIONAL.h"

int main()
{
    setlocale(LC_ALL, "ru");

    BigRational br1(-1111111, 25);
    BigRational br2(125, 3);
    std::cout << br1 << std::endl << br2 << std::endl;
    std::cout << std::endl;

    //сравнение
    if (br1 > br2)
    {
        std::cout << br1 << " > " << br2 << std::endl;
    }
    else if (br1 == br2)
    {
        std::cout << br1 << " = " << br2 << std::endl;
    }
    else if (br1 < br2)
    {
        std::cout << br1 << " < " << br2 << std::endl;
    }
    else if (br1 != br2)
    {
        std::cout << br1 << " != " << br2 << std::endl;
    }
    else if (br1 >= br2)
    {
        std::cout << br1 << " >= " << br2 << std::endl;
    }
    else if (br1 <= br2)
    {
        std::cout << br1 << " <= " << br2 << std::endl;
    }
    std::cout << std::endl;

     
    //br13_copy = br2, br14_copy = br1, br15_copy = br1, br16_copy = br1, br17(4, 12), br18_copy = br17, br22(15, 13);
    //BigRational br24(1, 14);
    //BigRational br24_copy(1, 14);
    //BigRational br24_copy_2(1, 14);
    //BigRational br24_copy_3(1, 14);

    BigRational br4;
    br4 = br1 + br2;
    std::cout << br1 << " + " << br2 << " = " << br4 << std::endl;


    BigRational br5;
    br5 = br1 - br2;
    std::cout << br1 << " - " << br2 << " = " << br5 << std::endl;


    BigRational br6;
    br6 = br1 * br2;
    std::cout << br1 << " * " << br2 << " = " << br6 << std::endl;


    BigRational br7;
    br7 = br1 / br2;
    std::cout << br1 << " / " << br2 << " = " << br7 << std::endl;


    BigRational br8;
    br8 = br2 + 2;
    std::cout << br2 << " + 2 " << " = " << br8 << std::endl;


    BigRational br9;
    br9 = br1 - 3;
    std::cout << br1 << " - 3 " << " = " << br9 << std::endl;


    BigRational br10;
    br10 = br2 * 3;
    std::cout << br2 << " * 3 " << " = " << br10 << std::endl;


    BigRational br11;
    br11 = br2 / 3;
    std::cout << br2 << " / 3 " << " = " << br11 << std::endl;


    BigRational br12(10000025, 12);
    BigRational br12_copy = br12;
    br12 -= 10;
    std::cout << br12_copy << " -= 10 " << " = " << br12 << std::endl;


    BigRational br13 = br1;
    br13--;
    std::cout << "( " << br1 << " )--  = " << br13 << std::endl;


    BigRational br14 = br2;
    br14++;
    std::cout << "( " << br2 << " )++  = " << br14 << std::endl;

    std::cout << std::endl;


    //приведение к double
    BigRational br15 = br1;
    std::cout << br1 << "   BigRational like double:  " << br15.asDecimal(5) << std::endl;


    BigRational br16 = br2;
    std::cout << br2 << "   BigRational like double:  " << br16.asDecimal(6) << std::endl;


    BigRational br17 = br12;
    std::cout << br12 << "   BigRational like double:  " << br17.asDecimal(7) << std::endl;

    std::cout << std::endl;
}
#include "BIG_RATIONAL.h"

int main()
{
    setlocale(LC_ALL, "ru");

    BigRational br1(-4, 5);
    BigRational br2(1, 3);
    BigRational br11(4, 3);
    std::cout << br1 << std::endl << br2 << std::endl;
    std::cout << std::endl;

    //сравнение
    if (br1 > br2)
    {
        std::cout << br1 << " > " << br2 << std::endl;
    }
    if (br1 == br2)
    {
        std::cout << br1 << " = " << br2 << std::endl;
    }
    if (br1 < br2)
    {
        std::cout << br1 << " < " << br2 << std::endl;
    }
    if (br1 != br2)
    {
        std::cout << br1 << " != " << br2 << std::endl;
    }
    if (br1 >= br2)
    {
        std::cout << br1 << " >= " << br2 << std::endl;
    }
    if (br1 <= br2)
    {
        std::cout << br1 << " <= " << br2 << std::endl;
    }
    std::cout << std::endl;

     
    BigRational br4, br5, br6, br7, br8, br9, br10, br12, br13_copy = br2, br14_copy = br1, br15_copy = br1, br16_copy = br1, br17(4, 12), br18_copy = br17, br22(15, 13);
    BigRational br24(1, 14);
    BigRational br24_copy(1, 14);
    BigRational br24_copy_2(1, 14);
    BigRational br24_copy_3(1, 14);

    br4 = br1 + br2;
    br5 = br1 - br2;
    br6 = br1 * br2;
    br7 = br1 / br2;
    br8 = br2 + 2;
    br9 = br1 - 3;
    br10 = br11 * 3;
    br12 = br2 / 3;
    br2 -= 3;
    br1--;
    --br15_copy;
    br24++;
    ++br24_copy_3;
    br17 *= 2;
    BigRational br23 = -br22;

    std::cout << br1 <<  " + " << br2  << " = " << br4 << std::endl;
    std::cout << br1 << " - " << br2 << " = " << br5 << std::endl;
    std::cout << br1 << " * " << br2 << " = " << br6 << std::endl;
    std::cout << br1 << " / " << br2 << " = " << br7 << std::endl;
    std::cout << br2 << " + 2 " << " = " << br8 << std::endl;
    std::cout << br1 << " - 3 " << " = " << br9 << std::endl;
    std::cout << br11 << " * 3 " << " = " << br10 << std::endl;
    std::cout << br2 << " / 3 " << " = " << br12 << std::endl;
    std::cout << br13_copy << " -= 3 " << " = " << br2 << std::endl;
    std::cout << br14_copy << "-- " << " = " << br1 << std::endl;
    std::cout << "--(" <<br16_copy << ") " << " = " << br15_copy << std::endl;
    std::cout << br24_copy << "++ " << " = " << br24 << std::endl;
    std::cout << "++(" << br24_copy_2 << ") " << " = " << br24_copy_3 << std::endl;
    std::cout << br18_copy << " *=2 " << " = " << br17 << std::endl;
    std::cout << "унарный минус: "  << br23 << std::endl;
    std::cout << std::endl;


    //приведение к double
    BigRational br19(2, 4);
    BigRational br19_сopy(2, 4);
    std::cout << br19_сopy << "   BigRational like double:  " << br19.asDecimal(1) << std::endl;


    BigRational br20(1, 3);
    BigRational br20_сopy(1, 3);
    std::cout << br20_сopy << "   BigRational like double:  " << br20.asDecimal(3) << std::endl;


    BigRational br21(4, 2);
    BigRational br21_сopy(4, 2);
    std::cout << br21_сopy << "   BigRational like double:  " << br21.asDecimal(1) << std::endl;

    std::cout << std::endl;
}
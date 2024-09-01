#include <iostream>
#include "Finite.h"
#include "Matrix.h"

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "класс Finite: " << '\n' << '\n';


    Finite<7> a(10);  // a = 10 mod 7 = 3
    Finite<7> b(5);   // b = 5 mod 7 = 5

    std::cout << "a = "; a.print();
    std::cout << "b = "; b.print();
    std::cout << '\n';


    std::cout << "a + b = " << (a + b).get() << '\n';  // 8 mod 7 = 1
    std::cout << "a - b = " << (a - b).get() << '\n';  // 2 mod 7 = 2
    std::cout << "a * b = " << (a * b).get() << '\n';  // 15 mod 7 = 1

    std::cout << '\n' << '\n';




    std::cout << "класс Matrix: " << '\n' << '\n';

    Matrix<2, 2> m1;
    Matrix<2, 2> m2;


    m1.set(0, 0, BigRational(1, 2));
    m1.set(0, 1, BigRational(1, 4));
    m1.set(1, 0, BigRational(1, 3));
    m1.set(1, 1, BigRational(2, 5));

    std::cout << "m1 = " << '\n';
    m1.print();
    std::cout << '\n';


    m2.set(0, 0, BigRational(1, 3));
    m2.set(0, 1, BigRational(1, 5));
    m2.set(1, 0, BigRational(1, 4));
    m2.set(1, 1, BigRational(1, 6));

    std::cout << '\n';
    std::cout << "m2 = " << '\n';
    m2.print();
    std::cout << '\n';

    std::cout << '\n';
    std::cout << " m1 + m2 = " << '\n';
    Matrix<2, 2> m3 = m1 + m2;
    m3.print();
    std::cout << '\n';

    std::cout << '\n';
    std::cout << " m1 - m2 = " << '\n';
    Matrix<2, 2> m4 = m1 - m2;
    m4.print();
    std::cout << '\n';

    std::cout << '\n';
    std::cout << " m1 * m2 = " << '\n';
    Matrix<2, 2> m5 = m1 * m2;
    m5.print();
    std::cout << '\n';

    std::cout << "ДОПОЛНИТЕЛЬНАЯ МАТРИЦА: " << '\n';


    Matrix<2, 2, BigRational> matrix;
    matrix.set(0, 0, BigRational(1));
    matrix.set(0, 1, BigRational(2));
    matrix.set(1, 0, BigRational(3));
    matrix.set(1, 1, BigRational(3));

    // НЕКВАДРАТНАЯ МАТРИЦА
    /*Matrix<2,3, Rational> matrix;
    matrix.set(0, 0, Rational(1));
    matrix.set(0, 1, Rational(1));
    matrix.set(0, 2, Rational(1));
    matrix.set(1, 0, Rational(2));
    matrix.set(1, 1, Rational(2));
    matrix.set(1, 2, Rational(2));*/

    matrix.print();
    std::cout << '\n';

    // Вычисляем и выводим определитель матрицы
    /*Rational det = matrix.det();
    cout << "Определитель матрицы: " << det << '\n';*/

    unsigned ran = matrix.rank();
    std::cout << "Ранг матрицы: " << ran << '\n';


    BigRational trace = matrix.trace();
    std::cout << "След матрицы: " << trace << '\n';

    std::cout << "Tранспонированная матрица:  " << '\n';
    matrix.transposed().print();



    //Matrix<2, 2, BigRational> obr = matrix.inverted(); //!!!!!!!!!!!!!!!!!!!!!!!!!  РАБОТАЕТ НЕ ОЧЕНЬ ПРАВИЛЬНО !!!!!!!!!!!
    //std::cout << "Обратная матрица:  " << '\n';
    //obr.print();

    // std::cout << "Обратимая от данной:  " << '\n';
    // obr.invert();
    // obr.print();

    //std::cout << '\n'; std::cout << '\n';



    std::cout << "первая строка нашей доп. матрицы: " << '\n';
      std::vector<BigRational> firstRow = matrix.getRow(0);
      for (int i = 0; i < firstRow.size(); ++i) { std::cout << firstRow[i] << " ";}

      std::cout << '\n';
      std::cout << '\n';

      std::cout << "первый стролбец нашей доп. матрицы: " << '\n';
      std::vector<BigRational> firstColumn = matrix.getColumn(0);
      for (int i = 0; i < firstColumn.size(); ++i) { std::cout << firstColumn[i] << '\n'; }

      std::cout << '\n';
      std::cout << '\n';

      std::cout << "смотрим значение: " << '\n';
      BigRational value = matrix(0, 1);
      std::cout << value; std::cout << '\n';

      std::cout << "теперь меняем его на: 5/5" << '\n';
      matrix(0, 1) = BigRational(5, 5);

      std::cout << "выводим получившуюся матрицу: " << '\n';
      matrix.print();



    return 0;
}

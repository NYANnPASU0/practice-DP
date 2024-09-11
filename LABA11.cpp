#include <iostream>
#include "Finite.h"
#include "Matrix.h"

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "класс Finite: " << std::endl << std::endl;


    Finite<7> a(10);  // a = 10 mod 7 = 3
    Finite<7> b(5);   // b = 5 mod 7 = 5

    std::cout << "a = "; a.print();
    std::cout << "b = "; b.print();
    std::cout << '\n';


    std::cout << "a + b = " << (a + b).get() << '\n';  // 8 mod 7 = 1
    std::cout << "a - b = " << (a - b).get() << '\n';  // 2 mod 7 = 2
    std::cout << "a * b = " << (a * b).get() << '\n';  // 15 mod 7 = 1

    std::cout << std::endl << std::endl;




    std::cout << "класс Matrix: " << std::endl << std::endl;

    Matrix<2, 2> m1;
    Matrix<2, 2> m2;


    m1.set(0, 0, BigRational(1, 2));
    m1.set(0, 1, BigRational(1, 4));
    m1.set(1, 0, BigRational(1, 3));
    m1.set(1, 1, BigRational(2, 5));

    std::cout << "m1 = " << std::endl;
    m1.print();
    std::cout << std::endl;


    m2.set(0, 0, BigRational(1, 3));
    m2.set(0, 1, BigRational(1, 5));
    m2.set(1, 0, BigRational(1, 4));
    m2.set(1, 1, BigRational(1, 6));

    std::cout << std::endl;
    std::cout << "m2 = " << std::endl;
    m2.print();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << " m1 + m2 = " << std::endl;
    Matrix<2, 2> m3 = m1 + m2;
    m3.print();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << " m1 - m2 = " << std::endl;
    Matrix<2, 2> m4 = m1 - m2;
    m4.print();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << " m1 * m2 = " << std::endl;
    Matrix<2, 2> m5 = m1 * m2;
    m5.print();
    std::cout << std::endl;

    std::cout << "ДОПОЛНИТЕЛЬНАЯ МАТРИЦА: " << std::endl;


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
    std::cout << std::endl;

    // Вычисляем и выводим определитель матрицы
    /*Rational det = matrix.det();
    cout << "Определитель матрицы: " << det << '\n';*/

    unsigned ran = matrix.rank();
    std::cout << "Ранг матрицы: " << ran << std::endl;


    BigRational trace = matrix.trace();
    std::cout << "След матрицы: " << trace << std::endl;

    std::cout << "Tранспонированная матрица:  " << std::endl;
    matrix.transposed().print();

    std::cout << "первая строка нашей доп. матрицы: " << std::endl;
      std::vector<BigRational> firstRow = matrix.getRow(0);

      for (int i = 0; i < firstRow.size(); i++)
      {
          std::cout << firstRow[i] << " ";
      }

      std::cout << std::endl;
      std::cout << std::endl;

      std::cout << "первый стролбец нашей доп. матрицы: " << std::endl;

      std::vector<BigRational> firstColumn = matrix.getColumn(0);
      for (int i = 0; i < firstColumn.size(); i++)
      {
          std::cout << firstColumn[i] << std::endl;
      }

      std::cout << std::endl;
      std::cout << std::endl;

      std::cout << "смотрим значение: " << std::endl;
      BigRational value = matrix(0, 1);
      std::cout << value; std::cout << std::endl;

      std::cout << "теперь меняем его на: 5/5" << std::endl;
      matrix(0, 1) = BigRational(5, 5);

      std::cout << "выводим получившуюся матрицу: " << std::endl;
      matrix.print();


    return 0;
}

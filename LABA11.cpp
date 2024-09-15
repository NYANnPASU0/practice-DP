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
    //1
    Matrix<2, 2> m1;

    m1.set(0, 0, BigRational(1, 2));
    m1.set(0, 1, BigRational(1, 4));
    m1.set(1, 0, BigRational(1, 3));
    m1.set(1, 1, BigRational(2, 5));

    std::cout << "m1 = " << std::endl;
    m1.print();
    std::cout << std::endl;

    //2
    Matrix<2, 2> m2;
    m2.set(0, 0, BigRational(1, 3));
    m2.set(0, 1, BigRational(1, 5));
    m2.set(1, 0, BigRational(1, 4));
    m2.set(1, 1, BigRational(1, 6));

    std::cout << std::endl;
    std::cout << "m2 = " << std::endl;
    m2.print();
    std::cout << std::endl;

    std::cout << std::endl;

    //арифм операции с матрицами
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



    std::cout << "Доп.матрица: " << std::endl;
    Matrix<2, 2, BigRational> matrix;
    matrix.set(0, 0, BigRational(1));
    matrix.set(0, 1, BigRational(2));
    matrix.set(1, 0, BigRational(3));
    matrix.set(1, 1, BigRational(3));

    matrix.print();
    std::cout << std::endl;



    //неквадратная матрица
    std::cout << "Неквадратная матрица: " << std::endl;
    Matrix<2,3, BigRational> m_nekw;
    m_nekw.set(0, 0, BigRational(1));
    m_nekw.set(0, 1, BigRational(1));
    m_nekw.set(0, 2, BigRational(1));
    m_nekw.set(1, 0, BigRational(2));
    m_nekw.set(1, 1, BigRational(2));
    m_nekw.set(1, 2, BigRational(2));

    m_nekw.print();
    std::cout << std::endl;



    // Вычисляем и выводим определитель матрицы
    BigRational det = matrix.det();
    std::cout << "Определитель матрицы: " << det << '\n';

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

      std::cout << "теперь меняем его на 5/5" << std::endl;
      matrix(0, 1) = BigRational(5, 5);

      std::cout << "выводим получившуюся матрицу: " << std::endl;
      matrix.print();



      //std::cout << "Есть матрица: " << std::endl;
      //Matrix<3, 3, BigRational> obr_m;
      //obr_m.set(0, 0, BigRational(1));
      //obr_m.set(0, 1, BigRational(3));
      //obr_m.set(0, 2, BigRational(2));
      //obr_m.set(1, 0, BigRational(4));
      //obr_m.set(1, 1, BigRational(1));
      //obr_m.set(1, 2, BigRational(1));
      //obr_m.set(2, 0, BigRational(1));
      //obr_m.set(2, 1, BigRational(2));
      //obr_m.set(2, 2, BigRational(3));

      //obr_m.print();
      //std::cout << std::endl;

      ////обратная матрица
      //std::cout << "Обратная матрица: " << std::endl;
      //obr_m.invert();

      //obr_m.print();
      //std::cout << std::endl;

    return 0;
}

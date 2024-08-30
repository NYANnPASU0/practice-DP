#pragma once
#include "BIG_INTEGER.h"
#include "BIG_RATIONAL.h"
#include "Finite.h"
#include <vector>
#include <iostream>


template <unsigned M, unsigned N, typename Field = BigRational>
class Matrix
{
    std::vector<std::vector<Field>> data;

public:
    Matrix()
    {
        for (size_t i = 0; i < M; i++)
        {
            data.push_back(std::vector<Field>(N));
            for (size_t j = 0; j < N; j++)
            {
                data[i][j] = Field(0);
            }
        }
    }

    Matrix(unsigned m, unsigned n)
    {
        data.resize(m);
        for (size_t i = 0; i < m; i++)
        {
            data[i].resize(n);
            for (size_t j = 0; j < n; j++)
            {
                data[i][j] = Field(0);
            }
        }
    }

    /*Matrix()
    {
        for (size_t i = 0; i < M; i++)
        {
            data.push_back(std::vector<Field>(N));
            for (size_t j = 0; j < N; j++)
            {
                if (i == j)
                {
                    data[i][j] = Field(1);
                }
                else
                {
                    data[i][j] = Field(0);
                }
            }
        }
    }*/


    Matrix(const Matrix& other)
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }

    }

    Matrix(const std::vector<std::vector<Field>>& values)
    {
        auto row_it = values.begin();
        for (size_t i = 0; i < M; i++, row_it++)
        {
            auto col_it = row_it->begin();
            for (size_t j = 0; j < N; j++, col_it++)
            {
                if (col_it != row_it->end())
                {
                    data[i][j] = *col_it;
                }
                else
                {
                    data[i][j] = Field(0);
                }
            }
        }
    }





    Field get(unsigned row, unsigned col) const
    {
        return data[row][col];
    }

    void set(unsigned row, unsigned col, const BigRational& value)
    {
        data[row][col] = value;
    }

    Matrix operator+(const Matrix& other) const
    {
        if (M != other.M || N != other.N)
        {
            throw std::invalid_argument("different sizes");
        }

        Matrix result;
        for (unsigned row = 0; row < M; row++)
        {
            for (unsigned col = 0; col < N; col++)
            {
                result.set(row, col, data[row][col] + other.get(row, col));
            }
        }
        return result;
    }


    Matrix operator-(const Matrix& other) const
    {
        if (M != other.M || N != other.N)
        {
            throw std::invalid_argument("different sizes");
        }
        Matrix result;
        for (unsigned row = 0; row < M; row++)
        {
            for (unsigned col = 0; col < N; col++)
            {
                result.set(row, col, data[row][col] - other.get(row, col));
            }
        }
        return result;
    }


    Matrix operator*(const Matrix& other) const
    {
        if (M != other.M || N != other.N)
        {
            throw std::invalid_argument("different sizes");
        }
        Matrix result;
        for (unsigned row = 0; row < M; row++)
        {
            for (unsigned col = 0; col < N; col++)
            {
                Field sum = 0;
                for (unsigned k = 0; k < N; k++)
                {
                    sum = sum + data[row][k] * other.get(k, col);
                }
                result.set(row, col, sum);
            }
        }
        return result;
    }


    Matrix& operator*=(const Matrix& other)
    {
        if (M != other.M || N != other.N)
        {
            throw std::invalid_argument("different sizes");
        }
        *this = *this * other;
        return *this;
    }

    Matrix& operator*=(Field scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    bool operator==(const Matrix& other) const
    {
        if (M != other.M || N != other.N)
        {
            return false;
        }
        for (unsigned row = 0; row < M; row++)
        {
            for (unsigned col = 0; col < N; col++)
            {
                if (data[row][col] != other.get(row, col))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    Matrix& operator+=(const Matrix& other)
    {
        *this = *this + other;
        return *this;
    }

    Matrix& operator-=(const Matrix& other)
    {
        *this = *this - other;
        return *this;
    }



    bool tr = false;
    Matrix<N, M, Field> transposed() //транспонирование матрицы
    {
        Matrix<N, M, Field> result;
        for (unsigned row = 0; row < M; row++)
        {
            for (unsigned col = 0; col < N; col++)
            {
                result.set(col, row, data[row][col]);
            }
        }
        return result;
    }



    Field trace() const //след матрицы
    {
        if (M != N)
        {
            throw std::invalid_argument("Trace is only defined for square matrices");
        }
        Field result = 0;
        for (unsigned i = 0; i < M; i++)
        {
            result += data[i][i];
        }
        return result;
    }





    std::vector<Field> getRow(unsigned row) const
    {
        if (row >= M)
        {
            throw std::invalid_argument("Invalid row index");
        }
        return data[row];
    }


    std::vector<Field> getColumn(unsigned col) const
    {
        if (col >= N)
        {
            throw std::invalid_argument("Invalid column index");
        }
        std::vector<Field> result(M);
        for (unsigned row = 0; row < M; row++)
        {
            result[row] = data[row][col];
        }
        return result;
    }




    Field& operator[](unsigned row)
    {
        if (row >= M)
        {
            throw std::invalid_argument("Invalid row index");
        }
        return data[row];
    }

    const Field& operator[](unsigned row) const
    {
        if (row >= M)
        {
            throw std::invalid_argument("Invalid row index");
        }
        return data[row];
    }




    Field& operator()(unsigned row, unsigned col)
    {
        if (row >= M || col >= N)
        {
            throw std::invalid_argument("Invalid indices");
        }
        return data[row][col];
    }

    const Field& operator()(unsigned row, unsigned col) const
    {
        if (row >= M || col >= N) 
        {
            throw std::invalid_argument("Invalid indices");
        }
        return data[row][col];
    }



    Field determinant(const std::vector<std::vector<Field>>& mat) const    // Вспомогательный метод для вычисления определителя
    {
        if (mat.size() == 1)
        {
            return mat[0][0];
        }
        else if (mat.size() == 2)
        {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }
        else
        {
            Field det = 0;
            int sign = 1;
            for (size_t i = 0; i < mat.size(); i++)
            {
                // Получаем минор матрицы.
                std::vector<std::vector<Field>> minor;
                for (size_t j = 1; j < mat.size(); j++)
                {
                    std::vector<Field> row;
                    for (size_t k = 0; k < mat.size(); k++)
                    {
                        if (k != i)
                        {
                            row.push_back(mat[j][k]);
                        }
                    }
                    minor.push_back(row);
                }
                det += sign * mat[0][i] * determinant(minor);
                sign = -sign;
            }
            return det;
        }
    }
    Field det() const //определитель
    {
        if (M != N)
        {
            throw std::invalid_argument("Only defined for square matrices");
        }
        if (M == 1)
        {
            return data[0][0];
        }
        else if (M == 2)
        {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        else
        {
            return determinant(data);
        }
    }


    // Вспомогательный метод для приведения матрицы к ступенчатому виду.
    void to_row_echelon_form(std::vector<std::vector<Field>>& mat) const
    {
        size_t lead = 0;
        for (size_t r = 0; r < mat.size(); r++)
        {
            if (lead >= mat[r].size()) break;
            size_t i = r;
            while (mat[i][lead] == 0)
            {
                i++;
                if (i == mat.size())
                {
                    i = r;
                    lead++;
                    if (lead == mat[r].size()) return;
                }
            }
            std::swap(mat[i], mat[r]);
            Field lv = mat[r][lead];
            for (size_t j = 0; j < mat[r].size(); j++) mat[r][j] /= lv;
            for (size_t i = 0; i < mat.size(); i++)
            {
                if (i != r)
                {
                    lv = mat[i][lead];
                    for (size_t j = 0; j < mat[r].size(); j++)
                    {
                        mat[i][j] -= lv * mat[r][j];
                    }
                }
            }
            lead++;
        }
    }
    unsigned rank() const // Ранг матрицы
    {
        std::vector<std::vector<Field>> tmp = data;
        to_row_echelon_form(tmp);
        unsigned rank = 0;
        for (size_t i = 0; i < tmp.size(); i++)
        {
            for (size_t j = 0; j < tmp[i].size(); j++)
            {
                if (tmp[i][j] != 0)
                {
                    ++rank;
                    break;
                }
            }
        }
        return rank;
    }


    Matrix<M, N, Field> inverted() const //вернуть обратную матрицу
    {
        if (M != N)
        {
            throw std::invalid_argument("Only defined for square matrices");
        }
        Field det = this->det();
        //если определитель равен нулю то значит что обратная матрица не существует
        if (det == Field(0))
        {
            throw std::invalid_argument("Matrix cannot be inverted");
        }
        Matrix<M, N, Field> obratn;
        for (unsigned i = 0; i < M; i++)
        {
            for (unsigned j = 0; j < N; j++)
            {

                std::vector<std::vector<Field>> minor;
                for (unsigned row = 0; row < M; row++)
                {
                    if (row == i) continue;
                    std::vector<Field> minorRow;
                    for (unsigned col = 0; col < N; col++)
                    {
                        if (col == j) continue;
                        minorRow.push_back(data[row][col]);
                    }
                    minor.push_back(minorRow);
                }
                Field minorDet = determinant(minor);
                Field cofactor;
                if ((i + j) % 2 == 0)
                {
                    cofactor = minorDet;
                }
                else
                {
                    cofactor = -minorDet;
                }
                obratn.set(j, i, cofactor);
            }
        }
        // Делим матрицу алгебраических дополнений на определитель
        for (unsigned i = 0; i < M; i++)
        {
            for (unsigned j = 0; j < N; j++)
            {
                obratn.set(i, j, obratn.get(i, j) / det);
            }
        }

        return obratn;
    }


    void invert() //обратить матрицу
    {
        *this = this->inverted();
    }







    void print() const
    {
        if (tr)
        {
            for (unsigned row = 0; row < N; row++)
            {
                for (unsigned col = 0; col < M; col++)
                {
                    std::cout << data[row][col] << " ";
                }
                std::cout << std::endl;
            }
        }
        else

        {
            for (unsigned row = 0; row < M; row++)
            {
                for (unsigned col = 0; col < N; col++)
                {
                    std::cout << data[row][col] << " ";
                }
                std::cout << std::endl;
            }
        }
    }




};


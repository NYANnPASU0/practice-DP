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


    unsigned get_M() const
    {
        return M;
    }
    unsigned get_N() const
    {
        return N;
    }

    Matrix operator+(const Matrix& other) const
    {
        if (this->get_M() != other.get_M() || this->get_N() != other.get_N())
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
        if (this->get_M() != other.get_M() || this->get_N() != other.get_N())
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
        if (this->get_M() != other.get_M() || this->get_N() != other.get_N())
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
        if (this->get_M() != other.get_M() || this->get_N() != other.get_N())
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
            result = result + data[i][i];
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



    Field determ(const std::vector<std::vector<Field>>& matrix) const
    {
        if (matrix.size() == 1)
        {
            return matrix[0][0];
        }
        else if (matrix.size() == 2)
        {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        else
        {
            Field det = 0;
            int sign = 1;
            for (size_t i = 0; i < matrix.size(); i++)
            {
                std::vector<std::vector<Field>> minor;
                for (size_t j = 1; j < matrix.size(); j++)
                {
                    std::vector<Field> row;
                    for (size_t k = 0; k < matrix.size(); k++)
                    {
                        if (k != i)
                        {
                            row.push_back(matrix[j][k]);
                        }
                    }
                    minor.push_back(row);
                }
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
            return determ(data);
        }
    }


    //приведениe матрицы к ступенчатому виду
    void stupench_vid(std::vector<std::vector<Field>>& matrix) const
    {
        int curr_elem = 0;
        for (int row = 0; row < matrix.size(); row++)
        {
            if (curr_elem >= matrix[row].size())
            {
                break;
            }
            int i = row;
            while (matrix[i][curr_elem] == 0)
            {
                i++;
                if (i == matrix.size())
                {
                    i = row;
                    curr_elem++;
                    if (curr_elem == matrix[row].size())
                    {
                        return;
                    }
                }
            }
            std::swap(matrix[i], matrix[row]);
            Field delitel = matrix[row][curr_elem];
            for (int j = 0; j < matrix[row].size(); j++)
            {
                matrix[row][j] /= delitel;
            }
            for (int i = 0; i < matrix.size(); i++)
            {
                if (i != row)
                {
                    delitel = matrix[i][curr_elem];
                    for (int j = 0; j < matrix[row].size(); j++)
                    {
                        matrix[i][j] = matrix[i][j] - (delitel * matrix[row][j]);
                    }
                }
            }
            curr_elem++;
        }
    }
    unsigned rank() const // Ранг матрицы
    {
        std::vector<std::vector<Field>> tmp = data;
        stupench_vid(tmp);
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
        //if (det == Field(0))
        //{
        //    throw std::invalid_argument("Matrix cannot be inverted");
        //}
        Matrix<M, N, Field> obratn;
        for (unsigned i = 0; i < M; i++)
        {
            for (unsigned j = 0; j < N; j++)
            {
                std::vector<std::vector<Field>> minor;
                for (unsigned row = 0; row < M; row++)
                {
                    if (row == i)
                    {
                        continue;
                    }
                    std::vector<Field> row_min;
                    for (unsigned col = 0; col < N; col++)
                    {
                        if (col == j)
                        {
                            continue;
                        }
                        row_min.push_back(data[row][col]);
                    }
                    minor.push_back(row_min);
                }
                Field determ_of_minor = determ(minor);
                Field sgn;
                if ((i + j) % 2 == 0)
                {
                    sgn = determ_of_minor;
                }
                else
                {
                    sgn = -determ_of_minor;
                }
                obratn.set(j, i, sgn);
            }
        }
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




    void print()
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


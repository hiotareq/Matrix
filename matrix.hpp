#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <numeric>
#include <typeinfo>
#include <cmath>

namespace matrix
{
    template <typename T>
    class matrix final
    {
    private:
        int n_; //количество строк/столбцов
        T **matrix_;

        struct row
        {
            T *row_;

            const T &operator[](int index) const
            {
                return row_[index];
            }

            T &operator[](int index)
            {
                return row_[index];
            }
        };

    public:
        int GetN() const
        {
            return n_;
        }

        matrix(int n)
        {
            n_ = n;
            matrix_ = new T *[n_];
            for (int i = 0; i < n_; ++i)
            {
                matrix_[i] = new T[n_];
            }
        };

        matrix() : matrix(0){};

        ~matrix()
        {
            for (int i = 0; i < n_; ++i)
            {
                delete[] matrix_[i];
            }
            delete[] matrix_;
        }

        matrix(const matrix &old)
        {
            n_ = old.GetN();
            matrix_ = new T *[n_];
            for (int i = 0; i < n_; ++i)
            {
                matrix_[i] = new T[n_];
            }

            for (int i = 0; i < n_; ++i)
            {
                for (int j = 0; j < n_; ++j)
                {
                    matrix_[i][j] = old.matrix_[i][j];
                }
            }
        }

        matrix(int n, bool flag)
        { //конструктор для единичной матрицы
            n_ = n;
            matrix_ = new T *[n_];
            for (int i = 0; i < n_; ++i)
            {
                matrix_[i] = new T[n_];
            }

            for (int i = 0; i < n_; ++i)
            {
                matrix_[i][i] = 1;
            }
        }

        const row operator[](int index) const
        {
            return row{matrix_[index]};
        }

        row operator[](int index)
        {
            return row{matrix_[index]};
        }

        T det()
        {
            double mem = 1;
            for (int i = 0; i < n_; ++i)
            {
                if (i == (n_ - 1))
                {
                    for(int k = 0; k < n_; ++k)
                    {
                        if(matrix_[k][i] != 0)
                        {
                            for(int j = 0; j < n_; ++j)
                            {
                                matrix_[i][j] += matrix_[k][j];
                                break;
                            }
                        }
                    }
                }

                if (matrix_[i][i] == 0)
                {
                    for (int k = i + 1; k < n_; ++k)
                    {
                        if (matrix_[k][i] != 0)
                        {
                            T* swap = matrix_[i];
                            matrix_[i] = matrix_[k];
                            matrix_[k] = swap;
                            mem *= pow((-1), (k - i));
                            break;
                        }
                        if (k == n_ - 1)
                            return 0; //here is col with 0-s
                    }                 
                }//after these actions matrix_[i][i] != 0

                for (int k = i + 1; k < n_; ++k)
                {
                    if (matrix_[k][i] == 0)
                    {
                        continue;
                    }


                    mem /= matrix_[i][i];
                    mem *= matrix_[k][i];
                    double tmp1 = matrix_[i][i], tmp2 = matrix_[k][i];
                    std::cout << "tmp1[" << i << "] = " << tmp1 << std::endl;

                    for (int c = 0; c < n_; ++c)
                    {
                        matrix_[i][c] /= tmp1;
                        matrix_[i][c] *= tmp2;
                    }

                    for (int c = 0; c < n_; ++c)
                        matrix_[k][c] -= matrix_[i][c];

                    for(int c = 0; c < n_; ++c)
                        matrix_[i][c] *= tmp1;
                }
            }

            double det = 1;
            for (int i = 0; i < n_; ++i)
                det *= matrix_[i][i];

            det /= mem;
            return det;
        }
    };
} // namespace matrix

template <typename T>
std::ostream &operator<<(std::ostream &os, const matrix::matrix<T> &matr)
{
    for (int i = 0; i < matr.GetN(); ++i)
    {
        for (int j = 0; j < matr.GetN(); ++j)
        {
            os << matr[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, matrix::matrix<T> &matr)
{
    for (int i = 0; i < matr.GetN(); ++i)
    {
        for (int j = 0; j < matr.GetN(); ++j)
        {
            is >> matr[i][j];
        }
    }
    return is;
}

#endif
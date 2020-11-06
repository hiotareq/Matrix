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

    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    int lcm(int a, int b)
    {
        if (a == 0 && b == 0)
            return 0;
        return a * b / gcd(a, b);
    }

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

        const row operator[](const int index) const
        {
            return row{matrix_[index]};
        }

        row operator[](int index)
        {
            return row{matrix_[index]};
        }

        T det() const
        {
            matrix tmp(*this);

            if (!(typeid(T).name() == typeid(int).name()))
            {
                matrix l(n_), u(n_);
                for (int i = 0; i < n_; ++i)
                { //тут смотрю, чтобы главные миноры не были равны нулю
                    if (tmp.matrix_[i][i] == 0)
                    {
                        for (int k = 0; k < n_; ++k)
                        {
                            if (k == i)
                                continue;

                            if (tmp.matrix_[k][i] != 0)
                            {
                                for (int j = 0; j < n_; ++j)
                                {
                                    tmp.matrix_[i][j] += tmp.matrix_[k][j];
                                }
                                break;
                            }
                            if (k == n_ - 1)
                                return 0; //тут есть столбец, где все нули
                        }
                    }

                    for (int j = 0; j < n_; ++j)
                    {
                        if (j < i)
                            l[j][i] = 0;
                        else
                        {
                            l[j][i] = tmp.matrix_[j][i];
                            for (int k = 0; k < i; ++k)
                            {
                                l[j][i] = l[j][i] - l[j][k] * u[k][i];
                            }
                        }
                    }
                    for (int j = 0; j < n_; ++j)
                    {
                        if (j < i)
                            u[i][j] = 0;
                        else if (j == i)
                            u[i][j] = 1;
                        else
                        {
                            if (l[i][i] == 0)
                                return 0; //тут есть элемент в l, который равен нулю
                            u[i][j] = tmp.matrix_[i][j] / l[i][i];
                            for (int k = 0; k < i; ++k)
                            {
                                u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                            }
                        }
                    }
                }
                float d = 1;
                for (int i = 0; i < n_; ++i)
                {
                    d *= l[i][i] * u[i][i];
                }
                return d;
            }
            else
            {
                int mem = 1;
                for (int i = 0; i < n_; ++i)
                {
                    if (i == n_ - 1)
                        break;

                    if (tmp.matrix_[i][i] == 0)
                    {

                        for (int k = i; k < n_; ++k)
                        {
                            if (tmp.matrix_[k][i] != 0)
                            {
                                std::swap(tmp.matrix_[i], tmp.matrix_[k]);
                                mem *= pow(-1, k - i);
                                break;
                            }
                            if (k == n_ - 1)
                                return 0; //тут на диагонали - 0, и под ним тоже нули
                        }

                        //после этих действий matrix_[i][i] != 0
                    }

                    for (int k = i + 1; k < n_; ++k)
                    {
                        int varlcm = lcm(tmp.matrix_[i][i], tmp.matrix_[k][i]);

                        if (varlcm != 0)
                        { //тут matrix_[i][i] and matrix_[k][i] одновременно не равны нулю

                            int ifactor = varlcm / tmp.matrix_[i][i];
                            for (int c = 0; c < n_; ++c)
                                matrix_[i][c] *= ifactor;

                            int kfactor = varlcm / tmp.matrix_[k][i];
                            for (int c = 0; c < n_; ++c)
                                tmp.matrix_[k][c] *= kfactor;

                            for (int c = 0; c < n_; ++c)
                                tmp.matrix_[k][c] -= tmp.matrix_[i][c];

                            for (int c = 0; c < n_; ++c)
                                tmp.matrix_[i][c] /= ifactor;

                            mem *= kfactor;
                        } //else matrix_[i][i] != 0, matrix_[k][i] = 0
                    }
                }

                int det = 1;
                for (int i = 0; i < n_; ++i)
                    det *= tmp.matrix_[i][i];

                det /= mem;
                return det;
            }
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
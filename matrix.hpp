#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <numeric>
#include <typeinfo>
#include <cmath>
#include <utility>

namespace matrix {
    template<typename T>
    class matrix final {
    private:
        int n_; //number of columns/rows
        T **matrix_;

        struct row {
            T *row_;

            const T &operator[](int index) const {
                return row_[index];
            }

            T &operator[](int index) {
                return row_[index];
            }
        };

    public:
        int GetN() const {
            return n_;
        }

        matrix(int n) {
            n_ = n;
            matrix_ = new T *[n_];
            for (int i = 0; i < n_; ++i) {
                matrix_[i] = new T[n_];
            }
            for (int i = 0; i < n_; ++i) {
                for (int j = 0; j < n_; ++j) {
                    matrix_[i][j] = 0;
                }
            }
        };

        matrix() : matrix(0) {};

        ~matrix() {
            for (int i = 0; i < n_; ++i) {
                delete[] matrix_[i];
            }
            delete[] matrix_;
        }

        matrix(const matrix &old) {
            n_ = old.GetN();
            matrix_ = new T *[n_];
            for (int i = 0; i < n_; ++i) {
                matrix_[i] = new T[n_];
            }

            for (int i = 0; i < n_; ++i) {
                for (int j = 0; j < n_; ++j) {
                    matrix_[i][j] = old.matrix_[i][j];
                }
            }
        }

        matrix(int n, bool flag) { //ctr for identity matrix
            n_ = n;
            matrix_ = new T *[n_];
            for (int i = 0; i < n_; ++i) {
                matrix_[i] = new T[n_];
            }

            for (int i = 0; i < n_; ++i) {
                for (int j = 0; j < n_; ++j) {
                    if(j == i) matrix_[i][j] = 1;
                    else    matrix_[i][j] = 0;
                }
            }
        }

        row operator[](int index) {
            return row{matrix_[index]};
        }

        const row operator[](int index) const {
            return row{matrix_[index]};
        }

        T det() {
            long double mem = 1;//variable to remember actions with determinant
            for (int i = 0; i < n_; ++i) {
                /*
                checking if matrix_[i][i] == 0, because we mustn't have it in Gauss method
                 */
                if (matrix_[i][i] == 0) {
                    for (int j = i + 1; j < n_; ++j) {
                        if (matrix_[j][i] != 0) {
                            std::swap(matrix_[i], matrix_[j]);
                            mem *= std::pow(-1, j - i);
                            break;
                        }
                    }
                }
                /*
                after these actions matrix_[i][i] != 0
                */

                for (int k = i + 1; k < n_; ++k) {//take a look at cells under diagonal

                    if (matrix_[k][i] != 0) {
                        std::cout << matrix_[i][i]<< std::endl;
                        long double tmp = matrix_[k][i] / matrix_[i][i];
                        mem /= tmp;
                        for (int j = 0; j < n_; ++j) {
                            matrix_[i][j] *= tmp;
                            matrix_[k][j] -= matrix_[i][j];//make cells under diagonal equal zero
                        }
                    }//else matrix_[k][i] == 0, do nothing
                }
            }
            long double det = 1;
            for (int i = 0; i < n_; ++i) {
                det *= matrix_[i][i];
            }

            det *= mem;
            return det;
        }
    };
} // namespace matrix

template<typename T>
std::ostream &operator<<(std::ostream &os, const matrix::matrix<T> &matr) {
    for (int i = 0; i < matr.GetN(); ++i) {
        for (int j = 0; j < matr.GetN(); ++j) {
            os << matr[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

template<typename T>
std::istream &operator>>(std::istream &is, matrix::matrix<T> &matr) {
    for (int i = 0; i < matr.GetN(); ++i) {
        for (int j = 0; j < matr.GetN(); ++j) {
            is >> matr[i][j];
        }
    }
    return is;
}

#endif
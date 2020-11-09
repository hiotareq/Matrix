#include "matrix.hpp"

int main() {
    int n;
    std::cin >> n;
    matrix::matrix<long double> matr(n);
    std::cin >> matr;
    std::cout << matr.det();
    return 0;
}
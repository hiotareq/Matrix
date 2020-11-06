#include "matrix.hpp"

int main()
{
    unsigned int n;
    std::cin >> n;
    matrix::matrix<float> matr(n);
    std::cin >> matr;
    std::cout << matr.det() << std::endl;
    return 0;
}
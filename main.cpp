#include "matrix.hpp"

int main()
{
    int n;
    std::cin >> n;
    matrix::matrix<double> matr(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j) std::cin >> matr[i][j];
    }
    std::cout << matr.det() << std::endl;
    return 0;
}

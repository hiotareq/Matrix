#include "matrix.hpp"
#include <fstream>
#include <cstdlib>
#include <ctime>

#if 0
int main()
{
    matrix::matrix<int> matr;
    std::fstream det;
    det.open("C:\\Users\\bobro\\Desktop\\matrix\\Matrix\\identity_matrix_1000x1000.txt");
    det >> matr;
    std :: cout << matr.det();
    return 0;
}
#endif

int main(){
    int n;
    std::cin >> n;
    matrix::matrix<double> matr(n);
    std::cin >> matr;
    std::cout << matr.det();
    return 0;
}

#if 0
int main()
{
    std::fstream det;
    det.open("C:\\Users\\bobro\\Desktop\\matrix\\Matrix\\identity_matrix_1000x1000.txt");
    int n = 1000;
    det << n << std::endl;
    matrix::matrix<int>* matr = new matrix::matrix<int>;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            (*matr)[i][j] = std::rand();
        }
    }
    det << matr;
    std::cout << (*matr).det() << std::endl;
    return 0;
}
#endif
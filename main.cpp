#include "matrix.hpp"

int main()
{
    unsigned int n;
    bool flag;
    std::cout << "Введите количество строк/столбцов квадратной матрицы" << std::endl;
    std::cin >> n;
    std::cout << "Выберите тип данных в матрице: 0 - int, 1 - other" << std::endl;
    std::cin >> flag;
    if (flag == 0)
    {
        matrix::matrix<int> matr(n);
        std::cout << "Введите матрицу" << std::endl;
        std::cin >> matr;
        std::cout << "Определитель матрицы = " << matr.det() << std::endl;
    }
    else
    {
        matrix::matrix<float> matr(n);
        std::cout << "Введите матрицу" << std::endl;
        std::cin >> matr;
        std::cout << "Определитель матрицы = " << matr.det() << std::endl;
    }
    return 0;
}
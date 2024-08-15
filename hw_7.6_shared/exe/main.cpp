#include <iostream>

using real = double;

struct Matrix;

#ifdef __cplusplus
extern "C"
{
#endif
    extern Matrix *math_createMatrix(int, int);
    extern void math_set(Matrix *, int, int, double);
    extern void math_print(Matrix *);
    extern void math_deleteMatrix(Matrix *);
    extern real math_get(const Matrix *, int, int);
    extern Matrix *math_add(const Matrix *, const Matrix *);
    extern Matrix *math_subtract(const Matrix *, const Matrix *);
    extern Matrix *math_dot(const Matrix *, const Matrix *);
#ifdef __cplusplus
}
#endif

int main()
{
    Matrix *m = math_createMatrix(3, 3);
    Matrix *m1 = math_createMatrix(3, 3);

    math_set(m, 0, 1, 1);
    math_set(m, 0, 2, 2);
    math_set(m, 0, 0, 3);
    math_set(m, 1, 0, 6);

    std::cout << "Matrix m = " << std::endl;
    math_print(m);

    math_set(m1, 0, 1, 2);
    math_set(m1, 0, 2, 3);
    math_set(m1, 0, 0, 4);
    math_set(m1, 1, 0, 8);

    std::cout << "Matrix m1 = " << std::endl;
    math_print(m1);

    Matrix *m2 = math_add(m, m1);

    std::cout << "Matrix m + Matrix m1 = " << std::endl;
    math_print(m2);

    return 0;
}
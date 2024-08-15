#include "c_api.h"
#include <matrix.h>

struct Matrix : public M_math::Matrix
{
public:
    Matrix(const struct M_math::Matrix &M) : M_math::Matrix(M) {};
};

Matrix *MATRIXLIB_EXPORT math_createMatrix(int rows, int cols)
{
    return new Matrix(M_math::Matrix(rows, cols));
}

void MATRIXLIB_EXPORT math_deleteMatrix(Matrix *M)
{
    delete M;
}

real MATRIXLIB_EXPORT math_get(const Matrix *M, int row, int col)
{
    return M->operator()(row, col);
}

void MATRIXLIB_EXPORT math_set(Matrix *M, int row, int col, real val)
{
    M->operator()(row, col) = val;
}

Matrix *MATRIXLIB_EXPORT math_add(const Matrix *A, const Matrix *B)
{
    return new Matrix(*A + *B);
}

Matrix *MATRIXLIB_EXPORT math_subtract(const Matrix *A, const Matrix *B)
{
    return new Matrix(*A - *B);
}

Matrix *MATRIXLIB_EXPORT math_dot(const Matrix *A, const Matrix *B)
{
    return new Matrix(*A * *B);
}

void MATRIXLIB_EXPORT math_EQadd(const Matrix *A, const Matrix *B)
{
    A = math_add(A, B);
}

void MATRIXLIB_EXPORT math_EQsubtract(const Matrix *A, const Matrix *B)
{
    A = math_subtract(A, B);
}

void MATRIXLIB_EXPORT math_EQdot(const Matrix *A, const Matrix *B)
{
    A = math_dot(A, B);
}

void MATRIXLIB_EXPORT math_print(const Matrix *M)
{
    M->print();
}

#include <matrix.h>
#include <iostream>
#include <cmath>

using namespace M_math;

real& Matrix::operator()(int row, int col)
{
    if (row >= this->rows_)
    {
        std::cerr << "Matrix: row number out of bounds" << std::endl;
    }
    if (col >= this->cols_)
    {
        std::cerr << "Matrix col number out of bounds" << std::endl;
    }

    int pos{0};

    pos = this->cols_ * row + col;

    return this->mvec_.at(pos);
}

const real& Matrix::operator()(int row, int col) const {
    if (row >= this->rows_) {
        std::cerr << "Matrix: row number out of bounds" << std::endl;
    }
    if (col >= this->cols_) {
        std::cerr << "Matrix col number out of bounds" << std::endl;
    }

    int pos = this->cols_ * row + col;
    return this->mvec_.at(pos);
}

void Matrix::print() const
{
    for (int i = 0; i < this->rows_;++i)
    {
        for (int j = 0; j < this->cols_; ++j)
        {
            std::cout << this->mvec_.at(cols_ * i + j) << " ";
        }
        std::cout << std::endl;
    }
}

Matrix M_math::operator+(const Matrix& A, const Matrix& B)
{
    if((A.cols_ != B.cols_) || (A.rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be added!" << std::endl;
    }

    Matrix M(A.cols_,A.rows_);

    for (int i = 0; i < M.mvec_.size();++i)
    {
        M.mvec_.at(i) = A.mvec_.at(i) + B.mvec_.at(i);
    }
    return M;
}

Matrix M_math::operator-(const Matrix& A, const Matrix& B)
{
    if((A.cols_ != B.cols_) || (A.rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be subtracted!" << std::endl;
    }

    Matrix M(A.cols_,A.rows_);

    for (int i = 0; i < M.mvec_.size();++i)
    {
        M.mvec_.at(i) = A.mvec_.at(i) - B.mvec_.at(i);
    }
    return M;
}

Matrix M_math::operator*(const Matrix& A, const Matrix& B)
{
    if(A.cols_ != B.rows_)
    {
        std::cerr << "Matrix: Matrices can't be multiplied!" << std::endl;
    }

    Matrix M(A.rows_,B.cols_);

    for (int pos = 0; pos < M.mvec_.size();++pos)
    {
        int row = pos/M.cols_;
        int col = pos - row*M.cols_;

        for (int k = 0; k < A.cols_; ++k)
        {
            M.mvec_.at(pos) += A(row,k)*B(k,col);
        }
    }

    return M;
}

Matrix& Matrix::operator+=(const Matrix& B)
{
    if((this->cols_ != B.cols_) || (this->rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be added!" << std::endl;
    }

    *this = *this + B;

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& B)
{
    if((this->cols_ != B.cols_) || (this->rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be subtracted!" << std::endl;
    }

    *this = *this - B;

    return *this;
}

Matrix& Matrix::operator*=(const Matrix& B)
{
    if((this->cols_ != B.cols_) || (this->rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be multiplied!" << std::endl;
    }

    *this = *this * B;

    return *this;
}

#pragma once
#include <vector>
#include <iostream>

namespace M_math
{
    using real = double;
    
    class Matrix
    {
        private:
            int cols_;
            int rows_;
            std::vector<real> mvec_;
        public:
            Matrix(){};

            Matrix(int rows, int cols): cols_(cols), rows_(rows), mvec_(std::vector<real>(rows * cols)){};

            real& operator()(int row, int col);

            const real& operator()(int row, int col) const;

            void print();

            friend Matrix operator+(const Matrix& A, const Matrix& B);

            friend Matrix operator-(const Matrix& A, const Matrix& B);

            friend Matrix operator*(const Matrix& A, const Matrix& B);

            Matrix& operator+=(const Matrix& B);

            Matrix& operator-=(const Matrix& B);

            Matrix& operator*=(const Matrix& B);

            friend std::ostream& operator<<(std::ostream& os, const Matrix& A)
            {
                for (int i = 0; i < A.rows_;++i)
                {
                    for (int j = 0; j < A.cols_; ++j)
                    {
                        os << A.mvec_.at(A.cols_ * i + j) << " ";
                    }

                    os << std::endl;
                }

                return os;
            }

            friend std::istream& operator>>(std::istream& is, Matrix& A) 
            {
                for (int i = 0; i < A.mvec_.size(); ++i)
                {
                    is >> A.mvec_.at(i);
                }

                return is;
            }
    };
}
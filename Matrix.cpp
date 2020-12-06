#include<iostream>
#include <omp.h>
#include"Matrix.hpp"

Matrix::Matrix()
{
    std::cout << "an empty matrix was created\n";
    data = NULL;
    mat_count = new int;
    *mat_count = 0;
    row = column = 0;
}

Matrix::Matrix(int row, int column)
{
    data = new float[row * column];
    this->row = row;    
    this->column = column;
    mat_count = new int;
    *(mat_count) = 1;
    std::cout << *mat_count << " same matrix created\n";
}

Matrix::Matrix(float* data, int row, int column)
{
    this->data = data;
    this->row = row;
    this->column = column;
    mat_count = new int;
    *(mat_count) = 1;
    std::cout << *mat_count << " same matrix created\n";
}

Matrix::Matrix(const Matrix& matrix)
{
    row = matrix.row;
    column = matrix.column;
    data = matrix.data;
    mat_count = matrix.mat_count;
    ++ *(mat_count);
    std::cout << *mat_count << " same matrix created\n"; 
}

Matrix::~Matrix()
{
    release();
}

Matrix& Matrix:: operator = (const Matrix& matrix)
{
    if (this == &matrix)
        return *this;
    else 
    {
        data = matrix.data;
        mat_count = matrix.mat_count;
        row = matrix.row;
        column = matrix.column;
        ++ *(mat_count);
        std::cout << *(mat_count) << " same matrix created\n";
        return *this;
    }
}

Matrix Matrix:: operator* (const Matrix& matrix) const
{
    Matrix c(this->row, matrix.column);
    int i=0, j=0 , k=0;
    #pragma omp parallel for
        for (i = 0; i < this->row; i++)
            for (k = 0; k < this->column; k++)
                for (j = 0; j < matrix.column; j++)
                    c.data[i * c.column + j] += this->data[i * this->column + k] * matrix.data[k * matrix.column + j];
    return c;
}

Matrix Matrix::operator * (float mult) const
{
    Matrix result (this->row, this->column);
    for(int i=0; i<this->row*this->column; i++)
        result.data[i] = this->data[i] * mult;
    return result;
}

Matrix operator * (float mult, const Matrix& matrix)
{
    Matrix result(matrix.row, matrix.column);
    for (int i=0; i<matrix.row* matrix.column; i++)
        result.data[i] = mult * matrix.data[i];
    return result;
}

void Matrix::release()
{
    std::cout << *(mat_count) << " " << data << " lefted\n";
    if (mat_count == NULL ||*(mat_count) <= 1)
    {
        std::cout<< "delete\n";
        delete mat_count;
    }
    else
        -- *(mat_count);
}



std::ostream & operator << (std::ostream& os, const Matrix& matrix)
{
    os << "[";
    for(int i=0; i<matrix.row-1; i++)
    {
        for(int j=0; j<matrix.column-1; j++)
            os << " " << matrix.data[i*matrix.column + j] << ",";
        os << " " <<matrix.data[i*matrix.column +matrix.column-1] << ";\n";
    }
    for (int j=0; j<matrix.column-1; j++)
        os << " " << matrix.data[(matrix.row-1)*matrix.column + j] << ",";
    os << " " << matrix.data[matrix.row*matrix.column - 1] <<"]\n";
    return os;
}

int Matrix::getColumn()
{
    return this->column;
}

int Matrix::getRow()
{
    return this->row;
}

float* Matrix::getData()
{
    return this->data;
}
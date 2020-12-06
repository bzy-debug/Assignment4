#ifndef MATRIX
#define MATRIX
class Matrix
{
private:
    int* mat_count;
    float* data;
    int row;
    int column;
    void release();
public:
    Matrix();
    Matrix(int row, int column);
    Matrix(float* data, int row, int column);
    Matrix(const Matrix&);
    ~Matrix();
    Matrix& operator = (const Matrix& matrix);
    Matrix operator * (const Matrix& matrix) const;
    Matrix operator * (float mult) const;
    friend Matrix operator * (float mult, const Matrix& matrix);
    friend std::ostream & operator << (std::ostream& os, const Matrix& matrix);
    int getRow();
    int getColumn();
    float* getData();
};
#endif
#include<iostream>
#include "Matrix.hpp"
using namespace std;
float sum(Matrix x);
int main()
{
    float a[25];
    for (int i=0; i<5;i++)
        for(int j=0; j<5;j++)
            a[i*5+j] = i+j;
    Matrix A(a,5,5);
    cout << A;
    Matrix B, D;
    B = A;
    Matrix C (B);
    cout << A*B;
    cout << 2*A;
    cout << A*2;
    cout << sum(A) << endl;
    Matrix E = A*2;
    cout << E;
}

float sum(Matrix x)
{
    float sum = 0;
    int row = x.getRow();
    int colunm = x.getColumn();
    float* data = x.getData();
    for(int i=0; i< row*colunm; i++)
        sum += data[i];
    return sum;
}
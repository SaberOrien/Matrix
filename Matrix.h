#pragma once
#include <iostream>
#include <exception>
//#include <stdio.h>

class Matrix{
private:
    struct matrix;
    matrix* mat;
public:
    class Cref;
    Matrix();
    Matrix(const char* fileName);
    Matrix(const Matrix& source_mat);
    Matrix& operator=(const Matrix& source_mat);
    ~Matrix();

    Matrix operator+(const Matrix& m2) const;
    Matrix& operator+=(const Matrix& m2);
    Matrix operator-(const Matrix& m2) const;
    Matrix& operator-=(const Matrix& m2);
    Matrix operator*(const Matrix& m2) const;
    Matrix& operator*=(const Matrix& m2);

    bool operator==(const Matrix& m2) const;
    bool operator!=(const Matrix& m2) const;

    int use_count();
    friend std::ostream& operator << (std::ostream& o, const Matrix &m);

    //double operator()(int row, int col) const;
    void check(int row, int col) const;
    double read(int row, int col) const;
    void write(int row, int col, double newValue);
    Cref operator()(int row, int col);
};

class Matrix::Cref{
    friend class Matrix;
    Matrix& mat;
    int row, col;
    Cref(Matrix& MM, int rr, int cc) : mat(MM), row(rr), col(cc){};
public:
    operator double() const;
    Matrix::Cref& operator=(double newValue);
    Matrix::Cref& operator=(const Cref& ref);
};
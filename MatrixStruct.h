#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include "Matrix.h"

struct Matrix::matrix{
    double** data;
    int refCount;
    int rows;
    int cols;

    matrix();
    matrix(const char* fileName);
    matrix(int s_row, int s_col, double** s_data);
    matrix(int s_row, int s_col);
    ~matrix();

    void allocateMem();
    void add(const struct matrix* m2);
    void sub(const struct matrix* m2);
    void mul(const struct matrix* m1, const struct matrix* m2);
    matrix* detach();
};
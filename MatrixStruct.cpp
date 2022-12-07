#include "Matrix.h"
#include "MatrixStruct.h"
#include "Exception.h"

using namespace std;

Matrix::matrix::matrix(){
    rows = 0;
    cols = 0;
    data = NULL;
    refCount = 1;
}

Matrix::matrix::matrix(const char* fileName){
    fstream inputFile;
    inputFile.open(fileName, ios::in);
    if(inputFile.is_open() == 0){
        throw file_not_opened();
    }
    inputFile >> rows;
    inputFile >> cols;

    allocateMem();
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            inputFile >> data[row][col];
        }
    }
    inputFile.close(); 
    refCount = 1;
}

Matrix::matrix::~matrix(){
    for(int row = 0; row < rows; row++){
        delete[] data[row];
    }
    delete[] data;
}

void Matrix::matrix::allocateMem(){
    data = new double*[rows];
    for(int row = 0; row < rows; row++){
        data[row] = new double[cols];
    }
}

Matrix::matrix::matrix(int s_row, int s_col, double** s_data){
    if(s_data != NULL){
        rows = s_row;
        cols = s_col;
        refCount = 1;
        allocateMem();
        for(int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                data[row][col] = s_data[row][col];
            }
        }
    }
    else{
        rows = 0;
        cols = 0;
        refCount = 1;
        data = NULL;
    }
}

Matrix::matrix::matrix(int s_row, int s_col){
    rows = s_row;
    cols = s_col;
    allocateMem();
    refCount = 1;
}

void Matrix::matrix::add(const struct matrix* m2){
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            data[row][col] += m2->data[row][col];
        }
    }
}

void Matrix::matrix::sub(const struct matrix* m2){
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            data[row][col] -= m2->data[row][col];
        }
    }
}

void Matrix::matrix::mul(const struct matrix* m1, const struct matrix* m2){
    matrix* result = new matrix(m1->rows, m2->cols);
    double mulResult = 0;
    for(int row1 = 0; row1 < m1->rows; row1++){
        for(int col2 = 0; col2 < m2->cols; col2++){
            mulResult = 0;
            for(int row2 = 0; row2 < m2->rows; row2++){
                mulResult += m1->data[row1][row2] * m2->data[row2][col2];
            }
            result->data[row1][col2] = mulResult;
        }
    }

    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            data[row][col] = result->data[row][col];
        }
    }
    delete result;
}

Matrix::matrix* Matrix::matrix::detach(){
    if(refCount == 1){
        return this;
    }
    matrix* newMatrix = new matrix(rows, cols, data);
    refCount--;
    return newMatrix;
}
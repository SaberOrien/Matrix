#include "Matrix.h"
#include <iostream>
#include <exception>
#include "Exception.h"

using namespace std;

void testAddition(const Matrix& A, const Matrix& B, const Matrix& C);
void testSubtraction(const Matrix& A, const Matrix& B, const Matrix& C);
void testMultiplication(const Matrix& A, const Matrix& B, const Matrix& C);
void testEqual(const Matrix& A, const Matrix& B, const Matrix& C);
void testRead(const Matrix& A);
void testWrite(const Matrix& A);
void testRefCount(Matrix& A, Matrix& B, Matrix& C);
void printMatrixAndCount(Matrix& A, Matrix& B, Matrix& C);

int main(){
    try{       
        Matrix m1("Matrix_1.txt");
        Matrix m2("Matrix_2.txt");
        Matrix m3("Matrix_3.txt");
        Matrix m4("Matrix_4.txt");
        cout << "___Matrix_1___\n" << m1 << endl;
        cout << "___Matrix_2___\n" << m2 << endl;
        cout << "___Matrix_3___\n" << m3 << endl;
        cout << "___Matrix_4___\n" << m4 << endl;
        //cout << "m1 used: " << m1.use_count() << endl;
        Matrix m5(m1);
        Matrix m6;
        m6 = m1;
        cout << "___Matrix_5___\n" << m5 << endl;
        cout << "___Matrix_6___\n" << m6 << endl;

        testAddition(m1, m2, m4);
        testSubtraction(m1, m2, m4);
        testMultiplication(m2, m3, m4);
        testEqual(m1, m2, m3);
        testRead(m1);
        testWrite(m1);
        testRefCount(m1, m4, m5);
    }
    catch(file_not_opened& fno){
        cout << fno.what() << endl;
    }
    return 0;
}

void testAddition(const Matrix& m1, const Matrix& m2, const Matrix& m4){
    cout << "\n===TestAddition===" << endl;
    try{
        Matrix m7;
        cout << "m1 + m4 = m7:" << endl;
        m7 = m1 + m4;
        cout << m7 << endl;
        cout << "m7 += m4" << endl;
        m7 += m4;
        cout << m7 << endl;
        cout << "m1 + m2 = m7" << endl;
        m7 = m1 + m2;
        cout << m7 << endl;
    }
    catch(incompatible_dimensions& id){
        cout << id.what() << endl;
    }
}

void testSubtraction(const Matrix& m1, const Matrix& m2, const Matrix& m4){
    cout << "\n===TestSubtraction===" << endl;
    try{
        Matrix m8;
        cout << "m4 - m1 = m8:" << endl;
        m8 = m4 - m1;
        cout << m8 << endl;
        cout << "m8 -= m4" << endl;
        m8 -= m4;
        cout << m8 << endl;
        cout << "m1 - m2 = m8:" << endl;
        m8 = m1 - m2;
        cout << m8 << endl;
    }
    catch(incompatible_dimensions& id){
        cout << id.what() << endl;
    }
}

void testMultiplication(const Matrix& m2, const Matrix& m3, const Matrix& m4){
    cout << "\n===TestMultiplication===" << endl;
    try{
        Matrix m9;
        cout << "m3 * m4 = m9" << endl;
        m9 = m3 * m4;
        cout << m9 << endl;
        cout << "m9 *= m4" << endl;
        m9 *= m4;
        cout << m9 << endl;
        cout << "m9 *= m2" << endl;
        m9 *= m2;
        cout << m9 << endl;
    }
    catch(incompatible_dimensions& id){
        cout << id.what() << endl;
    }
}

void testEqual(const Matrix& m1, const Matrix& m2, const Matrix& m3){
    cout << "\n===TestEqual===" << endl;
    Matrix m5(m1);
    Matrix m6;
    cout << "Where:\n\tm5 is copy of m1 and" << endl;
    cout << "\tm6 is new empty matrix." << endl;
    cout << "m1 == m2 " << (m1 == m2) << endl;
    cout << "m1 == m3 " << (m1 == m3) << endl;
    cout << "m1 == m5 " << (m1 == m5) << endl; 
    cout << "m1 != m2 " << (m1 != m2) << endl;
    cout << "m1 != m3 " << (m1 != m3) << endl;
    cout << "m1 != m5 " << (m1 != m5) << endl; 
    cout << "m5 == m6 " << (m5 == m6) << endl;
}

void testRead(const Matrix& A){
    Matrix m1(A);
    try{
        cout << "\n===Test Read===" << endl;
        cout << "\n===Matrix_1===\n" << m1 << endl;
        cout << "m1[0][0] = " << m1(0,0) << endl;
        cout << "m1[1][2] = " << m1(1,2) << endl;
        cout << "m1[4][5] = " << m1(4,5) << endl;
    }
    catch(out_of_bounds& oob){
        cout << oob.what() << endl;
    }
}

void testWrite(const Matrix& A){
    Matrix m1(A);
    try{
        cout << "\n===Test Write===" << endl;
        cout << "\n===Matrix_1===\n" << m1 << endl;
        cout << "m1[0][0] = 7" << endl;
        m1(0,0) = 7;
        cout << m1 << endl;
        cout << "m1[1][2] = 7" << endl;
        m1(1,2) = 7;
        cout << m1 << endl;
        cout << "m1[2][2] = 7" << endl;
        m1(2,2) = 7;
        cout << m1 << endl;
    }
    catch(out_of_bounds& oob){
        cout << oob.what() << endl;
    }
}

void testRefCount(Matrix& m1, Matrix& m4, Matrix& m5){
    cout << "\n----Pre-changes----" << endl;
    printMatrixAndCount(m1, m4, m5);
    cout << "\nAction: m1 + m4" << endl;
    m1 + m4;
    cout << "\nPost-action: " << endl;
    printMatrixAndCount(m1, m4, m5);
    cout << "\nAction: m1 += m4" << endl;
    m1 += m4;
    cout << "\nPost-action: " << endl;
    printMatrixAndCount(m1, m4, m5);
}

void printMatrixAndCount(Matrix& m1, Matrix& m4, Matrix& m5){
    cout << "\n___Matrix_1___\n" << m1;
    cout << "m1 ref count: " << m1.use_count() << endl;
    cout << "\n___Matrix_4___\n" << m4;
    cout << "m4 ref count: " << m4.use_count() << endl;
    cout << "\n___Matrix_5___\n" << m5;
    cout << "m5 ref count: " << m5.use_count() << endl;
}
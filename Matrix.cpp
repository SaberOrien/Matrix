#include "Exception.h"
#include "Matrix.h"
#include "MatrixStruct.h"

using namespace std;

Matrix::Matrix()
{
	mat = new matrix();
}

Matrix::Matrix(const char* fileName)
{
	mat = new matrix(fileName);
}

Matrix::Matrix(const Matrix& source_mat)
{
	source_mat.mat->refCount++;
	mat = source_mat.mat;
}

Matrix& Matrix::operator=(const Matrix& source_mat)
{
	if (--mat->refCount == 0) {
		delete mat;
	}

	mat = source_mat.mat;
	mat->refCount++;
	return *this;
}

Matrix::~Matrix()
{
	if (--mat->refCount == 0) {
		delete mat;
	}
}

int Matrix::use_count()
{
	return mat->refCount;
}

ostream& operator<<(ostream& o, const Matrix& m)
{
	for (int row = 0; row < m.mat->rows; row++) {
		for (int col = 0; col < m.mat->cols; col++) {
			o << m.mat->data[row][col] << " ";
		}
		o << "\n";
	}
	return o;
}

Matrix Matrix::operator+(const Matrix& m2) const
{
	return Matrix(*this) += m2;
}

Matrix& Matrix::operator+=(const Matrix& m2)
{
	if (!(mat->cols == m2.mat->cols && mat->rows == m2.mat->rows)) {
		throw incompatible_dimensions();
	}
	mat = mat->detach();
	mat->add(m2.mat);
	return *this;
}

Matrix Matrix::operator-(const Matrix& m2) const
{
	return Matrix(*this) -= m2;
}

Matrix& Matrix::operator-=(const Matrix& m2)
{
	if (!(mat->cols == m2.mat->cols && mat->rows == m2.mat->rows)) {
		throw incompatible_dimensions();
	}
	mat = mat->detach();
	mat->sub(m2.mat);
	return *this;
}

Matrix Matrix::operator*(const Matrix& m2) const
{
	return Matrix(*this) *= m2;
}

Matrix& Matrix::operator*=(const Matrix& m2)
{
	if (!(mat->cols == m2.mat->rows && mat->rows == m2.mat->cols)) {
		throw incompatible_dimensions();
	}
	matrix* result = new matrix(mat->rows, mat->cols);
	result->mul(mat, m2.mat);
	if (--mat->refCount == 0) {
		delete mat;
	}
	mat = result;
	return *this;
}

bool Matrix::operator==(const Matrix& m2) const
{
	if (mat->data == NULL || m2.mat->data == NULL) {
		return false;
	}

	if (!(mat->rows == m2.mat->rows && mat->cols == m2.mat->cols)) {
		return false;
	}

	for (int row = 0; row < mat->rows; row++) {
		for (int col = 0; col < mat->cols; col++) {
			if (mat->data[row][col] != m2.mat->data[row][col]) {
				return false;
			}
		}
	}

	return true;
}

bool Matrix::operator!=(const Matrix& m2) const
{
	return !(*this == m2);
}

void Matrix::check(int row, int col) const
{
	if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
		throw out_of_bounds();
	}
}

double Matrix::read(int row, int col) const
{
	return mat->data[row][col];
}

void Matrix::write(int row, int col, double newValue)
{
	mat = mat->detach();
	mat->data[row][col] = newValue;
}

Matrix::Cref::operator double() const
{
	return mat.read(row, col);
}

Matrix::Cref Matrix::operator()(int row, int col)
{
	check(row, col);
	return Cref(*this, row, col);
}

Matrix::Cref& Matrix::Cref::operator=(double newValue)
{
	mat.write(row, col, newValue);
	return *this;
}

Matrix::Cref& Matrix::Cref::operator=(const Cref& ref)
{
	return operator=((double)ref);
}

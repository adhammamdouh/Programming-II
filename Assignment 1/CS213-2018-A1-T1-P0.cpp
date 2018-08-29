// Course:  CS213 - Programming II  - 2018
// Title:   Assignment I - Task 1 - Problem 0
// Program: CS213-2018-A1-T1-P0
// Purpose: Skeleton code for the student to start working
// Author:  Ahmed Nasr Eldardery
// Date:    29 August 2018
// Version: 1.0

#include <iostream>
#include <iomanip>

using namespace std;

struct matrix
{
	int** data;
	int row, col;

	matrix(const int row, const int col) {
		this->row = row;
		this->col = col;
		if (row + col == 0) return;

		data = new int*[row];

		for (int i = 0; i < row; i++)
			data[i] = new int[col];
	}
	matrix(const matrix& old) {
		*this = old;
	}
	matrix(const int row, const int col, const int* num) {
		this->row = row;
		this->col = col;
		data = new int*[row];

		for (int i = 0; i < row; i++) {
			data[i] = new int[col];
			for (int j = 0; j < col; j++)
				data[i][j] = *(num++);
		}

	}
	matrix& operator=(const matrix& old) {

		this->row = old.row;
		this->col = old.col;
		if (old.row + old.col == 0) return *this;

		data = new int*[row];

		for (int i = 0; i < row; i++) {
			data[i] = new int[col];
			for (int j = 0; j < col; j++)
				data[i][j] = old[i][j];
		}
		return *this;
	}
	
	int* operator[] (int i) const {
		return data[i];
	}
	
	~matrix() {
		if (row + col == 0) return;
		for (int i = 0; i < row; i++)
			delete[] data[i];
		delete[] data;
	}
	
};

matrix operator+  (const matrix& mat1, const matrix& mat2); // Add if same dimensions
matrix operator-  (const matrix& mat1, const matrix& mat2); // Sub if same dimensions
matrix operator-  (const matrix& mat1);                     // Unary negative
matrix operator*  (const matrix& mat1, const matrix& mat2); // Multi if col1 == row2
matrix operator+  (const matrix& mat1, const int scalar);   // Add a scalar
matrix operator+  (const int scalar, const matrix& mat1);   // Add a scalar
matrix operator-  (const matrix& mat1, const int scalar);   // Subtract a scalar
matrix operator-  (const int scalar, const matrix& mat1);   // Subtract a scalar
matrix operator*  (const matrix& mat1, const int scalar);   // Multiple by scalar
matrix operator*  (const int scalar, const matrix& mat1);   // Multiple by scalar

matrix& operator+= (matrix& mat1, const matrix& mat2);      // mat1 changes & return new matrix with the sum
matrix& operator-= (matrix& mat1, const matrix& mat2);      // mat1 changes + return new matrix with difference
matrix& operator+= (matrix& mat, const int scalar);         // change mat & return new matrix
matrix& operator-= (matrix& mat, const int scalar);         // change mat & return new matrix
matrix& operator++ (matrix& mat);                           // Add 1 to each element ++mat (prefix)
matrix  operator++ (matrix& mat, int);                      // Add 1 to each element mat++
matrix& operator-- (matrix& mat);    	                    // Sub 1 from each element --mat
matrix  operator-- (matrix& mat, int);    	                // Sub 1 from each element mat--

istream& operator>> (istream& in, matrix& mat);
ostream& operator<< (ostream& out, const matrix& mat);

bool   operator== (const matrix& mat1, const matrix& mat2);	// True if identical
bool   operator!= (const matrix& mat1, const matrix& mat2); // True if not same

bool   is_square(const matrix& mat);  // True if square matrix
bool   is_symetric(const matrix& mat);  // True if square and symmetric
bool   is_identity(const matrix& mat);  // True if square and identity
matrix transpose(const matrix& mat);    // Return new matrix with the transpose

int main()
{
	int data1[] = { 1,2,3,4,5,6,7,8 };
	int data2[] = { 13,233,3,4,5,6 };
	int data3[] = { 10,100,10,100,10,100,10,100 };

	for (int i = 0; i < 1e5; ++i) {
		matrix test(100, 100);
	}
	matrix mat1(4, 2, data1),
		mat2(2, 3, data2),
		mat3(4, 2, data3),
		mat4 = mat3 * 2 + mat1 * 7;
	cout << mat1 << endl;
	cout << mat2 << endl;
	cout << mat3 << endl;
	cout << mat4 << endl;
	cout << (mat1 + mat3) << endl << endl;
	cout << (mat3 + mat3) << endl << endl;

	cout << ++++++mat1 << endl;
	cout << mat1++ << endl;
	cout << ----mat1 << endl;

	mat1 += mat3 += mat3;
	cout << mat1 << endl;
	cout << mat2 << endl;
	cout << mat3 << endl;
	return 0;
}

matrix operator+(const matrix& mat1, const matrix& mat2)
{
	if (mat1.col != mat2.col || mat1.row != mat1.row) return matrix(0,0);
	matrix mat(mat1.row, mat1.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat[i][j] = mat1[i][j] + mat2[i][j];
	return mat;
}

matrix operator-(const matrix& mat1, const matrix& mat2)
{
	if (mat1.col != mat2.col || mat1.row != mat1.row) return matrix(0, 0);
	matrix mat(mat1.row, mat1.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat[i][j] = mat1[i][j] - mat2[i][j];

	return mat;
}
matrix operator-(const matrix& mat1) {
	matrix mat = matrix(mat1.row, mat1.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat[i][j] = -mat1[i][j];
	return mat;
}

matrix operator*(const matrix& mat1, const matrix& mat2)
{
	if (mat1.col != mat2.row) return matrix(0, 0);
	matrix mat(mat1.row, mat2.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat2.col; ++j)
			for(int k = 0; k < mat1.col; ++k)
				mat[i][j] += mat1[i][k] * mat2[k][j];

	return mat;
}

matrix operator+(const matrix& mat1, const int scalar)
{
	matrix mat(mat1.row, mat1.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat[i][j] = mat1[i][j] + scalar;

	return mat;
}
matrix operator+(const int scalar, const matrix & mat1)
{
	return mat1 + scalar;
}
matrix operator-(const matrix& mat1, const int scalar)
{
	return mat1 + (-scalar);
}
matrix operator-(const int scalar, const matrix & mat1)
{
	return mat1 + (-scalar);
}
matrix operator*(const matrix& mat1, const int scalar)
{
	matrix mat(mat1.row, mat1.col);
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			mat[i][j] = mat1[i][j] * scalar;

	return mat;
}

matrix& operator+=(matrix & mat1, const matrix& mat2)
{
	return mat1 = mat1 + mat2;
}

matrix& operator-=(matrix & mat1, const matrix& mat2)
{
	return mat1 = mat1 - mat2;
}
matrix& operator+=(matrix & mat1, const int scaler)
{
	return mat1 = mat1 + scaler;
}
matrix& operator-=(matrix & mat1, const int scaler)
{
	return mat1 = mat1 - scaler;
}

matrix& operator++ (matrix& mat) {
	return mat += 1;
}

matrix operator++ (matrix& mat, int) {
	matrix tmp(mat);
	++mat;
	return tmp;
}

matrix& operator-- (matrix& mat) {
	return mat -= 1;
}

matrix operator-- (matrix& mat, int) {
	matrix tmp(mat);
	--mat;
	return tmp;
}

istream & operator>>(istream & in, matrix & mat)
{
	int row, col;
	in >> row >> col;
	mat = matrix(row, col);

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			in >> mat[i][j];
	return in;
}

ostream & operator<<(ostream & out, const matrix& mat)
{
	for (int i = 0; i < mat.row; ++i){
		for (int j = 0; j < mat.col; ++j)
			out << mat[i][j] << ' ';
		out << '\n';
	}
	return out;
}

//TODO: make it look nice when printed out using iomanip
bool operator==(const matrix& mat1, const matrix& mat2)
{
	if (mat1.col != mat2.col || mat1.row != mat1.row) return false;
	for (int i = 0; i < mat1.row; ++i)
		for (int j = 0; j < mat1.col; ++j)
			if (mat1[i][j] != mat2[i][j])
				return false;
			
	return true;
}

bool operator!=(const matrix& mat1, const matrix& mat2)
{
	return !(mat1 == mat2);
}

bool is_square(const matrix & mat)
{
	return mat.row == mat.col;
}

bool is_symetric(const matrix & mat)
{
	if (!is_square(mat)) return false;
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.col; j++)
			if (mat[j][i] != mat[i][j]) return false;
	return true;
}

bool is_identity(const matrix & mat)
{
	if (!is_square(mat)) return false;
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.col; j++)
			if (mat[i][j] != (i == j)) return false;
	return true;
}

matrix transpose(const matrix& mat)
{
	matrix tranmat(mat.col, mat.row);
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.col; j++)
			tranmat[j][i] = mat[i][j];
	return tranmat;
}

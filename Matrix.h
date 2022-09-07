/** @file matrix.h
	@brief		Matrix class header file
	@author		Colombe M'boungou
	@date		January 2020
 */
#pragma once
#include <iostream>
using namespace std;
 /** A matrix class
  *  This class implements matrix and its operations
  */
class Matrix
{
public:

	Matrix(int rows, int cols);					/**<	 initialize zero matrix rows * cols */
	Matrix(int rows, int cols, double value);	/**<	 initialize matrix with all elements equal to value */

	~Matrix();									/**<	default destructor */
	void free(void);

	Matrix operator+(Matrix& b);					/**<	Matrix addition  ; example :	M = A + B */
	Matrix operator-(Matrix& b);					/**<	Matrix substraction  ; example :	M = A - B */
	Matrix operator*(Matrix& b);					/**<	Matrix multiply  ; example :	M = A * B */
	bool operator==(Matrix& b);
	bool operator!=(Matrix& b);
	void StrassenMultiply(Matrix &a, Matrix &b, Matrix& c);				/**<	matrix multiply using Strassen's Algorithm  */
	void multiply(Matrix& a, Matrix& b,Matrix& c);
	
	void divide(Matrix &q1, Matrix &q2, Matrix &q3, Matrix &q4);// divide in quadrants
	void concatenate(Matrix& q1, Matrix& q2, Matrix& q3, Matrix& q4);
	Matrix operator*(double scalar);			/**<	Matrix multiply by scalar		M = scalar * B */
	friend ostream& operator<<(ostream& stream, const  Matrix);
	Matrix Identity(int rows, int cols);		/**<	initialize the identity matrix */

	Matrix multiply(double scalar);				/**<	multiply a matrix by a scalar */

	int getRows(void);							/**<	get the number of rows a matrix */
	int getCols(void);							/**<	get the number of columns a matrix */
	double* getArray(void);						/**<	get the array pointer a matrix */
	void display(void);							/**<	display all elements row after row */
	size_t index(int x, int y);					/**<	return the index of an element at row i , column j */
	double* pointer(int x, int y);				/**<	return the pointer to the element at row i , column j */
	double  element(int x, int y);				/**<	return the element at row i , column j */
	void submatrix(Matrix& M ,int i1, int i2 , int j1 , int j2);		/**<	return a submatrix from row i1 to row i2; column j1 to column j2*/
	void set(int i, int j, double x);
	void testMatrix(int n, int m);
private:

	/**	number of rows*/
	int Rows;
	/**	number of columns*/
	int Cols;
	/** matrix is stored as 1D double array pointer */
	double* Array;
};

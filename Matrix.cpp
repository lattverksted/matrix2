/** @file matrix.cpp
	@brief		Matrix class file
	@author		Colombe M'boungou
	@date		January 2020
 */

#include "Matrix.h"

#include <stdio.h>
#include <iostream>

using namespace std;

/**
* @brief	get the index an element in a matrix
*
* @param[in]	i	int	The row index
* @param[in]	j	int The column index
* @return	size_t	The index of the element at row i ; column j
*/
size_t Matrix::index(int i, int j)
{
	return j + this->Cols * i;
}

/*0 1 2 3
4 5 6 7
8 9 10 11*/

/**
* @brief	initialize a uniform zero matrix
*
* @param[in]		rows int	The row index
* @param[in]		cols int	The column index
* @return	Matrix		The initialized matrix
*/
Matrix::Matrix(int rows, int cols)
{
	this->Array =(double*)calloc(rows * cols, sizeof(double));
	// new double[rows * cols];//

	this->Rows = rows;
	this->Cols = cols;
	double* p_element = this->Array;

	for (int i = 0; i < rows * cols; i++)
	{
		*p_element++ = 0;
	}
}
/**
* @brief	initialize a uniform matrix
*
* @param[in]	rows	The row index
* @param[in]	cols	The column index
* @param[in]	value	The value of all the elements
* @return	Matrix		The initialized matrix
*/
Matrix::Matrix(int rows, int cols, double value)
{
	
	this->Array = new double[rows * cols];// (double*)malloc(rows * cols * sizeof(double));
	this->Rows = rows;
	this->Cols = cols;

	double* p_element = this->Array;
	for (int i = 0; i < rows * cols; i++)
	{
		*p_element++ = value;
	}
}

/**
* @brief	default matrix destructor
*/
Matrix::~Matrix()
{

}

void Matrix::free(void)
{
	//free(this->Array);
	delete[] Array;
	this->Array = 0;
}

/**
*	@brief	initialize an identity matrix
*
*	@param[in]	rows	The number of rows
*	@param[in]	cols	The number of columns
*	@return	Matrix		The initialized matrix
*/
Matrix Matrix::Identity(int rows, int cols)
{
	Matrix identity = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
			{
				double* p_element = identity.pointer(i, j);
				*p_element = 1;
			}
		}


	}

	return identity;
}


/**
* @brief	get the number of rows in a matrix
*
* @return	The  number of rows
*/
int Matrix::getRows(void)
{
	return this->Rows;
}



/**
* @brief	get the number of columns in a matrix
*
* @return	The  number of columns
*/
int Matrix::getCols(void)
{
	return this->Cols;
}



/**
* @brief	get the array pointer of a matrix
*
* @return	double*		The array pointer
*/
double* Matrix::getArray(void)
{
	return this->Array;
}


/**
* @brief	get the pointer to the element at row i , column j of a matrix
*
* @param[in]	i	The row index
* @param[in]	j	The column index
* @return	double*	The pointer to the element at row i , column j
*/
double* Matrix::pointer(int i, int j)
{
	double* address = this->Array + this->index(i, j);
	return address;
}

/**
* @brief	get the pointer to the element at row i , column j of a matrix
*
* @param[in]	i	The row index
* @param[in]	j	The column index
* @return	double*	The pointer to the element at row i , column j
*/
double Matrix::element(int i, int j)
{
	double* p = this->pointer(i,j);
	return *p;
}




/**
 * @brief	add two matrices together
 *
 * @param[in]	b	The other matrix to add with
 * @return		Matrix		The result of the addition
 */

Matrix  Matrix::operator+(Matrix& b)
{
	int rows = this->getRows();
	int cols = this->getCols();
	Matrix m = Matrix(rows, cols);

	if ((rows != b.getRows()) || (cols != b.getCols()))
	{
		return  Matrix(0, 0);
	}

	double* p_m = m.Array;
	double* p_a = this->Array;
	double* p_b = b.Array;

	//only  1 loop  also works
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*p_m++ = *p_a++ + *p_b++;
		}
	}
	return m;
}

/**
 * @brief	substract two matrices together
 *
 * @param[in]	b	The other matrix to add with
 * @return		Matrix		The result of the addition
 */

Matrix  Matrix::operator-(Matrix& b)
{
	int rows = this->getRows();
	int cols = this->getCols();
	Matrix m = Matrix(rows, cols);

	if ((rows != b.getRows()) || (cols != b.getCols()))
	{
		return  Matrix(0, 0);
	}

	double* p_m = m.Array;
	double* p_a = this->Array;
	double* p_b = b.Array;

	//only  1 loop  also works
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*p_m++ = *p_a++ - *p_b++;
		}
	}
	return m;
}

/**
 * @brief	multiply two matrices together
 *
 * @param[in,out]	b	The other matrix to multiply with
 * @return			Matrix		The result of the multiplication
 */

Matrix  Matrix::operator*(Matrix& b)
{
	int rows = this->getRows();
	int cols = this->getCols();

	if (cols != b.getRows())
	{
		return  Matrix(0, 0);
	}

	Matrix m = Matrix(rows, b.getCols());

	int cols_rows = cols;
	double* p_m = m.Array;


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			double* p_a = this->Array;
			double* p_b = b.Array;
			double sum = 0;
			for (int k = 0; k < cols_rows; k++)
			{

				double a_ik = *this->pointer(i, k);
				double b_kj = *b.pointer(k, j);
				sum += a_ik * b_kj;

			}
			*p_m++ = sum;

		}
	}
	return m;
}

bool Matrix::operator==(Matrix& b)
{

	if (this->getRows() != b.getRows() || this->getCols() != b.getCols())
	{
		cerr << " Warning! Matrices have different sizes." << endl;
		return false;
	}
	else 
	{
		for (int i = 0; i < this->getRows(); i++)
		{
			for (int j = 0; j < this->getCols(); j++)
			{
				if (this->element(i, j) != b.element(i, j))
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool Matrix::operator!=(Matrix& b)
{

	return !(this->operator==(b));
}

/**
 * @brief	operator multiply a matrix with a scalar
 *
 * @param[in]	scalar	The scalar to multiply the matrix with
 * @return		Matrix			The result
 */
Matrix  Matrix::operator*(double  scalar)
{

	return this->multiply(scalar);

}
/**
 * @brief	multiply a matrix with a scalar
 *
 * @param[in]	scalar	The scalar to multiply the matrix with
 * @return		Matrix			The result
 */
Matrix Matrix::multiply(double scalar)
{
	int rows = this->Rows;
	int  cols = this->Cols;
	Matrix M = Matrix(rows, cols);

	double* a_element = this->Array;
	double* m_element = M.Array;
	for (int i = 0; i < rows * cols; i++)
	{
		*m_element++ = scalar * *a_element++;
	}
	return M;
}

void Matrix::multiply( Matrix& a, Matrix& b, Matrix& c)
{
	c = a * b;
}

ostream& operator <<(ostream& out, Matrix m)
{
	m.display();
	out << "matrix" << endl;
	return out;
}

/**
 * @brief	display the elements of the matrix row after row
 */
void Matrix::display(void)
{
	int rows = this->Rows;
	int cols = this->Cols;

	cout << rows << " rows x " << cols << " columns" << endl;
	double* p_element = this->Array;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			cout << *p_element++ << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix::set(int i, int j, double x)
{
	double *p = this->pointer(i,j);
	*p = x;
}
void Matrix::submatrix(Matrix &dst, int i1, int i2, int j1, int j2)
{
	int rows = i2 - i1 + 1;
	int cols = j2 - j1 + 1;
	
	// number of bytes to copy each row
	int num_bytes = sizeof(double) * cols;

	// copy each sub-rows from the source matrix
	for (int i = 0; i < rows; i++)
	{
		
		// destination pointer
		double* p_dst_row_i = dst.pointer(i, 0);

		// source pointer
		double* p_src_row_i = this->pointer(i + i1,0);

		p_src_row_i += j1;
		memcpy((void*)p_dst_row_i, (const void*)p_src_row_i, (size_t) num_bytes); 

	}
	
}

void Matrix::testMatrix(int n, int m)
{
	// Matrix M = Matrix(n, m);

	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->set(i, j, k);
			k += 1;
		}
	}
}
// divide in quadrants
void Matrix::divide(Matrix &a, Matrix &b, Matrix &c, Matrix &d)
{
	int n = this->getRows();
	int m = this->getCols();

	int n_2 = n / 2;
	int m_2 = m / 2;

	this->submatrix(a, 0, n_2-1, 0, m_2-1);
	this->submatrix(b, 0, n_2-1, m_2, m-1);
	this->submatrix(c,n_2, n-1, 0, m_2-1);
	this->submatrix(d, n_2, n-1, m_2, m-1);

}
void Matrix::concatenate(Matrix& q1, Matrix& q2, Matrix& q3, Matrix& q4)
{
	int n = this->getRows();
	int m = this->getCols();

	int n_2 = n / 2;
	int m_2 = m / 2;
	// number of bytes to copy each row
	int num_bytes = sizeof(double) * n_2;

	// copy rows from q1 to destination matrix 
	for (int i = 0; i < n_2; i++)
	{ 
		// destination pointer
		double* p_dst_row_i = this->pointer(i, 0);

		// source pointer
		double* p_src_row_i = q1.pointer(i, 0);

		// copy row to destination
		memcpy((void*)p_dst_row_i, (const void*)p_src_row_i, (size_t)num_bytes);
	}
	// copy rows from q2 to destination matrix 
	for (int i = 0; i < n_2; i++)
	{
		// destination pointer
		double* p_dst_row_i = this->pointer(i , m_2);

		// source pointer
		double* p_src_row_i = q2.pointer(i, 0);

		// copy row to destination
		memcpy((void*)p_dst_row_i, (const void*)p_src_row_i, (size_t)num_bytes);
	}

	// copy rows from q3 to destination matrix 
	for (int i = 0; i < n_2; i++)
	{
		// destination pointer
		double* p_dst_row_i = this->pointer(i + n_2, 0);

		// source pointer
		double* p_src_row_i = q3.pointer(i, 0);

		// copy row to destination
		memcpy((void*)p_dst_row_i, (const void*)p_src_row_i, (size_t)num_bytes);
	}

	// copy rows from q3 to destination matrix 
	for (int i = 0; i < n_2; i++)
	{
		// destination pointer
		double* p_dst_row_i = this->pointer(i + n_2, m_2);

		// source pointer
		double* p_src_row_i = q4.pointer(i, 0);

		// copy row to destination
		memcpy((void*)p_dst_row_i, (const void*)p_src_row_i, (size_t)num_bytes);
	}

}

// square matrices only
void Matrix::StrassenMultiply(Matrix &A , Matrix& B, Matrix &C)
{
	int n = this->getRows();
	int m = this->getCols();

	int n_2 = n / 2;
	int m_2 = m / 2;
	// check size 
	if (this->getCols() != B.getRows())
	{
		cerr << "incompatible sizes" << endl;
		return;
	}
	// deal with base case

	if (this->getCols() <= 256)
	{
		C.multiply(A, B, C);
	}
	else
	{
		// divide into 4 quadrants
		Matrix a = Matrix(n_2, m_2);
		Matrix b = Matrix(n_2, m_2);
		Matrix c = Matrix(n_2, m_2); 
		Matrix d = Matrix(n_2, m_2);

		A.divide(a, b, c, d);

		// divide into 4 quadrants
		Matrix e = Matrix(n_2, m_2);
		Matrix f = Matrix(n_2, m_2);
		Matrix g = Matrix(n_2, m_2);
		Matrix h = Matrix(n_2, m_2);

		B.divide(e, f, g, h);

		// conquer
		Matrix p1 = Matrix(n_2, m_2);

		Matrix r1 = f - h;

		p1.StrassenMultiply(a, r1, p1);
		r1.free();
		
		Matrix r2 = a + b;

		Matrix p2 = Matrix(n_2, m_2);

		p2.StrassenMultiply(h, r2, p2);
		r2.free();

		Matrix r3 = c + d;
		Matrix p3 = Matrix(n_2, m_2);

		p3.StrassenMultiply(e, r3, p3);
		r3.free();
		Matrix r4 = g - e;
		Matrix p4 = Matrix(n_2, m_2);

		p4.StrassenMultiply(d, r4, p4);

		r4.free();
		Matrix r5 = a + d;
		Matrix r6 = e + h;
		Matrix p5 = Matrix(n_2, m_2);

		p5.StrassenMultiply(r5, r6, p5);
		// delete unnecessary matrices to save space
		r5.free();
		r6.free();


		Matrix r7 = b - d;
		b.free();
		d.free();
		Matrix r8 = g + h;
		g.free();
		h.free();
		Matrix p6 = Matrix(n_2, m_2);

		p6.StrassenMultiply(r7, r8, p6);
		// delete unnecessary matrices to save space
		r7.free();
		r8.free();
		
		Matrix r9 = a - c;
		a.free();
		c.free();
		Matrix r10 = e + f;
		e.free();
		f.free();

		Matrix p7 = Matrix(n_2, m_2);
		p7.StrassenMultiply(r9, r10, p7);
		// delete unnecessary matrices to save space
		r9.free();
		r10.free();

		// recombine

		Matrix q1 = p5 + p4 - p2 + p6;
		p6.free();
		Matrix q2 = p1 + p2;
		p2.free();
		Matrix q3 = p3 + p4;
		p4.free();
		Matrix q4 = p1 + p5 - p3 - p7;

		// delete unnecessary matrices to save space
		p1.free();
		p3.free();
		p5.free();
		p7.free();
		
		C.concatenate(q1, q2, q3, q4);
		q1.free();
		q2.free();
		q3.free();
		q4.free();
	}





}
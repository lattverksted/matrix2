/** @file test.cpp
	@brief		code to test matrix class
	@author		Colombe M'boungou
	@date		January 2020
 */

#include "Matrix.h"
#include "Name.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


void recur(Name n)
{
	static int calls = 0;

	Name temp1 = n;
	Name temp2 = n;

	temp1.setDataElement(0, temp1.getDataElement(0) + 1);
	temp2.setDataElement(0, temp1.getDataElement(0) - 1);
	calls++;

	if(calls>=5000) 
	{
		return;
	}
	else
	{
		recur(temp1);
		recur(temp2);
	}
}



int main()
{
	cout << "start" << endl;

	int n = 512;
	Matrix m = Matrix(n, n);
	m.testMatrix(n, n);

	
	
	//cout << "test matrix " << m << endl;

	//cout << "m22" << m.element(2, 2) << endl;

	/*Matrix sub = Matrix(3, 3);
	m.submatrix(sub, 1, 3, 1, 3);
	//cout << "submatrix " << sub << endl;

	Matrix q1 = Matrix(n/2, n/2);
	Matrix q2 = Matrix(n/2, n/2);
	Matrix q3 = Matrix(n/2, n/2);
	Matrix q4 = Matrix(n/2, n/2);

	m.divide(q1, q2, q3,  q4);*/

	/*cout << "q1 " << q1 << endl;
	cout << "q2 " << q2 << endl;
	cout << "q3 " << q3 << endl;
	cout << "q4 " << q4 << endl;*/

	/*Matrix m_ = Matrix(4, 4);
	m_.concatenate(q1, q2, q3, q4);
	cout << "correctness : " << (m_ == m) << endl;

	q1.free();
	q2.free();
	q3.free();
	q4.free();

	cout << "recombined " << m_ << endl;
	
	*/
	
	
	Matrix id = id.Identity(n, n);
	//cout << " identity " << id << endl;

	Matrix prod = Matrix(n, n);

	auto start = high_resolution_clock::now();
	prod.StrassenMultiply(m, id, prod);
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	cout << "strassen : " << duration.count()<< "ms" << endl;

	
	Matrix check_prod = Matrix(n, n); 


	start = high_resolution_clock::now();
	check_prod = m * id;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	cout << " naive " << duration.count() <<"ms" << endl;

	id.free();
	m.free();

	cout << "check " << (prod==check_prod) << endl;
	prod.free();
	check_prod.free();

	
	/*Name name = Name(1024);
	recur(name);*/

	cout << "end" << endl;

}
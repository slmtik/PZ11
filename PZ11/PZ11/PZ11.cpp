// PZ11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

//default matrix size;
const int defaultMatrixSize = 5;
//default random range for filling matrix
const int range = 5;

class Matrix
{
public:
	int Rows() const { return rows; }
	int Cols() const { return cols; }
private:
	int** matrix;
	int rows;
	int cols;
	int* colsWeight; //array with weights of columns - used for sorting

public:
	//creating matrix with specified sizes
	Matrix(unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
	{
		AllocateMatrix();
		FillMaxtrix();
		CalculateWeight();
	}

	//in case no sizes were specified use default matrix size
	Matrix() : Matrix(defaultMatrixSize, defaultMatrixSize) {}

	//initialize class with custom dynamic matrix 
	Matrix(int** matrix, unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
	{
		AllocateMatrix();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->matrix[i][j] = matrix[i][j];
		CalculateWeight();
	}

	//initialize class with custom matrix 
	Matrix(int matrix[], unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
	{
		AllocateMatrix();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->matrix[i][j] = matrix[i * cols + j];
		CalculateWeight();
	}

	~Matrix()
	{
		for (int i = 0; i < Rows(); ++i)
			delete[] matrix[i];
		delete[] matrix;
		delete[] colsWeight;
	}

private:
	//allocate matrix
	void AllocateMatrix()
	{
		matrix = new int*[Rows()];
		for (int i = 0; i < Rows(); ++i)
			matrix[i] = new int[cols] {};
	}

	//filling matrix with random numbers in certain range
	void FillMaxtrix()
	{
		for (int i = 0; i < Rows(); i++)
			for (int j = 0; j < cols; j++)
				matrix[i][j] = rand() % (range * 2 + 1) - range;
	}

	//calculating columns weight by sum all negative and odd numbers
	void CalculateWeight()
	{
		colsWeight = new int[cols] {};

		for (int i = 0; i < Rows(); i++)
			for (int j = 0; j < cols; j++)
				if (matrix[i][j] < 0 && matrix[i][j] % 2 != 0)
					colsWeight[j] += abs(matrix[i][j]);
	}

	//swap two columns in specified positions and swapping their columnWeight
	void SwapColumns(int columnIndexA, int columnIndexB)
	{
		for (int i = 0; i < Rows(); i++)
		{
			int temp = matrix[i][columnIndexA];
			matrix[i][columnIndexA] = matrix[i][columnIndexB];
			matrix[i][columnIndexB] = temp;
		}

		int tempWeight = colsWeight[columnIndexA];
		colsWeight[columnIndexA] = colsWeight[columnIndexB];
		colsWeight[columnIndexB] = tempWeight;
	}
public:
	//display current matrix
	void DisplayMatrix()
	{
		for (int i = 0; i < Rows(); i++)
		{
			for (int j = 0; j < cols; j++)
				cout << (matrix[i][j] >= 0 ? " " : "") << matrix[i][j] << " ";
			cout << endl;
		}
	}

	//sort columns by their column weight using insert sort
	void SortMatrix()
	{
		for (int i = 1; i < cols; i++)
			for (int j = i; j > 0 && colsWeight[j - 1] > colsWeight[j]; j--)
				SwapColumns(j - 1, j);
	}

	//for debug use to check columns weight
	void DisplayColumnWeight()
	{
		for (int i = 0; i < cols; i++)
			cout << colsWeight[i] << " ";
		cout << endl;

	}

	//multiplication operator by vector, if vector size is not the same as matrix columns amount return nullptr
	int* MultiplyByVector(int vector[], unsigned int size)
	{
		if (size != cols)
			return nullptr;

		int* result = new int[rows] {};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				result[i] += vector[j] * matrix[i][j];
		return result;
	}

	//multiplication operator by vector, if vector size is not the same as matrix columns amount return nullptr.
	//this time using other way to access elements
	int* MultiplyByVector2(int vector[], unsigned int size)
	{
		if (size != cols)
			return nullptr;

		int* result = new int[rows] {};
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				*(result + i) += *(vector +j) * *(*(matrix + i) + j);
		return result;
	}
};

void Task1()
{
	cout << "1. Sort matrix by condition\n";
	Matrix a;
	a.DisplayMatrix();
	cout << endl;
	//a.DisplayColumnWeight();
	cout << "some magic with sorting\n";
	a.SortMatrix();
	a.DisplayMatrix();
	cout << endl;
	//a.DisplayColumnWeight();
}

void Task2()
{
	cout << "2. multiplying matrix by vector\n";
	const int matrixSize = 3;
	int array[matrixSize][matrixSize] = { { 2,4,0 },{ -2,1,3 },{ -1, 0, 1 } };
	Matrix b(*array, matrixSize, matrixSize);
	b.DisplayMatrix();

	cout << "our vector is (1, 2, -1)\n";
	int vector[3] = { 1, 2, -1 };

	int *result = b.MultiplyByVector(vector, 3);
	cout << "result is\n";
	for (int i = 0; i < matrixSize; i++)
		cout << result[i] << " ";
	cout << endl;

	int *result2 = b.MultiplyByVector2(vector, 3);

	for (int i = 0; i < matrixSize; i++)
		cout << result2[i] << " ";
	cout << endl;

	cout << endl;
}

void Task3()
{

}

class B1
{
public:
	virtual void vf()
	{
		cout << "B1::vf()\n";
	}

	void f()
	{
		cout << "B1::f()\n";
	}

	virtual void pvf() = 0;
};

class D1 : public B1
{
public:
	void vf()
	{
		cout << "D1::vf\n";
	}

	void f()
	{
		cout << "D1::f\n";
	}
};

class D2 : public D1
{
public:
	void pvf()
	{
		cout << "D2::pvf\n";
	}
};

class B2
{
public:
	virtual void pvf() = 0;
};

class D21 : public B2
{
	string data = "testData";
	
public:
	void pvf()
	{
		cout << data << endl;
	}
};

class D22 : public B2
{
	int data = 123;

public:
	void pvf()
	{
		cout << data << endl;
	}
};

void f(B2& input)
{
	input.pvf();
}

int main()
{
	srand(time(NULL));
	//1. Sort matrix by condition
	Task1();
	
	//2. multiplying matrix by vector
	//we will be using already defined vector and matrix in this case
	Task2();

	//3. task related to virtual functions
	cout << "3. task related to virtual functions\n";
	/*
	до обьявления чисто виртульной ф-ции результаты были следующие:
	B1 a;
	a.f();		- вызов ф-ции из B1
	a.vf();		- вызов ф-ции из B1

	D1 b;
	b.f();		- до определения f() в D1 вызов ф-ции из B1, после вызов ф-ции из D1
	b.vf();		- вызов ф-ции из D1

	B1& c = b;
	c.f();		- вызов ф-ции из B1, эта ф-ция не виртуальная, используется определение из класса из которого она вызвана
	c.vf();		- вызов ф-ции из B1, эта ф-ция виртуальная, используется определение из класса, который расположен по этому адресу памяти

	после обьявления чисто виртуальной ф-ции, мы не можем создать обьект класса B1, так как этот класс становится абстрактным.
	и так как эта ф-ция не была переопределена в D1, этот класс тоже становится абстрактным и мы тоже не можем создать его объект.
	*/

	D2 d;
	d.f();
	d.vf();
	d.pvf();

	D21 d21;
	D22 d22;
	f(d21);
	f(d22);
    return 0;
}


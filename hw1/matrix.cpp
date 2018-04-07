#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

Matrix::Matrix(const int& r, const int& c)//: row(r), col(c) //constructor
{
	//printf("%d\n",r);
	row = r; col = c;
	//printf("%d\n",row);
	array = new double*[r];
	for(int i = 0; i < r; i++)
    	array[i] = new double[c];
	
}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
	row = rhs.row;
	col = rhs.col;
	array = new double*[row];
	for(int i = 0; i < row; i++)
    	array[i] = new double[col];
    	
	for (int i = 0; i < row; i++){
		for (int j =0; j < col; j++)
			array[i][j] = rhs.array[i][j];
	}
}

Matrix::~Matrix() //destructor
{
	for (int i =0; i < row; i++)
		delete [] array[i];
	delete [] array;
}

double* & Matrix::operator [](const int& idx) const	// Enable the use of A[i][j] instead of A.array[i][j]
{
	return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment operator
{
	if (this == &rhs)
		return *this;
		 //if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
	if (this->row != rhs.row || this->col != rhs.col){
		for (int i = 0; i < row; i++)
			delete [] array[i];
		delete [] array;
		
		row = rhs.row;
		col = rhs.col;
		array = new double* [row];
		for (int i = 0; i < row; i++)
			array[i] = new double [col];
	}
	
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			array[i][j] = rhs.array[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator -() const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)
			temp.array[i][j] = -array[i][j];
	}
	return temp;
}

Matrix Matrix::operator +() const
{
	return *this;
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)
			temp[i][j] = array[i][j] - rhs.array[i][j];
	}
	return temp;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
	Matrix temp(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)
			temp[i][j] = array[i][j] + rhs.array[i][j];
	}
	return temp;		
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
	Matrix temp(row, rhs.col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < rhs.col; j++){
			temp.array[i][j] = 0;
			for (int k = 0; k < rhs.row; k++)
				temp.array[i][j] += array[i][k] * (rhs.array[k][j]);
		}
	}
	return temp;
}

Matrix Matrix::operator /(const Matrix& rhs) const
{
	Matrix temp(row, rhs.col);
	temp = *this * rhs.inverse();
	return temp;
}

Matrix Matrix::inverse() const
{
	Matrix temp(row, col);
	double d = 0;
	for(int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			if (i == j)
				temp[i][j] = 1;
			else
				temp[i][j] = 0;
		}
	}
	auto abs = [](double a){
		return a > 0 ? a : -a;
	}; //lambda expression
	
	//upper triangle
	for (int i = 0; i < row-1; i++){
		if (abs(array[i][i]) < 1e-6) {
			for (int t = i+1; t < row; t++){
				if (abs(array[t][i]) > 1e-6){
					for (int s = 0; s < col; s++){
						std::swap(array[i][s], array[t][s]);
						std::swap(temp.array[i][s], temp.array[t][s]);
					}
					break;
				}
			} 
		}
		for (int j = i+1; j < row; j++){
			d = - array[j][i] / array[i][i];
			for (int k = 0; k < col; k++){
				array[j][k] += d * array[i][k];
				temp[j][k] += d * temp[i][k]; 
			}
		}
	}
	
	//diagonal matrix
	for (int i = row-1; i > 0; i--){
		for (int j = i-1; j >= 0 ; j--){
			d = - array[j][i] / array[i][i];
			for (int k = 0; k < col; k++){
				array[j][k] += d * array[i][k];
				temp[j][k] += d * temp[i][k]; 
			}
		}
	}

	//divide to 1
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++)
			temp.array[i][j] /= array[i][i];
	}

	return temp;
}


void Matrix::read(const char* fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if(fp == NULL){
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char* fn)
{
	FILE *fp = fopen(fn, "w");
	if(fp == NULL){
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			fprintf(fp, "%lf%c", array[i][j], " \n"[j==col-1]);
	fclose(fp);
}

void Matrix::print() const
{
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			printf("%lf%c", array[i][j], " \n"[j==col-1]);
}


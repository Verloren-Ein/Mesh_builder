#pragma once
#include "common.h"
//using primitive multiply algorithm

class Matrix
{
private:
	unsigned rows_, cols_;
	vector<double> elements_;

public:
	Matrix()
		:rows_()
		,cols_()
	{
		elements_.clear();
	}
	Matrix(unsigned n)
		:rows_(n)
		, cols_(n)
	{
		elements_.clear();
		elements_.resize(n*n);
	}
	Matrix(unsigned rows, unsigned cols)
		:rows_(rows)
		,cols_(cols)
	{
		elements_.clear();
		elements_.resize(rows_*cols_);
	}
	~Matrix()
	{
		elements_.clear();
		elements_.~vector();
	}
	void clear();
	void reset();
	void display();
	void display(streamsize precision);
	void print(ofstream& ostr);
	void print(ofstream& ostr, streamsize precision);
	unsigned rows();
	unsigned cols();
	/*returns transposed matrix*/
	Matrix transpose();
	/*returns inversed matrix*/
	Matrix inverse();
	/*returns matrix determinant*/
	double determinant();
	/*strike out given row and col and returns new matrix*/
	Matrix strike_out(unsigned row, unsigned col);

	/*sets current matrix with elements*/
	void set_matrix(double** elements);
	/*sets current matrix with element for all matrix elements*/
	void set_matrix(double element);
	/*sets current matrix to identity matrix*/
	void set_identity_matrix();
	/*sets current matrix to diagonal matrix with diagonal_element for all diagonal elements*/
	void set_diagonal_matrix(double diagonal_element);
	/*sets current matrix to diagonal matrix with diagonal_element for all diagonal elements*/
	/*diagonal_number values: 0 - main diagonal, >0 upper, <0 lower*/
	void set_subdiagonal_matrix(int diagonal_number, double diagonal_element);
	/*sets current matrix to diagonal matrix with diagonal_elements for diagonal*/
	void set_diagonal_matrix(vector<double> diagonal_elements);
	/*sets current matrix to diagonal matrix with diagonal_elements for diagonal*/
	/*diagonal_number values: 0 - main diagonal, >0 upper, <0 lower*/
	void set_subdiagonal_matrix(int diagonal_number, vector<double> diagonal_elements);
	/*returns vector contains diagonal_number elements*/
	/*diagonal_number values: 0 - main diagonal, >0 upper, <0 lower*/
	vector<double> get_diagonal(int diagonal_number);
	/*returns main diagonal elements*/
	vector<double> get_main_diagonal();
	/*returns vector contains row_number elements*/
	vector<double> get_row(unsigned row_number);
	/*returns vector contains col_number elements*/
	vector<double> get_col(unsigned col_number);


	/*operators overloading*/
	/*subscript operator*/
	double& operator() (unsigned row, unsigned col); 
	double operator() (unsigned row, unsigned col) const;

	/*unary operators*/
	friend const Matrix& operator+(const Matrix& i);
	friend const Matrix operator-(const Matrix& i);

	friend Matrix& operator+=(Matrix& left, const Matrix& right);
	friend Matrix& operator-=(Matrix& left, const Matrix& right);
	friend Matrix& operator*=(Matrix& left, const Matrix& right);

	friend Matrix& operator+=(Matrix& left, const double& right);
	friend Matrix& operator-=(Matrix& left, const double& right);
	friend Matrix& operator*=(Matrix& left, const double& right);

	/*binary operators*/
	friend bool operator ==(Matrix &A, Matrix &B);
	friend bool operator !=(Matrix &A, Matrix &B);

	friend const Matrix operator+(const Matrix& left, const Matrix& right);
	friend const Matrix operator-(const Matrix& left, const Matrix& right);
	friend const Matrix operator*(const Matrix& left, const Matrix& right);

	friend const Matrix operator+(const Matrix& left, const double& right);
	friend const Matrix operator-(const Matrix& left, const double& right);
	friend const Matrix operator*(const Matrix& left, const double& right);

	friend const Matrix operator+(const double& left, const Matrix&  right);
	friend const Matrix operator-(const double& left, const Matrix&  right);
	friend const Matrix operator*(const double& left, const Matrix&  right);

protected:
	/*arithmetic operations*/
	virtual void plus(Matrix arg);		// elements[i] + arg[i]
	virtual void minus(Matrix arg);		// elements[i] - arg[i]
	virtual void multiply(Matrix arg);	// elements[i] * arg[i]

	void plus(double arg);		// elements[i] + arg
	void minus(double arg);		// elements[i] - arg
	void multiply(double arg);	// elements[i] * arg

private:
	/*sets current matrix with vector elements for all matrix elements : internal use only*/
	void set_matrix(vector<double> elements);
	/*recursive determinant calculation : internal use only*/
	double recursive_determinant(Matrix matr);
	/*strike out given row and col and returns new matrix : internal use only*/
	Matrix strike_out(Matrix matrix, unsigned row, unsigned col);
};


#include "Matrix.h"

void Matrix::clear()
{
	rows_ = int();
	cols_ = int();
	elements_.clear();
}

void Matrix::reset()
{
	set_matrix(0.);
}

void Matrix::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);

	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			cout << this->operator()(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);

	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			cout << this->operator()(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout.precision(DISPLAY_PRECISION);
}

void Matrix::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);

	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			ostr << this->operator()(i, j) << " ";
		}
		ostr << endl;
	}
	ostr << endl;
}

void Matrix::print(ofstream & ostr, streamsize precision)
{
	ostr << fixed;
	ostr.precision(precision);

	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			ostr << this->operator()(i, j) << " ";
		}
		ostr << endl;
	}
	ostr << endl;
	ostr.precision(DISPLAY_PRECISION);
}

unsigned Matrix::rows()
{
	return rows_;
}

unsigned Matrix::cols()
{
	return cols_;
}

Matrix Matrix::transpose()
{
	Matrix transposed_matrix = Matrix(this->cols(), this->rows());
	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			transposed_matrix(j, i) = this->operator()(i, j);
		}
	}

	return transposed_matrix;
}

Matrix Matrix::inverse()
{
	Matrix inverse_matrix;
	Matrix new_matrix;

	/*calculate determinant*/
	double det = determinant();

	try
	{
		/*if determinant is zero, matrix can not be inversed*/
		if(abs(det) < almost_zero)
			throw "Error: matrix can not be inversed";
		else
		{
			inverse_matrix = Matrix(rows_, cols_);
			for(unsigned i = 0; i < rows_; i++)
			{
				for(unsigned j = 0; j < cols_; j++)
				{
					new_matrix = strike_out(i, j);
					inverse_matrix(i, j) = pow(-1.0, i + j + 2)*recursive_determinant(new_matrix) / det;
					new_matrix.~Matrix();
				}
			}
			inverse_matrix = inverse_matrix.transpose();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	return inverse_matrix;
}

double Matrix::determinant()
{
	/*copy base matrix*/
	Matrix new_matrix = Matrix(this->rows_, this->cols_);
	new_matrix.set_matrix(this->elements_);
	double determinant = 0;

	try
	{
		if(rows_ != cols_)
			throw "Error: attempt to calculate a determinant of non-square matrix";
		else
		{
			determinant = recursive_determinant(new_matrix);
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	new_matrix.~Matrix();
	return determinant;
}

Matrix Matrix::strike_out(unsigned row, unsigned col)
{
	Matrix new_matrix;
	try
	{
		if(row >= this->rows() || col >= this->cols())
			throw "Error: matrix subscript out of range";
		else
		{
			new_matrix = Matrix(this->rows() - 1, this->cols() - 1);
			for(unsigned i = 0, new_i = 0; i < this->rows(); i++)
			{
				if(i != row)
				{
					for(unsigned j = 0, new_j = 0; j < this->cols(); j++)
					{
						if(j != col)
						{
							new_matrix(new_i, new_j) = this->operator()(i, j);
							new_j++;
						}
					}
					new_i++;
				}
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return new_matrix;
}

void Matrix::set_matrix(double** elements)
{
	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			this->operator()(i, j) = elements[i][j];
		}
	}
}

void Matrix::set_matrix(double element)
{
	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			this->operator()(i, j) = element;
		}
	}
}

void Matrix::set_identity_matrix()
{
	set_diagonal_matrix(1.);
}

void Matrix::set_diagonal_matrix(double diagonal_element)
{
	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			if(i == j)
				this->operator()(i, j) = diagonal_element;
			else 
				this->operator()(i, j) = 0.;
		}
	}
}

void Matrix::set_subdiagonal_matrix(int diagonal_number, double diagonal_element)
{
	try 
	{
		if(diagonal_number == 0)
			set_diagonal_matrix(diagonal_element);
		if(diagonal_number > 0)
		{
			if(diagonal_number > int(cols_ - 1))
				throw "Error: diagonal number in matrix out of range";
			else
			{
				reset();
				for(unsigned i = 0, j = diagonal_number; i < rows_ && j < cols_; i++, j++)
				{
					this->operator()(i, j) = diagonal_element;
				}
			}
		}
		if(diagonal_number < 0)
		{
			if(abs(diagonal_number) > int(rows_ - 1))
				throw "Error: diagonal number in matrix out of range";
			else
			{
				reset();
				for(unsigned i = 0, j = abs(diagonal_number); i < cols_ && j < rows_; i++, j++)
				{
					this->operator()(j, i) = diagonal_element;
				}
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Matrix::set_diagonal_matrix(vector<double> diagonal_elements)
{
	for(unsigned i = 0; i < rows_; i++)
	{
		for(unsigned j = 0; j < cols_; j++)
		{
			if(i == j)
				this->operator()(i, j) = diagonal_elements[i];
			else
				this->operator()(i, j) = 0.;
		}
	}
}

void Matrix::set_subdiagonal_matrix(int diagonal_number, vector<double> diagonal_elements)
{
	//no check vector size
	try
	{
		if(diagonal_number == 0)
			set_diagonal_matrix(diagonal_elements);
		if(diagonal_number > 0)
		{
			if(diagonal_number > int(cols_ - 1))
				throw "Error: diagonal number in matrix out of range";
			else
			{
				reset();
				for(unsigned i = 0, j = diagonal_number; i < rows_ && j < cols_; i++, j++)
				{
					this->operator()(i, j) = diagonal_elements[i];
				}
			}
		}
		if(diagonal_number < 0)
		{
			if(abs(diagonal_number) > int(rows_ - 1))
				throw "Error: diagonal number in matrix out of range";
			else
			{
				reset();
				for(unsigned i = 0, j = abs(diagonal_number); i < cols_ && j < rows_; i++, j++)
				{
					this->operator()(j, i) = diagonal_elements[i];
				}
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

vector<double> Matrix::get_diagonal(int diagonal_number)
{
	vector<double> diagonal;
	try
	{
		if(diagonal_number == 0)
			diagonal = get_main_diagonal();
		if(diagonal_number > 0)
		{
			if(diagonal_number > int(cols_ - 1))
				throw "Error: diagonal number in matrix out of range";
			else
			{
				for(unsigned i = 0, j = diagonal_number; i < rows_ && j < cols_; i++, j++)
				{
					diagonal.push_back(this->operator()(i, j));
				}
			}
		}
		if(diagonal_number < 0)
		{
			if(abs(diagonal_number) > int(rows_ - 1))
				throw "Error: diagonal number in matrix out of range";
			else
			{
				for(unsigned i = 0, j = abs(diagonal_number); i < cols_ && j < rows_; i++, j++)
				{
					diagonal.push_back(this->operator()(j, i));
				}
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return diagonal;
}

vector<double> Matrix::get_main_diagonal()
{
	vector<double> diagonal;
	for(unsigned i = 0; i < rows_; i++)
	{
		diagonal.push_back(this->operator()(i, i));
	}
	return diagonal;
}

vector<double> Matrix::get_row(unsigned row_number)
{
	vector<double> row;
	try
	{
		if(row_number >= rows_)
			throw "Error: matrix subscript out of range";

		else
		{
			for(unsigned i = 0; i < cols_; i++)
			{
				row.push_back(elements_[cols_*row_number + i]);
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return row;
}

vector<double> Matrix::get_col(unsigned col_number)
{
	vector<double> col;
	try
	{
		if(col_number >= cols_)
			throw "Error: matrix subscript out of range";

		else
		{
			for(unsigned i = 0; i < rows_; i++)
			{
				col.push_back(elements_[col_number + i*cols_]);
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return col;
}

double & Matrix::operator()(unsigned row, unsigned col)
{
	try
	{
		if(row >= rows_ || col >= cols_)
			throw "Error: matrix subscript out of range";

		else
			return elements_[cols_*row + col];
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

double Matrix::operator()(unsigned row, unsigned col) const
{
	try
	{
		if(row >= rows_ || col >= cols_)
			throw "Error: matrix subscript out of range";

		else
			return elements_[cols_*row + col];
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

const Matrix & operator+(const Matrix & i)
{
	return i;
}

const Matrix operator-(const Matrix & i)
{
	Matrix matr = Matrix(i.rows_, i.cols_);
	for(int k = 0; k < i.elements_.size(); k++)
	{
		matr.elements_[k] = -i.elements_[k];
	}
	return matr;
}

Matrix & operator+=(Matrix & left, const Matrix & right)
{
	left.plus(right);
	return left;
}

Matrix & operator-=(Matrix & left, const Matrix & right)
{
	left.minus(right);
	return left;
}

Matrix & operator*=(Matrix & left, const Matrix & right)
{
	left.multiply(right);
	return left;
}

Matrix & operator+=(Matrix & left, const double & right)
{
	left.plus(right);
	return left;
}

Matrix & operator-=(Matrix & left, const double & right)
{
	left.minus(right);
	return left;
}

Matrix & operator*=(Matrix & left, const double & right)
{
	left.multiply(right);
	return left;
}

bool operator==(Matrix & A, Matrix & B)
{
	try
	{
		if(A.cols_ == B.cols_ && A.rows_ == B.rows_)
		{
			double precision = get_current_compare_precision();
			for(int i = 0; i < A.elements_.size(); i++)
			{
				if(abs(A.elements_[i] - B.elements_[i]) > precision)
				{
					return false;
				}
				else continue;
			}
			return true;
		}
		else
			throw "Error: attempt to compare matrix of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return false;
}

bool operator!=(Matrix & A, Matrix & B)
{
	try
	{
		if(A.cols_ == B.cols_ && A.rows_ == B.rows_)
		{
			double precision = get_current_compare_precision();
			for(int i = 0; i < A.elements_.size(); i++)
			{
				if(abs(A.elements_[i] - B.elements_[i]) > precision)
				{
					return true;
				}
				else continue;
			}
			return false;
		}
		else
			throw "Error: attempt to compare matrix of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return false;
}

const Matrix operator+(const Matrix & left, const Matrix & right)
{
	Matrix result = left;
	result.plus(right);
	return result;
}

const Matrix operator-(const Matrix & left, const Matrix & right)
{
	Matrix result = left;
	result.minus(right);
	return result;
}

const Matrix operator*(const Matrix & left, const Matrix & right)
{
	Matrix result = left;
	result.multiply(right);
	return result;
}

const Matrix operator+(const Matrix & left, const double & right)
{
	Matrix result = left;
	result.plus(right);
	return result;
}

const Matrix operator-(const Matrix & left, const double & right)
{
	Matrix result = left;
	result.minus(right);
	return result;
}

const Matrix operator*(const Matrix & left, const double & right)
{
	Matrix result = left;
	result.multiply(right);
	return result;
}

const Matrix operator+(const double & left, const Matrix & right)
{
	Matrix result = right;
	result.plus(left);
	return result;
}

const Matrix operator-(const double & left, const Matrix & right)
{
	Matrix result = right;
	result.minus(left);
	return result;
}

const Matrix operator*(const double & left, const Matrix & right)
{
	Matrix result = right;
	result.multiply(left);
	return result;
}

void Matrix::plus(Matrix arg)
{
	try
	{
		if(this->cols_ != arg.cols_ || this->rows_ != arg.rows_)
			throw "Error: matrix cannot be summarize";
		else
		{
			for(int i = 0; i < this->elements_.size(); i++)
			{
				elements_[i] += arg.elements_[i];
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Matrix::minus(Matrix arg)
{
	try
	{
		if(this->cols_ != arg.cols_ || this->rows_ != arg.rows_)
			throw "Error: matrix cannot be subtracted";
		else
		{
			for(int i = 0; i < this->elements_.size(); i++)
			{
				elements_[i] -= arg.elements_[i];
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Matrix::multiply(Matrix arg)
{
	Matrix matr = Matrix(rows_, arg.cols_);
	try
	{
		if(this->cols_ != arg.rows_)
			throw "Error: matrix cannot be multiplied";
		else
		{
			for(unsigned row = 0; row < this->rows_; row++)
			{
				for(unsigned col = 0; col < arg.cols_; col++)
				{
					for(unsigned inner = 0; inner < this->cols_; inner++)
					{
						matr(row, col) += this->operator()(row,inner) * arg(inner,col);
					}
				}
			}
			this->elements_ = matr.elements_;
			this->rows_ = matr.rows_;
			this->cols_ = matr.cols_;
			matr.~Matrix();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Matrix::plus(double arg)
{
	for(int i = 0; i < elements_.size(); i++)
	{
		elements_[i] += arg;
	}
}

void Matrix::minus(double arg)
{
	for(int i = 0; i < elements_.size(); i++)
	{
		elements_[i] -= arg;
	}
}

void Matrix::multiply(double arg)
{
	for(int i = 0; i < elements_.size(); i++)
	{
		elements_[i] *= arg;
	}
}


void Matrix::set_matrix(vector<double> elements)
{
	for(int i = 0; i < elements_.size(); i++)
	{
		elements_[i] = elements[i];
	}
}

double Matrix::recursive_determinant(Matrix matr)
{
	double current_determinant = 0;
	int dim = matr.cols();
	int k = 1; //power

	if(dim == 1)
	{
		current_determinant = matr(0, 0);
	}
	else
	{
		/*simple case handling*/
		if(dim == 2)
		{
			current_determinant = matr(0, 0)*matr(1, 1) - matr(1, 0)*matr(0, 1);
		}
		else
		{
			for(int i = 0; i < dim; i++)
			{
				Matrix new_matr = strike_out(matr, 0, i);
				current_determinant = current_determinant + k * matr(0, i)*recursive_determinant(new_matr);
				k = -k;

				new_matr.~Matrix();
			}
		}
	}
	return current_determinant;
}

Matrix Matrix::strike_out(Matrix matrix, unsigned row, unsigned col)
{
	Matrix new_matrix;
	try
	{
		if(row >= matrix.rows() || col >= matrix.cols())
			throw "Error: matrix subscript out of range";
		else
		{
			new_matrix = Matrix(matrix.rows() - 1, matrix.cols() - 1);
			for(unsigned i = 0, new_i = 0; i < matrix.rows(); i++)
			{
				if(i != row)
				{
					for(unsigned j = 0, new_j = 0; j < matrix.cols(); j++)
					{
						if(j != col)
						{
							new_matrix(new_i, new_j) = matrix(i, j);
							new_j++;
						}
					}
					new_i++;
				}
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return new_matrix;
}


#include "Vector.h"

void Vector::clear()
{
	n = int();
	elements.clear();
}

void Vector::reset()
{
	set_elements(0.);
}

void Vector::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(int i = 0; i < n; i++)
	{
		cout << elements[i] << " ";
	}
	cout << endl;
}

void Vector::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);
	for(int i = 0; i < n; i++)
	{
		cout << elements[i] << " ";
	}
	cout << endl;
	cout.precision(DISPLAY_PRECISION);
}

void Vector::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	for(int i = 0; i < n; i++)
	{
		ostr << elements[i] << " ";
	}
	ostr << endl;
}

void Vector::print(ofstream & ostr, streamsize precision)
{
	ostr << fixed;
	ostr.precision(precision);
	for(int i = 0; i < n; i++)
	{
		ostr << elements[i] << " ";
	}
	ostr << endl;
	ostr.precision(DISPLAY_PRECISION);
}

int Vector::size()
{
	return n;
}

void Vector::set_elements(vector<double> elements)
{
	try
	{
		if(n == elements.size())
		{
			for(int i = 0; i < n; i++)
			{
				this->elements[i] = elements[i];
			}
		}
		else
			throw "Error: attempt to create vector based on different size vector";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Vector::set_elements(double element)
{
	for(int i = 0; i < n; i++)
	{
		this->elements[i] = element;
	}
}

double & Vector::operator[](int n)
{
	return elements.at(n);
}

const Vector & operator+(const Vector & i)
{
	return i;
}

const Vector operator-(const Vector & i)
{
	Vector vec = Vector(i.n);
	for(int k = 0; k < i.n; k++)
	{
		vec[k] = -i.elements[k];
	}
	return vec;
}

Vector & operator+=(Vector & left, const Vector & right)
{
	left.plus(right);
	return left;
}

Vector & operator-=(Vector & left, const Vector & right)
{
	left.minus(right);
	return left;
}

Vector & operator*=(Vector & left, const Vector & right)
{
	left.multiply(right);
	return left;
}

Vector & operator/=(Vector & left, const Vector & right)
{
	left.divide(right);
	return left;
}

Vector & operator+=(Vector & left, const double & right)
{
	left.plus(right);
	return left;
}

Vector & operator-=(Vector & left, const double & right)
{
	left.minus(right);
	return left;
}

Vector & operator*=(Vector & left, const double & right)
{
	left.multiply(right);
	return left;
}

Vector & operator/=(Vector & left, const double & right)
{
	left.divide(right);
	return left;
}

bool operator==(Vector & A, Vector & B)
{
	try
	{
		if(A.size() == B.size())
		{
			double precision = get_current_compare_precision();
			for(int i = 0; i < A.size(); i++)
			{
				if(abs(A[i] - B[i]) > precision)
				{
					return false;
				}
				else continue;
			}
			return true;
		}
		else
			throw "Error: attempt to compare vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return false;
}

bool operator!=(Vector & A, Vector & B)
{
	try
	{
		if(A.size() == B.size())
		{
			double precision = get_current_compare_precision();
			for(int i = 0; i < A.size(); i++)
			{
				if(abs(A[i] - B[i]) > precision)
				{
					return true;
				}
				else continue;
			}
			return false;
		}
		else
			throw "Error: attempt to compare vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return false;
}

const Vector operator+(const Vector & left, const Vector & right)
{
	Vector result = left;
	result.plus(right);
	return result;
}

const Vector operator-(const Vector & left, const Vector & right)
{
	Vector result = left;
	result.minus(right);
	return result;
}

const Vector operator*(const Vector & left, const Vector & right)
{
	Vector result = left;
	result.multiply(right);
	return result;
}

const Vector operator/(const Vector & left, const Vector & right)
{
	Vector result = left;
	result.divide(right);
	return result;
}

const Vector operator+(const Vector & left, const double & right)
{
	Vector result = left;
	result.plus(right);
	return result;
}

const Vector operator-(const Vector & left, const double & right)
{
	Vector result = left;
	result.minus(right);
	return result;
}

const Vector operator*(const Vector & left, const double & right)
{
	Vector result = left;
	result.multiply(right);
	return result;
}

const Vector operator/(const Vector & left, const double & right)
{
	Vector result = left;
	result.divide(right);
	return result;
}
const Vector operator+(const double & left, const Vector & right)
{
	Vector result = right;
	result.plus(left);
	return result;
}

const Vector operator-(const double & left, const Vector & right)
{
	Vector result = right;
	result.minus(left);
	return result;
}

const Vector operator*(const double & left, const Vector & right)
{
	Vector result = right;
	result.multiply(left);
	return result;
}

const Vector operator/(const double & left, const Vector & right)
{
	Vector result = right;
	result.divide(left);
	return result;
}

void Vector::plus(Vector arg)
{
	try
	{
		if(arg.size() == n)
		{
			for(int i = 0; i < n; i++)
			{
				elements[i] += arg.elements[i];
			}
		}
		else
			throw "Error: attempt to summation vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Vector::minus(Vector arg)
{
	try
	{
		if(arg.size() == n)
		{
			for(int i = 0; i < n; i++)
			{
				elements[i] -= arg.elements[i];
			}
		}
		else
			throw "Error: attempt to subtract vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Vector::multiply(Vector arg)
{
	try
	{
		if(arg.size() == n)
		{
			for(int i = 0; i < n; i++)
			{
				elements[i] *= arg.elements[i];
			}
		}
		else
			throw "Error: attempt to multiply vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Vector::divide(Vector arg)
{
	try
	{
		if(arg.size() == n)
		{
			for(int i = 0; i < n; i++)
			{
				elements[i] /= arg.elements[i];
			}
		}
		else
			throw "Error: attempt to divide vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
}

void Vector::plus(double arg)
{
	for(int i = 0; i < n; i++)
	{
		elements[i] += arg;
	}
}

void Vector::minus(double arg)
{
	for(int i = 0; i < n; i++)
	{
		elements[i] -= arg;
	}
}

void Vector::multiply(double arg)
{
	for(int i = 0; i < n; i++)
	{
		elements[i] *= arg;
	}
}

void Vector::divide(double arg)
{
	for(int i = 0; i < n; i++)
	{
		elements[i] /= arg;
	}
}

void Vector3D::set_elements(Point3D point)
{
	for(int i = 0; i < n; i++)
	{
		elements[i] = point[i];
	}
}

Vector3D Vector3D::operator=(const Vector & v1)
{
	try
	{
		if(v1.n == n)
		{
			if(&v1 == this)
				return *this;
			return Vector3D(this->elements = v1.elements);
		}
		else
			throw "Error: attempt to assign Vector of different sizes to Vector3D";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return Vector3D();
}


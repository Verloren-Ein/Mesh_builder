#include "Point.h"

/*2D POINT METHODS*/
void Point2D::reset()
{
	x = double();
	y = double();
}

void Point2D::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	cout << x << " " << y << endl;
}

void Point2D::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);
	cout << x << " " << y << endl;
	cout.precision(DISPLAY_PRECISION);
}

void Point2D::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	ostr << x << " " << y << endl;
}

void Point2D::print(ofstream & ostr, streamsize precision)
{
	ostr << fixed;
	ostr.precision(precision);
	ostr << x << " " << y << endl;
	ostr.precision(DISPLAY_PRECISION);
}

double& Point2D::operator[](int n)
{
	try
	{
		if(n < 2)
		{
			if(n == 0)
				return this->x;
			if(n == 1)
				return this->y;
		}
		else
			throw "Error: point index out of range";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	
}

const Point2D & operator+(const Point2D & i)
{
	return i;
}

const Point2D operator-(const Point2D & i)
{
	return Point2D(-i.x, -i.y);
}

Point2D & operator+=(Point2D & left, const Point2D & right)
{
	left.plus(right);
	return left;
}

Point2D & operator-=(Point2D & left, const Point2D & right)
{
	left.minus(right);
	return left;
}

Point2D & operator*=(Point2D & left, const Point2D & right)
{
	left.multiply(right);
	return left;
}

Point2D & operator/=(Point2D & left, const Point2D & right)
{
	left.divide(right);
	return left;
}

Point2D & operator+=(Point2D & left, const double & right)
{
	left.plus(right);
	return left;
}

Point2D & operator-=(Point2D & left, const double & right)
{
	left.minus(right);
	return left;
}

Point2D & operator*=(Point2D & left, const double & right)
{
	left.multiply(right);
	return left;
}

Point2D & operator/=(Point2D & left, const double & right)
{
	left.divide(right);
	return left;
}

bool operator==(Point2D & A, Point2D & B)
{
	double precision = get_current_compare_precision();
	if(abs(A.x - B.x) > precision || abs(A.y - B.y) > precision)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

bool operator!=(Point2D & A, Point2D & B)
{
	double precision = get_current_compare_precision();
	if(abs(A.x - B.x) < precision && abs(A.y - B.y) < precision)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

const Point2D operator+(const Point2D & left, const Point2D & right)
{
	Point2D result = left;
	result.plus(right);
	return result;
}

const Point2D operator-(const Point2D & left, const Point2D & right)
{
	Point2D result = left;
	result.minus(right);
	return result;
}

const Point2D operator*(const Point2D & left, const Point2D & right)
{
	Point2D result = left;
	result.multiply(right);
	return result;
}

const Point2D operator/(const Point2D & left, const Point2D & right)
{
	Point2D result = left;
	result.divide(right);
	return result;
}

const Point2D operator+(const Point2D & left, const double & right)
{
	Point2D result = left;
	result.plus(right);
	return result;
}

const Point2D operator-(const Point2D & left, const double & right)
{
	Point2D result = left;
	result.minus(right);
	return result;
}

const Point2D operator*(const Point2D & left, const double & right)
{
	Point2D result = left;
	result.multiply(right);
	return result;
}

const Point2D operator/(const Point2D & left, const double & right)
{
	Point2D result = left;
	result.divide(right);
	return result;
}

const Point2D operator+(const double & left, const Point2D & right)
{
	Point2D result = right;
	result.plus(left);
	return result;
}

const Point2D operator-(const double & left, const Point2D & right)
{
	Point2D result = right;
	result.minus(left);
	return result;
}

const Point2D operator*(const double & left, const Point2D & right)
{
	Point2D result = right;
	result.multiply(left);
	return result;
}

const Point2D operator/(const double & left, const Point2D & right)
{
	Point2D result = right;
	result.divide(left);
	return result;
}

void Point2D::plus(Point2D arg)
{
	this->x += arg.x;
	this->y += arg.y;
}

void Point2D::minus(Point2D arg)
{
	this->x -= arg.x;
	this->y -= arg.y;
}

void Point2D::multiply(Point2D arg)
{
	this->x *= arg.x;
	this->y *= arg.y;
}

void Point2D::divide(Point2D arg)
{
	this->x /= arg.x;
	this->y /= arg.y;
}

void Point2D::plus(double arg)
{
	this->x += arg;
	this->y += arg;
}

void Point2D::minus(double arg)
{
	this->x -= arg;
	this->y -= arg;
}

void Point2D::multiply(double arg)
{
	this->x *= arg;
	this->y *= arg;
}

void Point2D::divide(double arg)
{
	this->x /= arg;
	this->y /= arg;
}


/*3D POINT METHODS*/
void Point3D::reset()
{
	x = double();
	y = double();
	z = double();
}

void Point3D::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	cout << x << " " << y << " " << z << endl;
}

void Point3D::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);
	cout << x << " " << y << " " << z << endl;
	cout.precision(DISPLAY_PRECISION);
}

void Point3D::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	ostr << x << " " << y << " " << z << endl;
}

void Point3D::print(ofstream & ostr, streamsize precition)
{
	ostr << fixed;
	ostr.precision(precition);
	ostr << x << " " << y << " " << z << endl;
	ostr.precision(DISPLAY_PRECISION);
}

double & Point3D::operator[](int n)
{
	try
	{
		if(n < 3)
		{
			if(n == 0)
				return this->x;
			if(n == 1)
				return this->y;
			if(n == 2)
				return this->z;
		}
		else
			throw "Error: point index out of range";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	//return NULL;
}

const Point3D & operator+(const Point3D & i)
{
	return i;
}

const Point3D operator-(const Point3D & i)
{
	return Point3D(-i.x, -i.y, -i.z);
}

Point3D & operator+=(Point3D & left, const Point3D & right)
{
	left.plus(right);
	return left;
}

Point3D & operator-=(Point3D & left, const Point3D & right)
{
	left.minus(right);
	return left;
}

Point3D & operator*=(Point3D & left, const Point3D & right)
{
	left.multiply(right);
	return left;
}

Point3D & operator/=(Point3D & left, const Point3D & right)
{
	left.divide(right);
	return left;
}

Point3D & operator+=(Point3D & left, const double & right)
{
	left.plus(right);
	return left;
}

Point3D & operator-=(Point3D & left, const double & right)
{
	left.minus(right);
	return left;
}

Point3D & operator*=(Point3D & left, const double & right)
{
	left.multiply(right);
	return left;
}

Point3D & operator/=(Point3D & left, const double & right)
{
	left.divide(right);
	return left;
}

bool operator==(Point3D & A, Point3D & B)
{
	double precision = get_current_compare_precision();
	if(abs(A.x - B.x) > precision || abs(A.y - B.y) > precision || abs(A.z - B.z) > precision)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

bool operator!=(Point3D & A, Point3D & B)
{
	double precision = get_current_compare_precision();
	if(abs(A.x - B.x) < precision && abs(A.y - B.y) < precision && abs(A.z - B.z) < precision)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

const Point3D operator+(const Point3D & left, const Point3D & right)
{
	Point3D result = left;
	result.plus(right);
	return result;
}

const Point3D operator-(const Point3D & left, const Point3D & right)
{
	Point3D result = left;
	result.minus(right);
	return result;
}

const Point3D operator*(const Point3D & left, const Point3D & right)
{
	Point3D result = left;
	result.multiply(right);
	return result;
}

const Point3D operator/(const Point3D & left, const Point3D & right)
{
	Point3D result = left;
	result.divide(right);
	return result;
}

const Point3D operator+(const Point3D & left, const double & right)
{
	Point3D result = left;
	result.plus(right);
	return result;
}

const Point3D operator-(const Point3D & left, const double & right)
{
	Point3D result = left;
	result.minus(right);
	return result;
}

const Point3D operator*(const Point3D & left, const double & right)
{
	Point3D result = left;
	result.multiply(right);
	return result;
}

const Point3D operator/(const Point3D & left, const double & right)
{
	Point3D result = left;
	result.divide(right);
	return result;
}

const Point3D operator+(const double & left, const Point3D & right)
{
	Point3D result = right;
	result.plus(left);
	return result;
}

const Point3D operator-(const double & left, const Point3D & right)
{
	Point3D result = right;
	result.minus(left);
	return result;
}

const Point3D operator*(const double & left, const Point3D & right)
{
	Point3D result = right;
	result.multiply(left);
	return result;
}

const Point3D operator/(const double & left, const Point3D & right)
{
	Point3D result = right;
	result.divide(left);
	return result;
}

void Point3D::plus(Point3D arg)
{
	this->x += arg.x;
	this->y += arg.y;
	this->z += arg.z;
}

void Point3D::minus(Point3D arg)
{
	this->x -= arg.x;
	this->y -= arg.y;
	this->z -= arg.z;
}

void Point3D::multiply(Point3D arg)
{
	this->x *= arg.x;
	this->y *= arg.y;
	this->z *= arg.z;
}

void Point3D::divide(Point3D arg)
{
	this->x /= arg.x;
	this->y /= arg.y;
	this->z /= arg.z;
}

void Point3D::plus(double arg)
{
	this->x += arg;
	this->y += arg;
	this->z += arg;
}

void Point3D::minus(double arg)
{
	this->x -= arg;
	this->y -= arg;
	this->z -= arg;
}

void Point3D::multiply(double arg)
{
	this->x *= arg;
	this->y *= arg;
	this->z *= arg;
}

void Point3D::divide(double arg)
{
	this->x /= arg;
	this->y /= arg;
	this->z /= arg;
}

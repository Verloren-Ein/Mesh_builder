#pragma once
#include "common.h"

class Point2D
{
protected:
	double x;
	double y;

public:
	Point2D()
	{
		x = double();
		y = double();
	}
	Point2D(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	void reset();
	void display();
	void display(streamsize precision);
	void print(ofstream &ostr);
	void print(ofstream &ostr, streamsize precision);

	/*operators overloading*/
	/*index access operator*/
	double& operator[](int n); /*right/left access*/

	/*unary operators*/
	friend const Point2D& operator+(const Point2D& i);
	friend const Point2D operator-(const Point2D& i);

	friend Point2D& operator+=(Point2D& left, const Point2D& right);
	friend Point2D& operator-=(Point2D& left, const Point2D& right);
	friend Point2D& operator*=(Point2D& left, const Point2D& right);
	friend Point2D& operator/=(Point2D& left, const Point2D& right);
		
	friend Point2D& operator+=(Point2D& left, const double& right);
	friend Point2D& operator-=(Point2D& left, const double& right);
	friend Point2D& operator*=(Point2D& left, const double& right);
	friend Point2D& operator/=(Point2D& left, const double& right);
	
	/*binary operators*/
	friend bool operator ==(Point2D &A, Point2D &B);
	friend bool operator !=(Point2D &A, Point2D &B);

	friend const Point2D operator+(const Point2D& left, const Point2D& right);
	friend const Point2D operator-(const Point2D& left, const Point2D& right);
	friend const Point2D operator*(const Point2D& left, const Point2D& right);
	friend const Point2D operator/(const Point2D& left, const Point2D& right);

	friend const Point2D operator+(const Point2D& left, const double& right);
	friend const Point2D operator-(const Point2D& left, const double& right);
	friend const Point2D operator*(const Point2D& left, const double& right);
	friend const Point2D operator/(const Point2D& left, const double& right);
	
	friend const Point2D operator+(const double& left, const Point2D&  right);
	friend const Point2D operator-(const double& left, const Point2D&  right);
	friend const Point2D operator*(const double& left, const Point2D&  right);
	friend const Point2D operator/(const double& left, const Point2D&  right);

protected:
	/*arithmetic operations*/
	virtual void plus(Point2D arg);		// x + arg.x, y + arg.y
	virtual void minus(Point2D arg);	// x - arg.x, y - arg.y
	virtual void multiply(Point2D arg);	// x * arg.x, y * arg.y
	virtual void divide(Point2D arg);	// x : arg.x, y : arg.y

	void plus(double arg);		// x + arg, y + arg
	void minus(double arg);		// x - arg, y - arg
	void multiply(double arg);	// x * arg, y * arg
	void divide(double arg);	// x : arg, y : arg
};


class Point3D : public Point2D
{
protected:
	double z;

public:
	Point3D() : Point2D()
	{
		z = double();
	}
	Point3D(double x, double y, double z) : Point2D(x, y)
	{
		this->z = z;
	}
	void reset();
	void display();
	void display(streamsize precision);
	void print(ofstream &ostr);
	void print(ofstream &ostr, streamsize precition);

	/*operators overloading*/
	/*index access operator*/
	double& operator[](int n); /*right/left access*/

	/*unary operators*/
	friend const Point3D& operator+(const Point3D& i);
	friend const Point3D operator-(const Point3D& i);

	friend Point3D& operator+=(Point3D& left, const Point3D& right);
	friend Point3D& operator-=(Point3D& left, const Point3D& right);
	friend Point3D& operator*=(Point3D& left, const Point3D& right);
	friend Point3D& operator/=(Point3D& left, const Point3D& right);

	friend Point3D& operator+=(Point3D& left, const double& right);
	friend Point3D& operator-=(Point3D& left, const double& right);
	friend Point3D& operator*=(Point3D& left, const double& right);
	friend Point3D& operator/=(Point3D& left, const double& right);

	/*binary operators*/
	friend bool operator ==(Point3D &A, Point3D &B);
	friend bool operator !=(Point3D &A, Point3D &B);

	friend const Point3D operator+(const Point3D& left, const Point3D& right);
	friend const Point3D operator-(const Point3D& left, const Point3D& right);
	friend const Point3D operator*(const Point3D& left, const Point3D& right);
	friend const Point3D operator/(const Point3D& left, const Point3D& right);

	friend const Point3D operator+(const Point3D& left, const double& right);
	friend const Point3D operator-(const Point3D& left, const double& right);
	friend const Point3D operator*(const Point3D& left, const double& right);
	friend const Point3D operator/(const Point3D& left, const double& right);

	friend const Point3D operator+(const double& left, const Point3D&  right);
	friend const Point3D operator-(const double& left, const Point3D&  right);
	friend const Point3D operator*(const double& left, const Point3D&  right);
	friend const Point3D operator/(const double& left, const Point3D&  right);

protected:
	/*arithmetic operations*/
	virtual void plus(Point3D arg);		// x + arg.x, y + arg.y
	virtual void minus(Point3D arg);	// x - arg.x, y - arg.y
	virtual void multiply(Point3D arg);	// x * arg.x, y * arg.y
	virtual void divide(Point3D arg);	// x : arg.x, y : arg.y
	
	void plus(double arg);		// x + arg, y + arg
	void minus(double arg);		// x - arg, y - arg
	void multiply(double arg);	// x * arg, y * arg
	void divide(double arg);	// x : arg, y : arg
	
};
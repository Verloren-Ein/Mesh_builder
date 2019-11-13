#pragma once
#include "common.h"
#include "Point.h"

#define VECTOR3D_SIZE 3

class Vector
{
private:
	int n;

protected:
	vector<double> elements;
	friend class Vector3D;

public:
	Vector()
	{
		n = int();
		elements.clear();
	}
	Vector(int n)
	{
		this->n = n;
		elements.clear();
		elements.resize(n);
	}
	Vector(vector<double> elements)
	{
		this->n = int(elements.size());
		this->elements.clear();
		this->elements.resize(n);
		this->set_elements(elements);
	}
	Vector(int n, double element)
	{
		this->n = n;
		this->elements.clear();
		this->elements.resize(n);
		this->set_elements(element);
	}
	~Vector()
	{
		elements.clear();
		elements.~vector();
	}
	void clear();
	void reset();
	void display();
	void display(streamsize precision);
	void print(ofstream &ostr);
	void print(ofstream &ostr, streamsize precision);
	int size();
	void set_elements(vector<double> elements);
	void set_elements(double element);

	/*operators overloading*/
	/*subscript operator*/
	double& operator[](int n); /*right/left access*/

	/*unary operators*/
	friend const Vector& operator+(const Vector& i);
	friend const Vector operator-(const Vector& i);

	friend Vector& operator+=(Vector& left, const Vector& right);
	friend Vector& operator-=(Vector& left, const Vector& right);
	friend Vector& operator*=(Vector& left, const Vector& right);
	friend Vector& operator/=(Vector& left, const Vector& right);

	friend Vector& operator+=(Vector& left, const double& right);
	friend Vector& operator-=(Vector& left, const double& right);
	friend Vector& operator*=(Vector& left, const double& right);
	friend Vector& operator/=(Vector& left, const double& right);

	/*binary operators*/
	friend bool operator ==(Vector &A, Vector &B);
	friend bool operator !=(Vector &A, Vector &B);

	friend const Vector operator+(const Vector& left, const Vector& right);
	friend const Vector operator-(const Vector& left, const Vector& right);
	friend const Vector operator*(const Vector& left, const Vector& right);
	friend const Vector operator/(const Vector& left, const Vector& right);

	friend const Vector operator+(const Vector& left, const double& right);
	friend const Vector operator-(const Vector& left, const double& right);
	friend const Vector operator*(const Vector& left, const double& right);
	friend const Vector operator/(const Vector& left, const double& right);

	friend const Vector operator+(const double& left, const Vector&  right);
	friend const Vector operator-(const double& left, const Vector&  right);
	friend const Vector operator*(const double& left, const Vector&  right);
	friend const Vector operator/(const double& left, const Vector&  right);
	
protected:
	/*arithmetic operations*/
	virtual void plus(Vector arg);		// elements[i] + arg[i]
	virtual void minus(Vector arg);		// elements[i] - arg[i]
	virtual void multiply(Vector arg);	// elements[i] * arg[i]
	virtual void divide(Vector arg);	// elements[i] / arg[i]
	
	void plus(double arg);		// elements[i] + arg
	void minus(double arg);		// elements[i] - arg
	void multiply(double arg);	// elements[i] * arg
	void divide(double arg);	// elements[i] / arg
};

class Vector3D : public Vector
{
private:
	int n;
	using Vector::set_elements;

public:
	Vector3D() : Vector(VECTOR3D_SIZE)
	{
		n = VECTOR3D_SIZE;
		elements.clear();
		elements.resize(n);
	}
	Vector3D(vector<double> elements) : Vector(VECTOR3D_SIZE)
	{
		n = VECTOR3D_SIZE;
		this->elements.clear();
		this->elements.resize(n);
		this->set_elements(elements);

	}
	Vector3D(double element) : Vector(VECTOR3D_SIZE)
	{
		n = VECTOR3D_SIZE;
		this->elements.clear();
		this->elements.resize(n);
		this->set_elements(element);
	}
	Vector3D(Point3D point) : Vector(VECTOR3D_SIZE)
	{
		n = VECTOR3D_SIZE;
		this->elements.clear();
		this->elements.resize(n);
		this->set_elements(point);
	}
	~Vector3D()
	{
		elements.clear();
		elements.~vector();
	}
	void set_elements(Point3D point);

	/*operators overloading*/
	Vector3D operator = (const Vector &v1);

};
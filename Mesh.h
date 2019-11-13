#pragma once
#include "common.h"
#include "Point.h"

/***********************************************/
/*MESH STRUCTURES*/
/***********************************************/

//node in 3D
class Node3D
{
private:
	Point3D coordinates;
	int number;
	/*node participation in calculations*/
	/*true - involved; false - not involved*/
	bool needful;

public:
	Node3D()
		:coordinates()
		, number(-1)
		, needful(false)
	{}
	Node3D(Point3D point, int number, bool needful)
		:coordinates(point)
		, number(number)
		, needful(needful)
	{}
	Node3D(double x, double y, double z, int number, bool needful)
		:coordinates(x, y, z)
		, number(number)
		, needful(needful)
	{}
	void reset();
	void display();
	void display(streamsize precision);
	void print(ofstream &ostr);
	void print(ofstream &ostr, streamsize precision);

	/*set-functions*/
	void set_node(Point3D point, int number, bool needful);
	void set_node(double x, double y, double z, int number, bool needful);

	/*get-functions*/
	Point3D get_coordinates();
	int get_number();
	bool get_needful();
};

//first boundary conditions
class FirstBC
{
private:
	int number;
	int n_formula;

public:
	FirstBC()
		:number(-1)
		, n_formula(-1)
	{}
	FirstBC(int number, int n_formula)
		:number(number)
		, n_formula(n_formula)
	{}
	void reset();
	void display();
	void print(ofstream &ostr);

	/*set-functions*/
	void set_firstBC(int number, int n_formula);

	/*get-functions*/
	int get_number();
	int get_n_formula();
};

//face of finite element mesh
class Face
{
private:
	vector<int> numbers;
	int n_formula;

public:
	Face()
		:n_formula(-1)
	{
		numbers.clear();
	}
	Face(vector<int> numbers, int n_formula)
		:n_formula(n_formula)
	{
		this->numbers = numbers;
	}
	~Face()
	{
		numbers.clear();
		numbers.~vector();
	}
	void reset();
	void display();
	void print(ofstream &ostr);

	/*set-functions*/
	void set_face(vector<int> numbers, int n_formula);

	/*get-functions*/
	vector<int> get_numbers();
	int get_number(int i);
	int get_n_formula();
};

//finite element
class FE
{
private: 
	vector<int> numbers;
	int n_area;
	/*fe participation in calculations*/
	/*true - involved; false - not involved*/
	bool needful;

public:
	FE()
		:n_area(-1)
		, needful(false)
	{
		numbers.clear();
	}
	FE(vector<int> numbers, int n_area, bool needful)
		:n_area(n_area)
		, needful(needful)
	{
		this->numbers = numbers;
	}
	~FE()
	{
		numbers.clear();
		numbers.~vector();
	}
	void reset();
	void display();
	void print(ofstream &ostr);

	/*set-functions*/
	void set_fe(vector<int> numbers, int n_area, bool needful);

	/*get-functions*/
	vector<int> get_numbers();
	int get_number(int i);
	int get_n_area();
	bool get_needful();
};


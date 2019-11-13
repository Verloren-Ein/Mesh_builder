#include"Mesh.h"

/***********************************************/
/*MESH STRUCTURES*/
/***********************************************/

/*----------------------------*/
/*Node`s functions*/
/*----------------------------*/

void Node3D::reset()
{
	coordinates = Point3D();
	number = -1;
	needful = false;
}

void Node3D::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	cout << number << " " 
		<< coordinates[0] << " " 
		<< coordinates[1] << " " 
		<< coordinates[2] << " " 
		<< needful << endl;
}

void Node3D::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);
	cout << number << " "
		<< coordinates[0] << " "
		<< coordinates[1] << " "
		<< coordinates[2] << " "
		<< needful << endl;
	cout.precision(DISPLAY_PRECISION);
}

void Node3D::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	ostr << number << " "
		<< coordinates[0] << " "
		<< coordinates[1] << " "
		<< coordinates[2] << " "
		<< needful << endl;
}

void Node3D::print(ofstream & ostr, streamsize precision)
{
	ostr << fixed;
	ostr.precision(precision);
	ostr << number << " "
		<< coordinates[0] << " "
		<< coordinates[1] << " "
		<< coordinates[2] << " "
		<< needful << endl;
	ostr.precision(DISPLAY_PRECISION);
}

void Node3D::set_node(Point3D point, int number, bool needful)
{
	coordinates = point;
	this->number = number;
	this->needful = needful;
}

void Node3D::set_node(double x, double y, double z, int number, bool needful)
{
	coordinates = Point3D(x, y, z);
	this->number = number;
	this->needful = needful;
}

Point3D Node3D::get_coordinates()
{
	return coordinates;
}

int Node3D::get_number()
{
	return number;
}

bool Node3D::get_needful()
{
	return needful;
}

/*----------------------------*/
/*firstBC`s functions*/
/*----------------------------*/

void FirstBC::reset()
{
	number = -1;
	n_formula = -1;
}

void FirstBC::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	cout << number << " " << n_formula << endl;
}

void FirstBC::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	ostr << number << " " << n_formula << endl;
}

void FirstBC::set_firstBC(int number, int n_formula)
{
	this->number = number;
	this->n_formula = n_formula;
}

int FirstBC::get_number()
{
	return number;
}

int FirstBC::get_n_formula()
{
	return n_formula;
}

/*----------------------------*/
/*face`s functions*/
/*----------------------------*/

void Face::reset()
{
	numbers.clear();
	n_formula = -1;
}

void Face::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(int i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i] << " ";
	}
	cout << n_formula << endl;
}

void Face::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	for(int i = 0; i < numbers.size(); i++)
	{
		ostr << numbers[i] << " ";
	}
	ostr << n_formula << endl;
}

void Face::set_face(vector<int> numbers, int n_formula)
{
	this->numbers = numbers;
	this->n_formula = n_formula;
}

vector<int> Face::get_numbers()
{
	return numbers;
}

int Face::get_number(int i)
{
	return numbers[i];
}

int Face::get_n_formula()
{
	return n_formula;
}

/*----------------------------*/
/*fe`s functions*/
/*----------------------------*/

void FE::reset()
{
	numbers.clear();
	n_area = -1;
	needful = false;
}

void FE::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(int i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i] << " ";
	}
	cout << n_area << " " << needful << endl;
}

void FE::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	for(int i = 0; i < numbers.size(); i++)
	{
		ostr << numbers[i] << " ";
	}
	ostr << n_area << " " << needful << endl;
}

void FE::set_fe(vector<int> numbers, int n_area, bool needful)
{
	this->numbers = numbers;
	this->n_area = n_area;
	this->needful = needful;
}

vector<int> FE::get_numbers()
{
	return numbers;
}

int FE::get_number(int i)
{
	return numbers[i];
}

int FE::get_n_area()
{
	return n_area;
}

bool FE::get_needful()
{
	return needful;
}

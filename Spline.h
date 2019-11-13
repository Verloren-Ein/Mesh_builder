#pragma once
#include "common.h"
#include "Gauss.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "functions.h"

#define ENOUGH_NODE 3

/***********************************************/
/*SYNTHETIC DATA GENERATION*/
/***********************************************/

/*create synthetic data for testing spline classes*/
void create_data(vector<double>* X, vector<double>* F);
void create_data(vector<double>* X, vector<double>* Y, Matrix* Z);

/*explicit function for testing spline classes*/
double e_function(double x, double y);
double e_function(double x);


/***********************************************/
/*INTERPOLATION SPLINES*/
/***********************************************/

//1D interpolation spline with linear basis function
class Spline1D_linear
{
protected:
	/*initial mesh*/
	int nx_;
	vector<double> X_;
	vector<double> F_;

	/*current fe values*/
	int nfex_;
	double hx_;
	/*reset fe values*/
	void reset_fe();

private:
	/*basis linear function*/
	/*i - function number*/
	double basis_function(int i, double x);

public:
	Spline1D_linear()
		:nx_()
		, nfex_(-1)
		, hx_()
	{
		X_.clear();
		F_.clear();
	}
	Spline1D_linear(vector<double> X, vector<double> F)
		:nx_(int(X.size()))
		, nfex_(-1)
		, hx_()
	{
		X_.clear();
		F_.clear();
		X_ = X;
		F_ = F;
	}
	~Spline1D_linear()
	{
		X_.clear();
		F_.clear();
		X_.~vector();
		F_.~vector();
	}

	void display();
	void display(streamsize precision);
	void print(ofstream& ostr);
	void print(ofstream& ostr, streamsize precision);

	/*returns value calculated using bilinear functions*/
	double get_value(double x);

	/*for testing*/
	Spline1D_linear get_spline(int nx);
};

//1D interpolation spline with cubic Hermitian basis function
class Spline1D_cubic : public Spline1D_linear
{
private:
	/*dfx calculation*/
	Matrix A;
	Vector b;
	Vector dfx;

	/*ensures the regularity of the first derivative*/
	void calculate_dfx_1();
	/*ensures the regularity of the second derivative*/
	void calculate_dfx_2();

	/*basis cubic functions*/
	/*i - function number*/
	double basis_function(int i, double x);
	/*functions for derivative calculate*/
	double basis_function_df(int i, double x);

public:
	Spline1D_cubic()
		: Spline1D_linear()
	{
		X_.clear();
		F_.clear();
		A.clear();
		b.clear();
		dfx.clear();
	}
	Spline1D_cubic(vector<double> X, vector<double> F)
		:Spline1D_linear(X, F)
	{
		A.clear();
		b.clear();
		dfx.clear();

		A = Matrix(nx_, nx_);
		b = Vector(nx_);
		dfx = Vector(nx_);

		/*calculate if enough nodes are set*/
		if(nx_ >= ENOUGH_NODE)
		{
			calculate_dfx_1();
			//calculate_dfx_2();
		}
		
	}
	~Spline1D_cubic()
	{
		X_.clear();
		F_.clear();
		X_.~vector();
		F_.~vector();

		A.~Matrix();
		b.~Vector();
		dfx.~Vector();
	}

	/*returns value calculated using cubic functions*/
	double get_value(double x);
	/*returns derivative value calculated using cubic functions*/
	double get_dfvalue(double x);

	/*for testing*/
	Spline1D_cubic get_spline(int nx);
	Spline1D_cubic get_dfspline(int nx);
};


/*2D interpolation spline with bilinear basis function*/
class Spline2D_linear
{
protected:
	/*size of initial mesh*/
	int nx_;
	int ny_;

	vector<double> X_;
	vector<double> Y_;
	Matrix Z_;

	/*current fe values*/
	int nfex_;
	int nfey_;
	double hx_;
	double hy_;
	/*reset fe values*/
	void reset_fe();

private:
	/*define index of the template linear function by the number of the local basis function*/
	int myu_(int i);
	int nyu_(int i);

	/*template linear function*/
	/*i - function number*/
	double temp_function_X(int i, double x);
	double temp_function_Y(int i, double y);

	/*basis linear function*/
	/*i - function number*/
	double basis_function(int i, double x, double y);

public:
	Spline2D_linear()
		:nx_()
		, ny_()
		, nfex_(-1)
		, nfey_(-1)
		, hx_()
		, hy_()
	{
		X_.clear();
		Y_.clear();
		Z_.clear();
	}
	Spline2D_linear(vector<double> X, vector<double> Y, Matrix Z)
		:nx_(int(X.size()))
		, ny_(int(Y.size()))
		, nfex_(-1)
		, nfey_(-1)
		, hx_()
		, hy_()
	{
		X_ = X;
		Y_ = Y;
		Z_ = Z;
	}
	~Spline2D_linear()
	{
		X_.clear();
		Y_.clear();
		X_.~vector();
		Y_.~vector();
		Z_.~Matrix();
	}

	void display();
	void display(streamsize precision);
	void print(ofstream& ostr);
	void print(ofstream& ostr, streamsize precision);

	/*returns value calculated using bilinear functions*/
	double get_value(double x, double y);
	double get_value(Point2D p);

	/**/
	Spline2D_linear get_spline(int nx, int ny);
};

/*2D interpolation spline with bicubic basis function*/
class Spline2D_cubic:public Spline2D_linear
{
private:
	/*x-splines with fixed y*/
	vector<Spline1D_cubic> spline_X;
	/*y-splines with fixed x*/
	vector<Spline1D_cubic> spline_Y;
	/*dx-splines */
	vector<Spline1D_cubic> spline_dX;

	/*dx values with fixed y*/
	Matrix dX_;
	/*dy values with fixed x*/
	Matrix dY_;
	/*dxy values*/
	Matrix dXY_;

	/*calculate required splines*/
	void calculate_x_splines();
	void calculate_y_splines();

	/*calculate required derivative splines*/
	void calculate_dx_splines();
	void calculate_dy_splines();
	void calculate_dxy_splines();

	/*define index of the template linear function by the number of the local basis function*/
	/*i [1:16]*/
	int myu_(int i);
	int nyu_(int i);

	/*template cubic function*/
	/*i - function number*/
	double temp_function(int i, double x);

	/*basis cubic function*/
	/*i - function number*/
	double basis_function(int i, double x, double y);

public:
	Spline2D_cubic()
		: Spline2D_linear()
	{
		spline_X.clear();
		spline_Y.clear();
	}
	Spline2D_cubic(vector<double> X, vector<double> Y, Matrix Z)
		:Spline2D_linear(X, Y, Z)
	{
		spline_X.resize(ny_);
		spline_Y.resize(nx_);
		spline_dX.resize(nx_);
		dX_ = Matrix(ny_, nx_);
		dY_ = Matrix(ny_, nx_);
		dXY_ = Matrix(ny_, nx_);

		/*calculate if enough nodes are set*/
		if(nx_ >= ENOUGH_NODE && ny_ >= ENOUGH_NODE)
		{
			calculate_x_splines();
			calculate_y_splines();
			calculate_dx_splines();
			calculate_dy_splines();
			calculate_dxy_splines();
		}
	}
	~Spline2D_cubic()
	{
		X_.clear();
		Y_.clear();
		spline_X.clear();
		spline_Y.clear();
		spline_dX.clear();
		X_.~vector();
		Y_.~vector();
		spline_X.~vector();
		spline_Y.~vector();
		spline_dX.~vector();
		dX_.~Matrix();
		dY_.~Matrix();
		dXY_.~Matrix();
		Z_.~Matrix();
	}

	/*returns value calculated using bicubic functions*/
	double get_value(double x, double y);
	double get_value(Point2D p);

	/*for testing*/
	Spline2D_cubic get_spline(int nx, int ny);
};

#include "Spline.h"

/***********************************************/
/*SYNTHETIC DATA GENERATION*/
/***********************************************/

void create_data(vector<double>* X, vector<double>* F)
{
	vector<double> X_;
	vector<double> F_;

	/*number of segment splits*/
	int nx;

	/*begin/end points of X-segment*/
	double x0;
	double xn;

	/*steps*/
	double hx;

	/*initial data*/
	nx = 5;
	x0 = 0;
	xn = 10;
	hx = abs(xn - x0) / double(nx);

	X_.resize(nx + 1);
	F_.resize(nx + 1);

	X_[0] = x0;
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = x0 + hx * i;
		X_[i] = xnew;
	}
	X_[nx] = xn;


	for(int i = 0; i <= nx; i++)
		F_[i] = e_function(X_[i]);

	swap_vectors(&X_, X);
	swap_vectors(&F_, F);
	X_.clear();
	F_.clear();
	X_.~vector();
	F_.~vector();
}

void create_data(vector<double>* X, vector<double>* Y, Matrix* Z)
{
	vector<double> X_;
	vector<double> Y_;
	Matrix Z_;

	/*number of segment splits*/
	int nx;
	int ny;

	/*begin/end points of X-segment*/
	double x0;
	double xn;

	/*begin/end points of Y-segment*/
	double y0;
	double yn;

	/*steps*/
	double hx;
	double hy;

	/*initial data*/
	nx = 5;
	ny = 5;
	x0 = 0;
	xn = 10;
	y0 = 0;
	yn = 10;
	hx = abs(xn - x0) / double(nx);
	hy = abs(yn - y0) / double(ny);

	X_.resize(nx + 1);
	Y_.resize(ny + 1);
	Z_ = Matrix(ny + 1, nx + 1);

	X_[0] = x0;
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = x0 + hx * i;
		X_[i] = xnew;
	}
	X_[nx] = xn;

	Y_[0] = y0;
	for(int i = 1; i < ny; i++)
	{
		double ynew;
		ynew = y0 + hy * i;
		Y_[i] = ynew;
	}
	Y_[ny] = yn;

	for(int i = 0; i <= ny; i++)
		for(int j = 0; j <= nx; j++)
			Z_(i, j) = e_function(X_[j], Y_[i]);

	swap_vectors(&X_, X);
	swap_vectors(&Y_, Y);
	swap_matrices(&Z_, Z);
	X_.clear();
	Y_.clear();
	X_.~vector();
	Y_.~vector();
	Z_.~Matrix();
}

double e_function(double x, double y)
{
	double z;
	z = x*x*x + y*y*y;

	return z;
}

double e_function(double x)
{
	double f;
	f = x*x;

	return f;
}


/***********************************************/
/*INTERPOLATION SPLINES*/
/***********************************************/

/*----------------------------*/
/*1D Interpolation Splines*/
/*----------------------------*/

/*Linear*/

void Spline1D_linear::reset_fe()
{
	nfex_ = -1;
	hx_ = double();
}

double Spline1D_linear::basis_function(int i, double x)
{
	double value;
	switch(i)
	{
	case 1:
		value = (X_[nfex_ + 1] - x) / hx_;
		break;
	case 2:
		value = (x - X_[nfex_]) / hx_;
		break;
	default:
		break;
	}

	return value;
}

void Spline1D_linear::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);

	display_stlvector(X_);
	cout << endl;
	display_stlvector(F_);
	cout << endl;
}

void Spline1D_linear::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);

	display_stlvector(X_);
	cout << endl;
	display_stlvector(F_);
	cout << endl;

	cout.precision(DISPLAY_PRECISION);
}

void Spline1D_linear::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);

	for(int i = 0; i < nx_; i++)
	{
		ostr << X_[i] << " " << F_[i] << endl;
	}
}

void Spline1D_linear::print(ofstream & ostr, streamsize precision)
{
	ostr << fixed;
	ostr.precision(precision);

	for(int i = 0; i < nx_; i++)
	{
		ostr << X_[i] << " " << F_[i] << endl;
	}
	ostr.precision(DISPLAY_PRECISION);
}

double Spline1D_linear::get_value(double x)
{
	double result = 0.;

	try
	{
		nfex_ = search(x, X_);
		if(nfex_ == -1 )
			throw "Error: point for spline interpolation out of range";
		else
		{
			hx_ = abs(X_[nfex_ + 1] - X_[nfex_]);

			for(int i = 0; i < 2; i++)
				result += F_[nfex_ + i] * basis_function(i + 1, x);

			reset_fe();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	return result;
}

Spline1D_linear Spline1D_linear::get_spline(int nx)
{
	vector<double> X;
	vector<double> F;

	double hx = abs(this->X_[0] - this->X_[nx_ - 1]) / nx;

	X.resize(nx + 1);
	F.resize(nx + 1);

	X[0] = this->X_[0];
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = this->X_[0] + hx * i;
		X[i] = xnew;
	}
	X[nx] = this->X_[nx_ - 1];


	for(int i = 0; i <= nx; i++)
		F[i] = get_value(X[i]);

	Spline1D_linear new_spline = Spline1D_linear(X, F);
	X.clear();
	F.clear();
	X.~vector();
	F.~vector();

	return new_spline;
}

/*Cubic*/

void Spline1D_cubic::calculate_dfx_1()
{
	dfx.reset();

	double h1 = abs(X_[1] - X_[0]);
	double h2 = abs(X_[2] - X_[1]);
	dfx[0] = -((2 * h1 + h2) / (h1*(h1 + h2)))*F_[0]
		+ ((h1 + h2) / (h1*h2))*F_[1]
		- (h1 / ((h1 + h2)*h2))*F_[2];

	double hn_1 = abs(X_[nx_ - 1] - X_[nx_ - 2]);
	double hn_2 = abs(X_[nx_ - 2] - X_[nx_ - 3]);
	dfx[nx_ - 1] = (hn_1 / (hn_2*(hn_2 + hn_1)))*F_[nx_ - 3]
		- ((hn_2 + hn_1) / (hn_1*hn_2))*F_[nx_ - 2]
		+ ((2 * hn_1 + hn_2) / (hn_1*(hn_2 + hn_1)))*F_[nx_ - 1];

	for(int i = 1; i < nx_ - 1; i++)
	{
		double hi = abs(X_[i + 1] - X_[i]);
		double h_i = abs(X_[i] - X_[i - 1]);

		dfx[i] = (-hi / (h_i*(h_i + hi)))*F_[i - 1]
			+ ((hi - h_i) / (h_i*hi))*F_[i]
			+ (h_i / (hi*(h_i + hi)))*F_[i + 1];
	}
}

void Spline1D_cubic::calculate_dfx_2()
{
	A.reset();
	b.reset();
	dfx.reset();

	A(0, 0) = 1.;
	A(nx_ - 1, nx_ - 1) = 1.;

	double h1 = abs(X_[1] - X_[0]);
	double h2 = abs(X_[2] - X_[1]);
	b[0] = -((2 * h1 + h2) / (h1*(h1 + h2)))*F_[0] 
		+ ((h1 + h2) / (h1*h2))*F_[1] 
		- (h1 / ((h1 + h2)*h2))*F_[2];

	double hn_1 = abs(X_[nx_ - 1] - X_[nx_ - 2]);
	double hn_2 = abs(X_[nx_ - 2] - X_[nx_ - 3]);
	b[nx_ - 1] = (hn_1 / (hn_2*(hn_2 + hn_1)))*F_[nx_ - 3] 
		- ((hn_2 + hn_1) / (hn_1*hn_2))*F_[nx_ - 2] 
		+ ((2 * hn_1 + hn_2) / (hn_1*(hn_2 + hn_1)))*F_[nx_ - 1];

	for(int i = 1; i < nx_ - 1; i++)
	{
		double hi = abs(X_[i+1] - X_[i]);
		double h_i = abs(X_[i] - X_[i-1]);

		A(i, i - 1) = 2. / h_i;
		A(i, i) = 4. / h_i + 4. / hi;
		A(i, i + 1) = 2. / hi;

		b[i] = (-6.*F_[i - 1]) / (h_i*h_i)
			+ (6.*F_[i]) / (h_i*h_i) - (6.*F_[i]) / (hi*hi)
			+ (6.*F_[i + 1]) / (hi * hi);
	}
	sol_gauss(A, b, dfx);
}

double Spline1D_cubic::basis_function(int i, double x)
{
	double value;
	switch(i)
	{
	case 1:
		value = 1 - 3.*x*x + 2.*x*x*x;
		break;
	case 2:
		value = x - 2.*x*x + x*x*x;
		break;
	case 3:
		value = 3.*x*x - 2.*x*x*x;
		break;
	case 4:
		value = -x*x + x*x*x;
		break;
	default:
		break;
	}

	return value;
}

double Spline1D_cubic::basis_function_df(int i, double x)
{
	double value;
	switch(i)
	{
	case 1:
		value = -6.*x + 6.*x*x;
		break;
	case 2:
		value = 1. - 4.*x + 3.*x*x;
		break;
	case 3:
		value = 6.*x - 6.*x*x;
		break;
	case 4:
		value = -2.*x + 3.*x*x;
		break;
	default:
		break;
	}

	return value;
}

double Spline1D_cubic::get_value(double x)
{
	double result = 0.;
	vector<double> basis_function_value;
	basis_function_value.resize(4);

	try
	{
		nfex_ = search(x, X_);
		if(nfex_ == -1)
			throw "Error: point for spline interpolation out of range";
		else
		{ 
			/*if enough nodes are set*/
			if(nx_ >= ENOUGH_NODE)
			{
				hx_ = abs(X_[nfex_ + 1] - X_[nfex_]);

				double t = (x - X_[nfex_]) / hx_;

				for(int i = 0; i < 4; i++)
					basis_function_value[i] = basis_function(i + 1, t);

				result += basis_function_value[0] * F_[nfex_];
				result += basis_function_value[2] * F_[nfex_ + 1];
				result += hx_ * (basis_function_value[1] * dfx[nfex_]);
				result += hx_ * (basis_function_value[3] * dfx[nfex_ + 1]);

			}
			/*use linear spline*/
			else
			{
				Spline1D_linear spline = Spline1D_linear(X_, F_);
				result = spline.get_value(x);
			}

			reset_fe();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	basis_function_value.clear();
	basis_function_value.~vector();

	return result;
}

double Spline1D_cubic::get_dfvalue(double x)
{
	double result = 0.;
	vector<double> basis_function_df_value;
	basis_function_df_value.resize(4);

	try
	{
		nfex_ = search(x, X_);
		if(nfex_ == -1)
			throw "Error: point for spline interpolation out of range";
		else
		{
			hx_ = abs(X_[nfex_ + 1] - X_[nfex_]);

			double t = (x - X_[nfex_]) / hx_;

			for(int i = 0; i < 4; i++)
				basis_function_df_value[i] = basis_function_df(i + 1, t);

			result += (basis_function_df_value[0] * F_[nfex_]) / hx_;
			result += (basis_function_df_value[2] * F_[nfex_ + 1]) / hx_;
			result += (basis_function_df_value[1] * dfx[nfex_]);
			result += (basis_function_df_value[3] * dfx[nfex_ + 1]);

			reset_fe();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	basis_function_df_value.clear();
	basis_function_df_value.~vector();

	return result;
}

Spline1D_cubic Spline1D_cubic::get_spline(int nx)
{
	vector<double> X;
	vector<double> F;

	double hx = abs(this->X_[0] - this->X_[nx_ - 1]) / nx;

	X.resize(nx + 1);
	F.resize(nx + 1);

	X[0] = this->X_[0];
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = this->X_[0] + hx * i;
		X[i] = xnew;
	}
	X[nx] = this->X_[nx_ - 1];


	for(int i = 0; i <= nx; i++)
		F[i] = get_value(X[i]);

	Spline1D_cubic new_spline = Spline1D_cubic(X, F);
	X.clear();
	F.clear();
	X.~vector();
	F.~vector();

	return new_spline;
}

Spline1D_cubic Spline1D_cubic::get_dfspline(int nx)
{
	vector<double> X;
	vector<double> F;

	double hx = abs(this->X_[0] - this->X_[nx_ - 1]) / nx;

	X.resize(nx + 1);
	F.resize(nx + 1);

	X[0] = this->X_[0];
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = this->X_[0] + hx * i;
		X[i] = xnew;
	}
	X[nx] = this->X_[nx_ - 1];


	for(int i = 0; i <= nx; i++)
		F[i] = get_dfvalue(X[i]);

	Spline1D_cubic new_spline = Spline1D_cubic(X, F);
	X.clear();
	F.clear();
	X.~vector();
	F.~vector();

	return new_spline;
}


/*----------------------------*/
/*2D Interpolation Splines*/
/*----------------------------*/

/*Linear*/

void Spline2D_linear::reset_fe()
{
	nfex_ = -1;
	nfey_ = -1;
	hx_ = double();
	hy_ = double();
}

int Spline2D_linear::myu_(int i)
{
	return (i - 1) % 2 + 1;
}

int Spline2D_linear::nyu_(int i)
{
	return int(double(i - 1) / 2.) + 1;
}

double Spline2D_linear::temp_function_X(int i, double x)
{
	double value;
	switch(i)
	{
	case 1:
		value = (X_[nfex_ + 1] - x) / hx_;
		break;
	case 2:
		value = (x - X_[nfex_]) / hx_;
		break;
	default:
		break;
	}

	return value;
}

double Spline2D_linear::temp_function_Y(int i, double y)
{
	double value;
	switch(i)
	{
	case 1:
		value = (Y_[nfey_ + 1] - y) / hy_;
		break;
	case 2:
		value = (y - Y_[nfey_]) / hy_;
		break;
	default:
		break;
	}

	return value;
}

double Spline2D_linear::basis_function(int i, double x, double y)
{
	double value;
	int myu = myu_(i);
	int nyu = nyu_(i);
	value = temp_function_X(myu, x) * temp_function_Y(nyu, y);

	return value;
}

void Spline2D_linear::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);

	display_stlvector(X_);
	/*cout << endl;*/
	display_stlvector(Y_);
	/*cout << endl;*/
	Z_.display();
}

void Spline2D_linear::display(streamsize precision)
{
	cout << fixed;
	cout.precision(precision);

	display_stlvector(X_);
	cout << endl;
	display_stlvector(Y_);
	cout << endl;
	Z_.display();

	cout.precision(DISPLAY_PRECISION);
}

void Spline2D_linear::print(ofstream & ostr)
{
	ostr << fixed;
	ostr.precision(DISPLAY_PRECISION);
	
	ostr << " ";
	for(int i = 0; i < nx_; i++)
		ostr << X_[i] << " ";
	ostr << endl;

	for(int i = 0; i < ny_; i++)
	{
		ostr << Y_[i] << " ";
		for(int j = 0; j < nx_; j++)
			ostr << Z_(i, j) << " ";
		ostr << endl;
	}
}

void Spline2D_linear::print(ofstream & ostr, streamsize precision)
{
	ostr << fixed;
	ostr.precision(precision);

	ostr << " ";
	for(int i = 0; i < nx_; i++)
		ostr << X_[i] << " ";
	ostr << endl;

	for(int i = 0; i < ny_; i++)
	{
		ostr << Y_[i] << " ";
		for(int j = 0; j < nx_; j++)
			ostr << Z_(i, j) << " ";
		ostr << endl;
	}

	ostr.precision(DISPLAY_PRECISION);
}

double Spline2D_linear::get_value(double x, double y)
{
	double result = 0.;
	vector<double> basis_function_value;
	basis_function_value.resize(4);

	try
	{
		nfex_ = search(x, X_);
		nfey_ = search(y, Y_);

		if(nfex_ == -1 || nfey_ == -1)
			throw "Error: point for spline interpolation out of range";
		else
		{
			hx_ = abs(X_[nfex_ + 1] - X_[nfex_]);
			hy_ = abs(Y_[nfey_ + 1] - Y_[nfey_]);

			for(int i = 0; i < 4; i++)
				basis_function_value[i] = basis_function(i + 1, x, y);

			result += Z_(nfey_, nfex_) * basis_function_value[0];
			result += Z_(nfey_, nfex_ + 1) * basis_function_value[1];
			result += Z_(nfey_ + 1, nfex_) * basis_function_value[2];
			result += Z_(nfey_ + 1, nfex_ + 1) * basis_function_value[3];
			
			reset_fe();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	return result;
}

Spline2D_linear Spline2D_linear::get_spline(int nx, int ny)
{
	vector<double> X;
	vector<double> Y;
	Matrix Z;

	double hx = abs(this->X_[0] - this->X_[nx_ - 1]) / nx;
	double hy = abs(this->Y_[0] - this->Y_[ny_ - 1]) / ny;

	X.resize(nx + 1);
	Y.resize(ny + 1);
	Z = Matrix(ny + 1, nx + 1);

	X[0] = this->X_[0];
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = this->X_[0] + hx * i;
		X[i] = xnew;
	}
	X[nx] = this->X_[nx_ - 1];

	Y[0] = this->Y_[0];
	for(int i = 1; i < ny; i++)
	{
		double ynew;
		ynew = this->Y_[0] + hy * i;
		Y[i] = ynew;
	}
	Y[ny] = this->Y_[ny_ - 1];

	for(int i = 0; i <= ny; i++)
		for(int j = 0; j <= nx; j++)
			Z(i, j) = get_value(X[j], Y[i]);

	Spline2D_linear new_spline = Spline2D_linear(X, Y, Z);
	X.clear();
	Y.clear();
	X.~vector();
	Y.~vector();
	Z.~Matrix();

	return new_spline;
}

/*Cubic*/

void Spline2D_cubic::calculate_x_splines()
{
	for(int i = 0; i < ny_; i++)
	{
		spline_X[i] = Spline1D_cubic(X_, Z_.get_row(i));
	}
}

void Spline2D_cubic::calculate_y_splines()
{
	for(int i = 0; i < nx_; i++)
	{
		spline_Y[i] = Spline1D_cubic(Y_, Z_.get_col(i));
	}
}

void Spline2D_cubic::calculate_dx_splines()
{
	for(int i = 0; i < ny_; i++)
	{
		for(int j = 0; j < nx_; j++)
		{
			dX_(i, j) = spline_X[i].get_dfvalue(X_[j]);
		}
	}
}

void Spline2D_cubic::calculate_dy_splines()
{
	Matrix dY = Matrix(nx_, ny_);

	for(int i = 0; i < nx_; i++)
	{
		for(int j = 0; j < ny_; j++)
		{
			dY(i, j) = spline_Y[i].get_dfvalue(Y_[j]);
		}
	}

	dY_ = dY.transpose();
	dY.~Matrix();
}

void Spline2D_cubic::calculate_dxy_splines()
{
	Matrix dXY = Matrix(nx_, ny_);

	for(int i = 0; i < nx_; i++)
	{
		spline_dX[i] = Spline1D_cubic(Y_, dX_.get_col(i));
	}

	for(int i = 0; i < nx_; i++)
	{
		for(int j = 0; j < ny_; j++)
		{
			dXY(i, j) = spline_dX[i].get_dfvalue(Y_[j]);
		}
	}

	dXY_ = dXY.transpose();
	dXY.~Matrix();
}

int Spline2D_cubic::myu_(int i)
{
	return 2 * (int((i - 1) / 4.) % 2) + ((i - 1) % 2) + 1;
}

int Spline2D_cubic::nyu_(int i)
{
	return 2 * int((i - 1) / 8.) + (int((i - 1) / 2.) % 2) + 1;
}

double Spline2D_cubic::temp_function(int i, double x)
{
	double value;
	switch(i)
	{
	case 1:
		value = 1 - 3.*x*x + 2.*x*x*x;
		break;
	case 2:
		value = x - 2.*x*x + x * x*x;
		break;
	case 3:
		value = 3.*x*x - 2.*x*x*x;
		break;
	case 4:
		value = -x * x + x * x*x;
		break;
	default:
		break;
	}
	return value;
}

double Spline2D_cubic::basis_function(int i, double x, double y)
{
	double value;
	int myu = myu_(i);
	int nyu = nyu_(i);
	value = temp_function(myu, x) * temp_function(nyu, y);

	return value;
}

double Spline2D_cubic::get_value(double x, double y)
{
	double result = 0.;
	vector<double> basis_function_value;
	basis_function_value.resize(16);

	try
	{
		nfex_ = search(x, X_);
		nfey_ = search(y, Y_);

		if(nfex_ == -1 || nfey_ == -1)
			throw "Error: point for spline interpolation out of range";
		else
		{
			if(nx_ >= ENOUGH_NODE && ny_ >= ENOUGH_NODE)
			{
				hx_ = abs(X_[nfex_ + 1] - X_[nfex_]);
				hy_ = abs(Y_[nfey_ + 1] - Y_[nfey_]);

				double t = (x - X_[nfex_]) / hx_;
				double u = (y - Y_[nfey_]) / hy_;

				for(int i = 0; i < 16; i++)
					basis_function_value[i] = basis_function(i + 1, t, u);

				result += Z_(nfey_, nfex_) * basis_function_value[0];
				result += Z_(nfey_, nfex_ + 1) * basis_function_value[4];
				result += Z_(nfey_ + 1, nfex_) * basis_function_value[8];
				result += Z_(nfey_ + 1, nfex_ + 1) * basis_function_value[12];

				result += hx_ * (dX_(nfey_, nfex_) * basis_function_value[1]);
				result += hx_ * (dX_(nfey_, nfex_ + 1) * basis_function_value[5]);
				result += hx_ * (dX_(nfey_ + 1, nfex_) * basis_function_value[9]);
				result += hx_ * (dX_(nfey_ + 1, nfex_ + 1) * basis_function_value[13]);

				result += hy_ * (dY_(nfey_, nfex_) * basis_function_value[2]);
				result += hy_ * (dY_(nfey_, nfex_ + 1) * basis_function_value[6]);
				result += hy_ * (dY_(nfey_ + 1, nfex_) * basis_function_value[10]);
				result += hy_ * (dY_(nfey_ + 1, nfex_ + 1) * basis_function_value[14]);

				result += (dXY_(nfey_, nfex_) * basis_function_value[3]);
				result += (dXY_(nfey_, nfex_ + 1) * basis_function_value[7]);
				result += (dXY_(nfey_ + 1, nfex_) * basis_function_value[11]);
				result += (dXY_(nfey_ + 1, nfex_ + 1) * basis_function_value[15]);
			}
			/*use linear spline*/
			else
			{
				Spline2D_linear spline = Spline2D_linear(X_, Y_, Z_);
				result = spline.get_value(x, y);
			}

			reset_fe();
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}

	basis_function_value.~vector();
	return result;
}

Spline2D_cubic Spline2D_cubic::get_spline(int nx, int ny)
{
	vector<double> X;
	vector<double> Y;
	Matrix Z;

	double hx = abs(this->X_[0] - this->X_[nx_ - 1]) / nx;
	double hy = abs(this->Y_[0] - this->Y_[ny_ - 1]) / ny;

	X.resize(nx + 1);
	Y.resize(ny + 1);
	Z = Matrix(ny + 1, nx + 1);

	X[0] = this->X_[0];
	for(int i = 1; i < nx; i++)
	{
		double xnew;
		xnew = this->X_[0] + hx * i;
		X[i] = xnew;
	}
	X[nx] = this->X_[nx_ - 1];

	Y[0] = this->Y_[0];
	for(int i = 1; i < ny; i++)
	{
		double ynew;
		ynew = this->Y_[0] + hy * i;
		Y[i] = ynew;
	}
	Y[ny] = this->Y_[ny_ - 1];

	for(int i = 0; i <= ny; i++)
		for(int j = 0; j <= nx; j++)
			Z(i, j) = get_value(X[j], Y[i]);

	Spline2D_cubic new_spline = Spline2D_cubic(X, Y, Z);
	X.clear();
	Y.clear();
	X.~vector();
	Y.~vector();
	Z.~Matrix();

	return new_spline;
}



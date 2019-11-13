#include"common.h"

double COMPARE_PRECISION = 1e-12;

void set_compare_precision(double precision)
{
	COMPARE_PRECISION = precision;
}

double get_current_compare_precision()
{
	return COMPARE_PRECISION;
}

void reset_compare_precision()
{
	COMPARE_PRECISION = CONST_COMPARE_PRECISION;
}

vector<double> array_to_vector(int size, double* arr)
{
	vector<double> vec = vector<double>(size);
	for(int i = 0; i < size; i++)
		vec[i] = arr[i];

	return vec;
}

void display_stlvector(vector<double> vec)
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

void display_stlvector(vector<int> vec)
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

void display_stlvector(vector<double> vec, int precision)
{
	cout << fixed;
	cout.precision(precision);
	for(int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
	cout.precision(DISPLAY_PRECISION);
}

void display_stlset(set<double> st)
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(set<double>::iterator it = st.begin(); it != st.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void display_stlset(set<int> st)
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	for(set<int>::iterator it = st.begin(); it != st.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void display_stlset(set<double> st, int precision)
{
	cout << fixed;
	cout.precision(precision);
	for(set<double>::iterator it = st.begin(); it != st.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout.precision(DISPLAY_PRECISION);
}

int search(double val, vector<double> vec)
{
	if(val > vec[vec.size() - 1] || val < vec[0])
		return -1;

	for(int i = 0; i < vec.size() - 1; i++)
		if(val >= vec[i] && val <= vec[i + 1])
			return i;

	return -1;
}

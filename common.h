#pragma once
#define _USE_MATH_DEFINES
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <math.h>
#include <cmath>

using namespace std;

/*const for compare with null*/
const double almost_zero = 1e-16;
/*current precision of floating-point numbers compare*/
extern double COMPARE_PRECISION;
/*const precision of floating-point numbers compare*/
const double CONST_COMPARE_PRECISION = 1e-12;
/*precision of floating-point numpers display*/
const streamsize DISPLAY_PRECISION = cout.precision();
/*conversion constant radian to degree*/
const double rad_to_deg = 180. / M_PI;
/*conversion constant degree to radian*/
const double deg_to_rad = M_PI / 180.;

/*number of node for edge*/
#define EDGE_SIZE	2
/*number of node for face*/
#define FACE_SIZE	4
/*number of node for fe*/
#define FE_SIZE		8

/*set new precision of floating-point numbers compare*/
void set_compare_precision(double precision);
/*get current precision of floating-point numbers compare*/
double get_current_compare_precision();
/*set typical precision of floating-point numbers compare*/
void reset_compare_precision();

/*create vector<double> based on double array*/
vector<double> array_to_vector(int size, double* arr);
/*display vector<double>*/
void display_stlvector(vector<double> vec);
void display_stlvector(vector<int> vec);
void display_stlvector(vector<double> vec, int precision);
/*display vector<double>*/
void display_stlset(set<double> st);
void display_stlset(set<int> st);
void display_stlset(set<double> st, int precision);
/*search segment in given vector which contains given value*/
/*if out of range returns -1*/
int search(double val, vector<double> vec);

template <typename T>
void string_to_number(string s, T &n)
{
	stringstream str;
	str << s;
	str >> n;
}
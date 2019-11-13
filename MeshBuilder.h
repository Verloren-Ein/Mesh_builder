#pragma once
#include "common.h"
#include "Mesh.h"
#include "Spline.h"

/*-------------------*/
/*INPUT MESH BUILDER */
/*-------------------*/

/*information about layers number and layers boundary*/
#define default_file_enviroment "environment.txt"
/*information about anomalies number and anomalies boundary*/
#define default_file_anomalies "anomalies.txt"
/*information about segment fragmentation*/
#define default_file_fragmentation "fragmentation.txt"
/*information about the number of calculation formulas for layers and anomalies*/
#define default_file_formula "formulas.txt"

/*-------------------*/
/*OUTPUT MESH BUILDER*/
/*-------------------*/

#define default_file_fes "fes.txt"
#define default_file_nodes "nodes.txt"
#define default_file_firstBCs "firstBCs.txt"

/*layer boundary description*/
class Layer_boundary
{
public:
	/*size of initial mesh*/
	int nx_;
	int ny_;

	vector<double> X_;
	vector<double> Y_;
	Matrix Z_;

	Layer_boundary()
		:nx_()
		, ny_()
	{
		X_.clear();
		Y_.clear();
		Z_.clear();
	}
	Layer_boundary(vector<double> X, vector<double> Y, Matrix Z)
		:nx_(int(X.size()))
		, ny_(int(Y.size()))
	{
		X_ = X;
		Y_ = Y;
		Z_ = Z;
	}
	~Layer_boundary()
	{
		X_.clear();
		Y_.clear();
		X_.~vector();
		Y_.~vector();
		Z_.~Matrix();
	}
	void display();
};

/*anomaly location*/
class Anomaly
{
public:
	/*number of layer which contains this anomaly*/
	int n_layer;

	/*anomaly`s boundary*/
	double x0;
	double xn;
	double y0;
	double yn;

	Anomaly()
		:n_layer()
		, x0()
		, xn()
		, y0()
		, yn()
	{}

	Anomaly(int n_layer, double x0, double xn, double y0, double yn)
		:n_layer(n_layer)
		, x0(x0)
		, xn(xn)
		, y0(y0)
		, yn(yn)
	{}

	void display();
};

/*information about fragmentations in each segment*/
class Fragmentation_info
{
public:
	/*number of subsegments in segment*/
	int n;
	/*discharge factor*/
	double coeff;
	/*discharge direction*/
	int sign;

	Fragmentation_info()
		:n()
		, coeff()
		, sign()
	{}
	Fragmentation_info(int n, double coeff)
		:n(n)
		,coeff(fabs(coeff))
	{
		if(coeff < 0)
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
	}

	void display();
};

class MeshBuilder
{
private:
	/*LAYER INFORMATION*/
	/*number of layers in enviroment*/
	int n_layers;
	/*layers boundary*/
	vector<Layer_boundary> layer_boundary;
	/*splines computing from layer_boundary*/
	vector<Spline2D_cubic> layer_boundary_spl;

	/*ANOMALY INFORMATION*/
	/*number of anomalies*/
	int n_anomalies;
	/*anomalies*/
	vector<Anomaly> anomalies;

	/*FRAGMENTATION INFORMATION*/
	vector<Fragmentation_info> X_fragments;
	vector<Fragmentation_info> Y_fragments;
	vector<Fragmentation_info> Z_fragments;

	/*FORMULA INFORMATION*/
	vector<int> formula_layer;
	vector<int> formula_anomaly;

	/*MESH INFORMATION*/
	/*primitive mesh*/
	set<double> X_primitive;
	set<double> Y_primitive;

	/*splitted x/y - segments*/
	vector<double> X_splitted;
	vector<double> Y_splitted;

	/*number of nodes*/
	int n_nodes;
	/*number of fes*/
	int n_fes;
	/*number of firstBC*/
	int n_firstBCs;
	/*mesh nodes*/
	vector<Node3D> nodes;
	/*mesh fes*/
	vector<FE> fes;
	/*mesh first boundary condition*/
	vector<FirstBC> firstBCs;

	/*splittig segment to subsegments*/
	void split_segment(double start, double end, Fragmentation_info fragmentation_info, vector<double> &splitted_segment);
	/*checks point for belonging to an anomaly*/
	/*returns anomaly number or -1*/
	int is_anomaly(int n_layer, Point2D midpoint);

	/*debug print*/
	void print_layers();
	void print_anomalies();
	void print_fragmentation_info();

public:
	/*finite element mesh construction*/
	void build_mesh();

public:
	MeshBuilder()
		:n_layers(-1)
	{
		layer_boundary.clear();
		layer_boundary_spl.clear();
		anomalies.clear();
		X_fragments.clear();
		Y_fragments.clear();
		Z_fragments.clear();
		formula_layer.clear();
		formula_anomaly.clear();
		X_primitive.clear();
		Y_primitive.clear();
		X_splitted.clear();
		Y_splitted.clear();
		nodes.clear();
		fes.clear();
		firstBCs.clear();
	}
	~MeshBuilder()
	{
		layer_boundary.~vector();
		layer_boundary_spl.~vector();
		anomalies.~vector();
		X_fragments.~vector();
		Y_fragments.~vector();
		Z_fragments.~vector();
		formula_layer.~vector();
		formula_anomaly.~vector();
		X_splitted.~vector();
		Y_splitted.~vector();
		nodes.~vector();
		fes.~vector();
		firstBCs.~vector();
	}

	/*use default input file*/
	void set_layer_boundary();
	/*use custom input file*/
	void set_layer_boundary(const char *file_name);

	/*use default input file*/
	void set_anomalies();
	/*use custom input file*/
	void set_anomalies(const char *file_name);

	/*use default input file*/
	void set_fragmentation();
	/*use custom input file*/
	void set_fragmentation(const char *file_name);

	/*use default input file*/
	void set_formula();
	/*use custom input file*/
	void set_formula(const char *file_name);

	/*use default output file*/
	void get_mesh();
	/*use custom output file*/
	void get_mesh(const char *file_name_nodes, const char *file_name_fes, const char *file_name_firstBCs);
	/*use use output transfer via method parameters*/
	void get_mesh(vector<Node3D> &nodes, vector<FE> &fes, vector<FirstBC> &firstBCs);

};


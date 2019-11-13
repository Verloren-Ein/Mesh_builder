#pragma once
#include "common.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"

/*distance between two points*/
double points_distance(Point2D A, Point2D B);
double points_distance(Point3D A, Point3D B);

/*swap vectors*/
void swap_vectors(Vector* A, Vector* B);
void swap_vectors(vector<double>* A, vector<double>* B);

/*dot product*/
double dot_product(Vector A, Vector B);

/*Euclidean vector norm*/
double norm_euclidean(Vector A);


/*3D vector`s functions*/
/*cross product*/
Vector3D cross_product(Vector3D A, Vector3D B);

/*vector coordinates given by coordinates of start point and end point*/
Vector3D vector_coordinates(Point3D start, Point3D end);

/*vectors orthogonality check; returns true if orthogonal*/
bool orthogonality_check(Vector3D A, Vector3D B);

/*vectors collinearity check; returns true if collinear*/
bool collinearity_check(Vector3D A, Vector3D B);

/*angle between vectors. [0, pi]*/
double vectors_angle_rad(Vector3D A, Vector3D B);
double vectors_angle_deg(Vector3D A, Vector3D B);

/*swap matrices*/
void swap_matrices(Matrix *A, Matrix *B);

/*strike out given row and col and returns new matrix*/
Matrix strike_out(Matrix matrix, unsigned iRow, unsigned iCol);

/*multiply vector-row by vector-col: scalar*/
double multiply_vectorRow_by_vectorCol(Vector vectorRow, Vector vectorCol);
/*multiply vector-col by vector-row: matrix nxn*/
Matrix multiply_vectorCol_by_vectorRow(Vector vectorCol, Vector vectorRow);
/*multiply matrix by vector: vector nxm * m = n*/
Vector multiply_matrix_by_vector(Matrix matrix, Vector vector);
/*multiply matrix by matrix: matrix nxm*mxl = nxl*/
Matrix multiply_matrix_by_matrix(Matrix matrix1, Matrix matrix2);


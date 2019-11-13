#include "common.h"
#include "functions.h"

double points_distance(Point2D A, Point2D B)
{
	double result = 0.;
	for(int i = 0; i < 2; i++)
	{
		result += (B[i] - A[i])*(B[i] - A[i]);
	}
	return sqrt(result);
}

double points_distance(Point3D A, Point3D B)
{
	double result = 0.;
	for(int i = 0; i < 3; i++)
	{
		result += (B[i] - A[i])*(B[i] - A[i]);
	}
	return sqrt(result);
}

void swap_vectors(Vector * A, Vector * B)
{
	Vector tmp = *A;
	*A = *B;
	*B = tmp;
}

void swap_vectors(vector<double>* A, vector<double>* B)
{
	vector<double> tmp = *A;
	*A = *B;
	*B = tmp;
}

double dot_product(Vector A, Vector B)
{
	try
	{
		if(A.size() == B.size())
		{
			double dot_prod = 0.;
			for(int i = 0; i < A.size(); i++)
			{
				dot_prod += A[i] * B[i];
			}
			return dot_prod;
		}
		else
			throw "Error: attempt to calculate the dot product vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return false;
}

double norm_euclidean(Vector A)
{
	return sqrt(dot_product(A, A));
}

Vector3D cross_product(Vector3D A, Vector3D B)
{
	Vector3D cross_product;
	cross_product[0] = A[1] * B[2] - A[2] * B[1];
	cross_product[1] = A[2] * B[0] - A[0] * B[2];
	cross_product[2] = A[0] * B[1] - A[1] * B[0];

	return cross_product;
}

Vector3D vector_coordinates(Point3D start, Point3D end)
{
	return Vector3D(start - end);
}

bool orthogonality_check(Vector3D A, Vector3D B)
{
	double precision = get_current_compare_precision();
	if(abs(dot_product(A, B)) < precision)
	{
		return true;
	}
	return false;
}

bool collinearity_check(Vector3D A, Vector3D B)
{
	if(cross_product(A, B) == Vector3D())
	{
		return true;
	}
	return false;
}

double vectors_angle_rad(Vector3D A, Vector3D B)
{
	double cosAB = dot_product(A, B) / (norm_euclidean(A) * norm_euclidean(B));
	return acos(cosAB);
}

double vectors_angle_deg(Vector3D A, Vector3D B)
{
	double cosAB = dot_product(A, B) / (norm_euclidean(A) * norm_euclidean(B));
	return acos(cosAB) * rad_to_deg;
}

void swap_matrices(Matrix * A, Matrix * B)
{
	Matrix tmp = *A;
	*A = *B;
	*B = tmp;
}

Matrix strike_out(Matrix matrix, unsigned row, unsigned col)
{
	Matrix new_matrix;
	try
	{
		if(row >= matrix.rows() || col >= matrix.cols())
			throw "Error: matrix subscript out of range";
		else
		{
			new_matrix = Matrix(matrix.rows() - 1, matrix.cols() - 1);
			for(unsigned i = 0, new_i = 0; i < matrix.rows(); i++)
			{
				if(i != row)
				{
					for(unsigned j = 0, new_j = 0; j < matrix.cols(); j++)
					{
						if(j != col)
						{
							new_matrix(new_i, new_j) = matrix(i, j);
							new_j++;
						}
					}
					new_i++;
				}
			}
		}
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return new_matrix;
}

double multiply_vectorRow_by_vectorCol(Vector vectorRow, Vector vectorCol)
{
	return dot_product(vectorRow, vectorCol);
}

Matrix multiply_vectorCol_by_vectorRow(Vector vectorCol, Vector vectorRow)
{
	Matrix matrix = Matrix(vectorCol.size());
	try
	{
		if(vectorCol.size() == vectorRow.size())
		{
			for(int i = 0; i < vectorCol.size(); i++)
			{
				for(int j = 0; j < vectorCol.size(); j++)
				{
					matrix(i, j) = vectorCol[i] * vectorRow[j];
				}
			}
		}
		else
			throw "Error: attempt to multiply the vectors of different sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return matrix;
}

Vector multiply_matrix_by_vector(Matrix matrix, Vector vector)
{
	Vector result_vector = Vector(matrix.rows());
	try
	{
		if(vector.size() == matrix.cols())
		{
			for(unsigned i = 0; i < matrix.rows(); i++)
			{
				for(int j = 0; j < vector.size(); j++)
				{
					result_vector[i] += matrix(i, j) * vector[j];
				}
			}
		}
		else
			throw "Error: attempt to multiply matrix and vector of inappropriate sizes";
	}
	catch(char *str)
	{
		cerr << str << endl;
	}
	return result_vector;
}

Matrix multiply_matrix_by_matrix(Matrix matrix1, Matrix matrix2)
{
	Matrix result_matrix;
	result_matrix = matrix1 * matrix2;
	return result_matrix;
}

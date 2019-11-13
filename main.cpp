#include "common.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Spline.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "functions.h"

void test_point2D()
{
	/*-----TESTING Point2D`S METHODS-----*/

	/*create and display default (double) points*/
	cout << ">>>create and display points" << endl;
	Point2D point;
	Point2D point2 = Point2D(14.567327832, 15.0);
	point.display();
	point.display(15);
	point2.display();
	point2.display(15);
	cout << endl;

	/*output points in test_file.txt*/
	cout << ">>>output points in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	point.print(ostr);
	point.print(ostr, 15);
	point2.print(ostr);
	point2.print(ostr, 15);
	ostr.close();

	/*arithmetic operator overloading*/
	cout << ">>>arithmetic operator overloading" << endl;
	Point2D point3 = Point2D(1, 2);
	Point2D point4 = Point2D(2, 1);
	int int_const = 10;
	double double_const = 20.;
	Point2D result_point;
	cout << ">>binary summation" << endl;
	cout << "---point + point" << endl;
	result_point = point3 + point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point + int" << endl;
	result_point = int_const + point3;
	point3.display();
	cout << int_const << endl;
	result_point.display();
	result_point.reset();
	cout << "---point + double" << endl;
	result_point = point3 + double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>binary subtraction" << endl;
	cout << "---point - point" << endl;
	result_point = point3 - point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point - arg" << endl;
	result_point = point3 - double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>binary multiplication" << endl;
	cout << "---point * point" << endl;
	result_point = point3 * point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point * arg" << endl;
	result_point = point3 * double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>binary division" << endl;
	cout << "---point / point" << endl;
	result_point = point3 / point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point / arg" << endl;
	result_point = point3 / double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>unary summation" << endl;
	cout << "---point + point" << endl;
	result_point = Point2D(1, 1);
	result_point.display();
	point3.display();
	result_point += point3;
	result_point.display();
	result_point = Point2D(1, 1);
	cout << "---point + int" << endl;
	result_point.display();
	cout << int_const << endl;
	result_point += int_const;
	result_point.display();
	result_point = Point2D(1, 1);
	cout << "---point + double" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point += double_const;
	result_point.display();
	result_point = Point2D(1, 1);

	cout << ">>unary subtraction" << endl;
	cout << "---point - point" << endl;
	result_point.display();
	point3.display();
	result_point -= point3;
	result_point.display();
	result_point = Point2D(1, 1);
	cout << "---point - arg" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point -= double_const;
	result_point.display();
	result_point = Point2D(1, 1);

	cout << ">>unary multiplication" << endl;
	cout << "---point * point" << endl;
	result_point.display();
	point3.display();
	result_point *= point3;
	result_point.display();
	result_point = Point2D(1, 1);
	cout << "---point * arg" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point *= double_const;
	result_point.display();
	result_point = Point2D(1, 1);

	cout << ">>unary division" << endl;
	cout << "---point / point" << endl;
	result_point.display();
	point3.display();
	result_point /= point3;
	result_point.display();
	result_point = Point2D(1, 1);
	cout << "---point / arg" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point /= double_const;
	result_point.display();
	result_point = Point2D(1, 1);

	cout << ">>unari +/-" << endl;
	result_point = +point3;
	result_point.display();
	result_point = -point3;
	result_point.display();

	/*compare operator overloading*/
	cout << ">>>compare operator overloading" << endl;
	cout << ">>equality" << endl;
	point3 = Point2D(2.2, 3.3);
	point4 = Point2D(2.2, 3.3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 == point4) << endl;
	point3 = Point2D(2.222221, 3.333331);
	point4 = Point2D(2.222222, 3.333333);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 == point4) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 == point4) << endl;

	reset_compare_precision();
	cout << ">>inequality" << endl;
	point3 = Point2D(2.2, 3.3);
	point4 = Point2D(2.1, 3.3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 != point4) << endl;
	point3 = Point2D(2.222221, 3.333331);
	point4 = Point2D(2.222222, 3.333333);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 != point4) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 != point4) << endl;

	/*index access operator overloading*/
	cout << ">>>index access operator overloading" << endl;
	point3 = Point2D(1, 2);
	point3.display();
	cout << point3[0] << " " << point3[1] /*<< point3[2] /*exception*/ << endl;

	point3[0] = 2;
	point3[1] = 1;
	//point3[2] = 0; //exception
	point3.display();

}

void test_point3D()
{
	/*-----TESTING Point3D`S METHODS-----*/
	/*create and display default (double) points*/
	cout << ">>>create and display points" << endl;
	Point3D point;
	Point3D point2 = Point3D(12.345678910, 23.45678910, 1);
	point.display();
	point.display(15);
	point2.display();
	point2.display(15);
	cout << endl;

	/*output points in test_file.txt*/
	cout << ">>>output points in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	point.print(ostr);
	point.print(ostr, 15);
	point2.print(ostr);
	point2.print(ostr, 15);
	ostr.close();

	/*arithmetic operator overloading*/
	cout << ">>>arithmetic operator overloading" << endl;
	Point3D point3 = Point3D(1, 2, 0);
	Point3D point4 = Point3D(2, 1, 5);
	int int_const = 10;
	double double_const = 20.;
	Point3D result_point;
	cout << ">>binary summation" << endl;
	cout << "---point + point" << endl;
	result_point = point3 + point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point + int" << endl;
	result_point = int_const + point3;
	point3.display();
	cout << int_const << endl;
	result_point.display();
	result_point.reset();
	cout << "---point + double" << endl;
	result_point = point3 + double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>binary subtraction" << endl;
	cout << "---point - point" << endl;
	result_point = point3 - point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point - arg" << endl;
	result_point = point3 - double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>binary multiplication" << endl;
	cout << "---point * point" << endl;
	result_point = point3 * point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point * arg" << endl;
	result_point = point3 * double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>binary division" << endl;
	cout << "---point / point" << endl;
	result_point = point3 / point4;
	point3.display();
	point4.display();
	result_point.display();
	result_point.reset();
	cout << "---point / arg" << endl;
	result_point = point3 / double_const;
	point3.display();
	cout << double_const << endl;
	result_point.display();
	result_point.reset();

	cout << ">>unary summation" << endl;
	cout << "---point + point" << endl;
	result_point = Point3D(1, 1, 1);
	result_point.display();
	point3.display();
	result_point += point3;
	result_point.display();
	result_point = Point3D(1, 1, 1);
	cout << "---point + int" << endl;
	result_point.display();
	cout << int_const << endl;
	result_point += int_const;
	result_point.display();
	result_point = Point3D(1, 1, 1);
	cout << "---point + double" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point += double_const;
	result_point.display();
	result_point = Point3D(1, 1, 1);

	cout << ">>unary subtraction" << endl;
	cout << "---point - point" << endl;
	result_point.display();
	point3.display();
	result_point -= point3;
	result_point.display();
	result_point = Point3D(1, 1, 1);
	cout << "---point - arg" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point -= double_const;
	result_point.display();
	result_point = Point3D(1, 1, 1);

	cout << ">>unary multiplication" << endl;
	cout << "---point * point" << endl;
	result_point.display();
	point3.display();
	result_point *= point3;
	result_point.display();
	result_point = Point3D(1, 1, 1);
	cout << "---point * arg" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point *= double_const;
	result_point.display();
	result_point = Point3D(1, 1, 1);

	cout << ">>unary division" << endl;
	cout << "---point / point" << endl;
	result_point.display();
	point3.display();
	result_point /= point3;
	result_point.display();
	result_point = Point3D(1, 1, 1);
	cout << "---point / arg" << endl;
	result_point.display();
	cout << double_const << endl;
	result_point /= double_const;
	result_point.display();
	result_point = Point3D(1, 1, 1);

	cout << ">>unari +/-" << endl;
	result_point = +point3;
	result_point.display();
	result_point = -point3;
	result_point.display();

	/*compare operator overloading*/
	cout << ">>>compare operator overloading" << endl;
	cout << ">>equality" << endl;
	point3 = Point3D(2.2, 3.3, 4.4);
	point4 = Point3D(2.2, 3.3, 4.4);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 == point4) << endl;
	point3 = Point3D(2.222221, 3.333331, 4.444441);
	point4 = Point3D(2.222222, 3.333333, 4.444441);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 == point4) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 == point4) << endl;

	reset_compare_precision();
	cout << ">>inequality" << endl;
	point3 = Point3D(2.2, 3.3, 4.4);
	point4 = Point3D(2.1, 3.3, 4.1);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 != point4) << endl;
	point3 = Point3D(2.222221, 3.333331, 4.444441);
	point4 = Point3D(2.222222, 3.333333, 4.444444);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 != point4) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	point3.display();
	point4.display();
	cout << (point3 != point4) << endl;

	/*index access operator overloading*/
	cout << ">>>index access operator overloading" << endl;
	point3 = Point3D(1, 2, 3);
	point3.display();
	cout << point3[0] << " " << point3[1] << " " << point3[2] << endl;

	point3[0] = 2;
	point3[1] = 1;
	point3[2] = 0;
	point3.display();
}

void test_vector()
{
	/*-----TESTING Vector`S METHODS-----*/
	double test_array[4] = {1, 2, 3, 4};
	double test_array2[4] = {10, 20, 30, 40};

	/*create and display vectors*/
	cout << ">>>create and display vectors" << endl;
	Vector vec0;
	Vector vec1 = Vector(4);
	Vector vec2 = Vector(array_to_vector(4, test_array));
	Vector vec3 = Vector(4, 10);
	cout << vec0.size() << endl;
	vec0.display();
	cout << vec1.size() << endl;
	vec1.display();
	cout << vec2.size() << endl;
	vec2.display();
	vec2.display(15);
	cout << vec3.size() << endl;
	vec3.display();
	cout << endl;

	/*output points in test_file.txt*/
	cout << ">>>output points in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	vec0.print(ostr);
	vec1.print(ostr);
	vec2.print(ostr);
	vec3.print(ostr);
	vec3.print(ostr, 15);
	ostr.close();

	/*arithmetic operator overloading*/
	vec3 = Vector(array_to_vector(4, test_array2));
	cout << ">>>arithmetic operator overloading" << endl;
	int int_const = 10;
	double double_const = 20.;
	Vector result_vec;
	cout << ">>binary summation" << endl;
	cout << "---vector + vector" << endl;
	result_vec = vec2 + vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector + int" << endl;
	result_vec = int_const + vec2;
	vec2.display();
	cout << int_const << endl;
	result_vec.display();
	result_vec.reset();
	cout << "---vector + double" << endl;
	result_vec = vec2 + double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();

	cout << ">>binary subtraction" << endl;
	cout << "---vector - vector" << endl;
	result_vec = vec2 - vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector - arg" << endl;
	result_vec = vec2 - double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();

	cout << ">>binary multiplication" << endl;
	cout << "---vector * vector" << endl;
	result_vec = vec2 * vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector * arg" << endl;
	result_vec = vec2 * double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();

	cout << ">>binary division" << endl;
	cout << "---vector / vector" << endl;
	result_vec = vec2 / vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector / arg" << endl;
	result_vec = vec2 / double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();
	cout << endl;

	cout << ">>unary summation" << endl;
	cout << "---vector + vector" << endl;
	result_vec.reset();
	result_vec.display();
	vec2.display();
	result_vec += vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector + int" << endl;
	result_vec.display();
	cout << int_const << endl;
	result_vec += int_const;
	result_vec.display();
	result_vec.reset();
	cout << "---vector + double" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec += double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unary subtraction" << endl;
	cout << "---vector - vector" << endl;
	result_vec.display();
	vec2.display();
	result_vec -= vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector - arg" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec -= double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unary multiplication" << endl;
	cout << "---vector * vector" << endl;
	result_vec.display();
	vec2.display();
	result_vec *= vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector * arg" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec *= double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unary division" << endl;
	cout << "---vector / vector" << endl;
	result_vec.display();
	vec2.display();
	result_vec /= vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector / arg" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec /= double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unari +/-" << endl;
	vec2.display();
	result_vec = +vec2;
	result_vec.display();
	result_vec = -vec2;
	result_vec.display();

	Vector _vec1 = Vector(4);
	Vector _vec2 = Vector(5);
	Vector _vec_res;
	
	_vec_res = _vec1 + _vec2;
	_vec_res = _vec1 - _vec2;
	_vec_res = _vec1 * _vec2;
	_vec_res = _vec1 / _vec2;


	/*compare operator overloading*/
	cout << ">>>compare operator overloading" << endl;
	cout << ">>equality" << endl;
	double arr1[3] = {1.1, 2.2, 3.3};
	double arr2[3] = {1.1, 2.2, 3.3};
	vec2 = Vector(array_to_vector(3, arr1));
	vec3 = Vector(array_to_vector(3, arr2));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 == vec3) << endl;

	double arr3[3] = {2.222221, 3.333331, 4.444441};
	double arr4[3] = {2.222222, 3.333333, 4.444441};
	vec2 = Vector(array_to_vector(3, arr3));
	vec3 = Vector(array_to_vector(3, arr4));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 == vec3) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 == vec3) << endl;
	reset_compare_precision();

	cout << ">>inequality" << endl;
	double arr5[3] = {1.1, 2.2, 3.3};
	double arr6[3] = {1.1, 2.2, 3.2};
	vec2 = Vector(array_to_vector(3, arr5));
	vec3 = Vector(array_to_vector(3, arr6));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 != vec3) << endl;

	double arr7[3] = {2.222221, 3.333331, 4.444441};
	double arr8[3] = {2.222221, 3.333333, 4.444449};
	vec2 = Vector(array_to_vector(3, arr7));
	vec3 = Vector(array_to_vector(3, arr8));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 != vec3) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 != vec3) << endl;

	/*index access operator overloading*/
	cout << ">>>index access operator overloading" << endl;
	vec3.display();
	cout << vec3[0] << " " << vec3[1] << " " << vec3[2] << endl;

	vec3[0] = 2;
	vec3[1] = 1;
	vec3[2] = 0;
	vec3.display();
}

void test_vector3D()
{
	/*-----TESTING Vector3D`S METHODS-----*/
	double test_array[3] = {1, 2, 3};
	double test_array2[3] = {10, 20, 30};
	double test_array3[4] = {12, 13, 14, 15};

	/*create and display vectors*/
	cout << ">>>create and display vectors" << endl;
	Vector3D vec0;
	Vector3D vec1 = Vector3D(4);
	Vector3D vec2 = Vector3D(array_to_vector(3, test_array));
	Vector3D vec3 = Vector3D(10);
	cout << vec0.size() << endl;
	vec0.display();
	cout << vec1.size() << endl;
	vec1.display();
	cout << vec2.size() << endl;
	vec2.display();
	vec2.display(15);
	cout << vec3.size() << endl;
	vec3.display();
	cout << endl;

	/*output points in test_file.txt*/
	cout << ">>>output points in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	vec0.print(ostr);
	vec1.print(ostr);
	vec2.print(ostr);
	vec3.print(ostr);
	vec3.print(ostr, 15);
	ostr.close();

	/*arithmetic operator overloading*/
	vec3 = Vector3D(array_to_vector(3, test_array2));
	cout << ">>>arithmetic operator overloading" << endl;
	int int_const = 10;
	double double_const = 20.;
	Vector3D result_vec;
	cout << ">>binary summation" << endl;
	cout << "---vector + vector" << endl;
	result_vec = vec2 + vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector + int" << endl;
	result_vec = int_const + vec2;
	vec2.display();
	cout << int_const << endl;
	result_vec.display();
	result_vec.reset();
	cout << "---vector + double" << endl;
	result_vec = vec2 + double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();

	cout << ">>binary subtraction" << endl;
	cout << "---vector - vector" << endl;
	result_vec = vec2 - vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector - arg" << endl;
	result_vec = vec2 - double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();

	cout << ">>binary multiplication" << endl;
	cout << "---vector * vector" << endl;
	result_vec = vec2 * vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector * arg" << endl;
	result_vec = vec2 * double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();

	cout << ">>binary division" << endl;
	cout << "---vector / vector" << endl;
	result_vec = vec2 / vec3;
	vec2.display();
	vec3.display();
	result_vec.display();
	result_vec.reset();
	cout << "---vector / arg" << endl;
	result_vec = vec2 / double_const;
	vec2.display();
	cout << double_const << endl;
	result_vec.display();
	result_vec.reset();
	cout << endl;

	cout << ">>unary summation" << endl;
	cout << "---vector + vector" << endl;
	result_vec.reset();
	result_vec.display();
	vec2.display();
	result_vec += vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector + int" << endl;
	result_vec.display();
	cout << int_const << endl;
	result_vec += int_const;
	result_vec.display();
	result_vec.reset();
	cout << "---vector + double" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec += double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unary subtraction" << endl;
	cout << "---vector - vector" << endl;
	result_vec.display();
	vec2.display();
	result_vec -= vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector - arg" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec -= double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unary multiplication" << endl;
	cout << "---vector * vector" << endl;
	result_vec.display();
	vec2.display();
	result_vec *= vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector * arg" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec *= double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unary division" << endl;
	cout << "---vector / vector" << endl;
	result_vec.display();
	vec2.display();
	result_vec /= vec2;
	result_vec.display();
	result_vec.reset();
	cout << "---vector / arg" << endl;
	result_vec.display();
	cout << double_const << endl;
	result_vec /= double_const;
	result_vec.display();
	result_vec.reset();

	cout << ">>unari +/-" << endl;
	vec2.display();
	result_vec = +vec2;
	result_vec.display();
	result_vec = -vec2;
	result_vec.display();

	/*compare operator overloading*/
	cout << ">>>compare operator overloading" << endl;
	cout << ">>equality" << endl;
	double arr1[3] = {1.1, 2.2, 3.3};
	double arr2[3] = {1.1, 2.2, 3.3};
	vec2 = Vector(array_to_vector(3, arr1));
	vec3 = Vector(array_to_vector(3, arr2));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 == vec3) << endl;

	double arr3[3] = {2.222221, 3.333331, 4.444441};
	double arr4[3] = {2.222222, 3.333333, 4.444441};
	vec2 = Vector(array_to_vector(3, arr3));
	vec3 = Vector(array_to_vector(3, arr4));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 == vec3) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 == vec3) << endl;
	reset_compare_precision();

	cout << ">>inequality" << endl;
	double arr5[3] = {1.1, 2.2, 3.3};
	double arr6[3] = {1.1, 2.2, 3.2};
	vec2 = Vector(array_to_vector(3, arr5));
	vec3 = Vector(array_to_vector(3, arr6));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 != vec3) << endl;

	double arr7[3] = {2.222221, 3.333331, 4.444441};
	double arr8[3] = {2.222221, 3.333333, 4.444449};
	vec2 = Vector(array_to_vector(3, arr7));
	vec3 = Vector(array_to_vector(3, arr8));
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 != vec3) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	vec2.display();
	vec3.display();
	cout << (vec2 != vec3) << endl;

	/*index access operator overloading*/
	cout << ">>>index access operator overloading" << endl;
	vec3.display();
	cout << vec3[0] << " " << vec3[1] << " " << vec3[2] << endl;

	vec3[0] = 2;
	vec3[1] = 1;
	vec3[2] = 0;
	vec3.display();
}

void test_matrix()
{
	/*-----TESTING Matrix`S METHODS-----*/

	double **mass = new double* [3];
	for(int count = 0; count < 3; count++)
		mass[count] = new double[6];

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 6; j++)
			mass[i][j] = i + j;

	double mass2[3] = {10, 20, 30};

	/*create and display matrices*/
	cout << ">>>create and display matrices" << endl;
	Matrix matr0;
	Matrix matr1 = Matrix(3, 6);
	cout << matr0.rows() << "x" << matr0.cols() << endl;
	matr0.display();
	cout << matr1.rows() << "x" << matr1.cols() << endl;
	matr1.display();

	cout << ">>set matrix from number" << endl;
	matr1.set_matrix(2);
	matr1.display();
	cout << ">>set matrix from array" << endl;
	matr1.set_matrix(mass);
	matr1.display();
	cout << ">>set matrix to null" << endl;
	matr1.reset();
	matr1.display();
	cout << ">>set matrix to identity" << endl;
	matr1.set_identity_matrix();
	matr1.display();
	cout << ">>set matrix to diagonal from number" << endl;
	matr1.set_diagonal_matrix(4);
	matr1.display();
	cout << ">>set matrix to diagonal from vector" << endl;
	matr1.set_diagonal_matrix(array_to_vector(3, mass2));
	matr1.display();
	cout << ">>set matrix to upper subdiagonal from number" << endl;
	matr1.set_subdiagonal_matrix(3, 5);
	matr1.display();
	cout << ">>set matrix to lower subdiagonal from number" << endl;
	matr1.set_subdiagonal_matrix(-1, 5);
	matr1.display();
	cout << ">>set matrix to upper subdiagonal from vector" << endl;
	matr1.set_subdiagonal_matrix(3, array_to_vector(3, mass2));
	matr1.display();
	cout << ">>set matrix to lower subdiagonal from vector" << endl;
	matr1.set_subdiagonal_matrix(-1, array_to_vector(3, mass2));
	matr1.display();
	cout << ">>get matrix main diagonal" << endl;
	/*set more informative matrix*/
	matr1.set_matrix(mass);
	matr1.display();
	display_stlvector(matr1.get_main_diagonal());
	display_stlvector(matr1.get_diagonal(0));
	cout << ">>get matrix subdiagonal" << endl;
	display_stlvector(matr1.get_diagonal(1));
	display_stlvector(matr1.get_diagonal(2));
	display_stlvector(matr1.get_diagonal(3));
	display_stlvector(matr1.get_diagonal(4));
	display_stlvector(matr1.get_diagonal(5));
	display_stlvector(matr1.get_diagonal(6));
	display_stlvector(matr1.get_diagonal(-1));
	display_stlvector(matr1.get_diagonal(-2));
	display_stlvector(matr1.get_diagonal(-3));
	cout << ">>get matrix row" << endl;
	display_stlvector(matr1.get_row(0));
	display_stlvector(matr1.get_row(1));
	display_stlvector(matr1.get_row(2));
	display_stlvector(matr1.get_row(3));

	cout << ">>get matrix row" << endl;
	display_stlvector(matr1.get_col(0));
	display_stlvector(matr1.get_col(1));
	display_stlvector(matr1.get_col(2));
	display_stlvector(matr1.get_col(3));
	display_stlvector(matr1.get_col(4));
	display_stlvector(matr1.get_col(5));
	display_stlvector(matr1.get_col(6));

	/*output matrix in test_file.txt*/
	cout << ">>>output matrix in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	matr1.print(ostr);
	matr1.print(ostr, 15);
	ostr.close();

	/*arithmetic operator overloading*/
	Matrix result_matr;
	cout << ">>>arithmetic operator overloading" << endl;
	cout << ">>unari +/-" << endl;
	matr1.display();
	result_matr = +matr1;
	result_matr.display();
	result_matr = -matr1;
	result_matr.display();

	matr1.set_matrix(mass);
	Matrix matr2 = Matrix(3, 6);
	matr2.set_matrix(mass);
	matr2 = -matr2;
	Matrix matr3 = Matrix(3, 6);
	matr3.set_matrix(5);
	Matrix matr4 = Matrix(5, 7);
	Matrix matr5 = Matrix(6, 4);
	matr5.set_matrix(2);
	result_matr.reset();
	cout << ">>binary summation" << endl;
	cout << "---matrix + matrix" << endl;
	result_matr = matr2 + matr1;
	matr2.display();
	matr1.display();
	result_matr.display();
	result_matr.reset();
	cout << "---matrix + int" << endl;
	int int_const = 10;
	result_matr = int_const + matr3;
	matr3.display();
	cout << int_const << endl;
	result_matr.display();
	result_matr.reset();
	cout << "---matrix + double" << endl;
	double double_const = 20;
	result_matr = matr3 + double_const;
	matr3.display();
	cout << double_const << endl;
	result_matr.display();
	result_matr.reset();

	cout << ">>binary subtraction" << endl;
	cout << "---matrix - matrix" << endl;
	result_matr = matr1 - matr2;
	matr1.display();
	matr2.display();
	result_matr.display();
	result_matr.reset();
	cout << "---matrix - arg" << endl;
	result_matr = matr1 - double_const;
	matr1.display();
	cout << double_const << endl;
	result_matr.display();
	result_matr.reset();

	cout << ">>binary multiplication" << endl;
	cout << "---matrix * matrix" << endl;
	result_matr = matr1 * matr5;
	matr1.display();
	matr5.display();
	result_matr.display();
	result_matr.reset();
	cout << "---matrix * arg" << endl;
	result_matr = matr1 * double_const;
	matr1.display();
	cout << double_const << endl;
	result_matr.display();
	result_matr.reset();

	cout << ">>unary summation" << endl;
	cout << "---matrix + matrix" << endl;
	result_matr.reset();
	result_matr.display();
	matr1.display();
	result_matr += matr1;
	result_matr.display();
	result_matr.reset();
	cout << "---matrix + int" << endl;
	result_matr.display();
	cout << int_const << endl;
	result_matr += int_const;
	result_matr.display();
	result_matr.reset();
	cout << "---matrix + double" << endl;
	result_matr.display();
	cout << double_const << endl;
	result_matr += double_const;
	result_matr.display();
	result_matr.reset();

	cout << ">>unary subtraction" << endl;
	cout << "---matrix - matrix" << endl;
	result_matr.display();
	matr1.display();
	result_matr -= matr1;
	result_matr.display();
	result_matr.reset();
	cout << "---matrix - arg" << endl;
	result_matr.display();
	cout << double_const << endl;
	result_matr -= double_const;
	result_matr.display();
	result_matr.reset();

	cout << ">>unary multiplication" << endl;
	cout << "---vector * vector" << endl;
	result_matr.display();
	matr5.display();
	result_matr *= matr5;
	result_matr.display();
	result_matr.reset();
	cout << "---vector * arg" << endl;
	result_matr.display();
	cout << double_const << endl;
	result_matr *= double_const;
	result_matr.display();
	result_matr.reset();

	/*compare operator overloading*/
	cout << ">>>compare operator overloading" << endl;
	cout << ">>equality" << endl;
	matr1.set_matrix(1.000001);
	matr2.set_matrix(1.000001);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	matr1.display();
	matr2.display();
	cout << (matr1 == matr2) << endl;

	matr1.set_matrix(1.000001);
	matr2.set_matrix(1.000002);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	matr1.display();
	matr2.display();
	cout << (matr1 == matr2) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	matr1.display();
	matr2.display();
	cout << (matr1 == matr2) << endl;
	reset_compare_precision();

	cout << ">>inequality" << endl;
	matr1.set_matrix(1.000001);
	matr2.set_matrix(1.000001);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	matr1.display();
	matr2.display();
	cout << (matr1 != matr2) << endl;

	matr1.set_matrix(1.000001);
	matr2.set_matrix(1.000002);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	matr1.display();
	matr2.display();
	cout << (matr1 != matr2) << endl;
	set_compare_precision(1e-3);
	cout << "compare precision = " << get_current_compare_precision() << endl;
	matr1.display();
	matr2.display();
	cout << (matr1 != matr2) << endl;
	reset_compare_precision();

	/*subscript operator overloading*/
	cout << ">>>subscript operator overloading" << endl;
	matr1.set_matrix(mass);
	matr1.display();
	cout << matr1(1, 5) << " " << matr1(2, 4) << " " << matr1(0, 0) << endl;

	matr1(1, 5) = 100.;
	matr1(2, 4) = 200.;
	matr1(0, 0) = 300.;
	matr1.display();
}

void test_common_function_point()
{
	cout << ">>>calculate distance between points" << endl;
	Point2D point2D_A = Point2D(1, 5);
	Point2D point2D_B = Point2D(7, 10);
	point2D_A.display();
	point2D_B.display();
	cout << points_distance(point2D_A, point2D_B) << endl;

	Point3D point3D_A = Point3D(1, 5, 18);
	Point3D point3D_B = Point3D(7, 10, 100);
	point3D_A.display();
	point3D_B.display();
	cout << points_distance(point3D_A, point3D_B) << endl;
}

void test_common_function_vector()
{
	cout << endl << ">>>swap vectors" << endl;
	Vector vector_A = Vector(5, 3);
	Vector vector_B = Vector(5, 9);
	Vector vector_C = Vector(7, 2);
	vector_A.display();
	vector_B.display();
	cout << "swap:" << endl;
	swap_vectors(&vector_A, &vector_B);
	vector_A.display();
	vector_B.display();
	vector_A.display();
	vector_C.display();
	cout << "swap:" << endl;
	swap_vectors(&vector_A, &vector_C);
	vector_A.display();
	vector_C.display();

	swap_vectors(&vector_A, &vector_C);
	swap_vectors(&vector_A, &vector_B);
	cout << endl << ">>>calculate dot product" << endl;
	vector_A.display();
	vector_B.display();
	cout << dot_product(vector_A, vector_B) << endl;
	vector_A.display();
	vector_C.display();
	cout << dot_product(vector_A, vector_C) << endl;

	cout << endl << ">>>calculate Euclidean vector norm" << endl;
	vector_A.display();
	cout << norm_euclidean(vector_A) << endl;

}

void test_common_function_vector3D()
{
	cout << endl << ">>>swap vectors" << endl;
	Vector3D vector_A = Vector3D(3);
	Vector3D vector_B = Vector3D(9);
	vector_A.display();
	vector_B.display();
	cout << "swap:" << endl;
	swap_vectors(&vector_A, &vector_B);
	vector_A.display();
	vector_B.display();

	cout << endl << ">>>calculate dot product" << endl;
	vector_A.display();
	vector_B.display();
	cout << dot_product(vector_A, vector_B) << endl;
	
	cout << endl << ">>>calculate Euclidean vector norm" << endl;
	vector_A.display();
	cout << norm_euclidean(vector_A) << endl;

	cout << endl << ">>>calculate cross product" << endl;
	double arr0[3] = {2, 3, 6};
	double arr1[3] = {4, 6, 13};
	vector_A.display();
	vector_B.display();
	cout << "cross product: ";
	cross_product(vector_A, vector_B).display();
	vector_A = Vector3D(array_to_vector(3, arr0));
	vector_B = Vector3D(array_to_vector(3, arr1));
	vector_A.display();
	vector_B.display();
	cout << "cross product: ";
	cross_product(vector_A, vector_B).display();

	cout << endl << "calculate vector`s coordinate" << endl;
	Point3D point1 = Point3D(7, 6, 11);
	Point3D point2 = Point3D(12, 5, 8);
	cout << "point 1: ";
	point1.display();
	cout << "point 2: ";
	point2.display();
	vector_coordinates(point1, point2).display();

	cout << endl << ">>>check vector`s orthogonality" << endl;
	double arr2[3] = {2, 3, 6};
	double arr3[3] = {-3, -4, 3};
	vector_A = Vector3D(3);
	vector_B = Vector3D(9);
	vector_A.display();
	vector_B.display();
	cout << "orthogonality: " << orthogonality_check(vector_A, vector_B) << endl;
	vector_A = Vector3D(array_to_vector(3, arr2));
	vector_B = Vector3D(array_to_vector(3, arr3));
	vector_A.display();
	vector_B.display();
	cout << "orthogonality: " << orthogonality_check(vector_A, vector_B) << endl;

	cout << endl << ">>>check vector`s collinearity" << endl;
	double arr4[3] = {1, 0, 0};
	double arr5[3] = {0, 1, 2};
	vector_A = Vector3D(3);
	vector_B = Vector3D(9);
	vector_A.display();
	vector_B.display();
	cout << "collinearity: " << collinearity_check(vector_A, vector_B) << endl;
	vector_A = Vector3D(array_to_vector(3, arr4));
	vector_B = Vector3D(array_to_vector(3, arr5));
	vector_A.display();
	vector_B.display();
	cout << "collinearity: " << collinearity_check(vector_A, vector_B) << endl;

	cout << endl << ">>>calculate angle between vectors" << endl;
	double arr6[3] = {1, 0, 0};
	double arr7[3] = {0, 1, 0};
	vector_A = Vector3D(3);
	vector_B = Vector3D(9);
	vector_A.display();
	vector_B.display();
	cout << "angle: rad: " << vectors_angle_rad(vector_A, vector_B) << " deg: " << vectors_angle_deg(vector_A, vector_B) << endl;
	vector_A = Vector3D(array_to_vector(3, arr6));
	vector_B = Vector3D(array_to_vector(3, arr7));
	vector_A.display();
	vector_B.display();
	cout << "angle: rad: " << vectors_angle_rad(vector_A, vector_B) << " deg: " << vectors_angle_deg(vector_A, vector_B) << endl;

}

void test_common_function_matrix()
{
	double mass[4] = {1, 2, 3, 4};
	double mass2[4] = {4, 3, 2, 1};
	Vector vectorRow = Vector(4);
	Vector vectorCol = Vector(4);
	Vector vectorD = Vector(10);
	Matrix matrix = Matrix(2, 4);
	Matrix matrix2 = Matrix(4, 3);
	Matrix matrixD = Matrix(10, 10);
	matrix.set_matrix(3.);
	matrix2.set_matrix(5.);
	vectorRow.set_elements(array_to_vector(4, mass));
	vectorCol.set_elements(array_to_vector(4, mass2));

	cout << ">>>calculate product of vector-row and vector-col" << endl;
	vectorRow.display();
	vectorCol.display();
	cout << multiply_vectorRow_by_vectorCol(vectorRow, vectorCol) << endl;
	cout << endl << ">>>calculate product of vector-col and vector-row" << endl;
	vectorCol.display();
	vectorRow.display();
	multiply_vectorCol_by_vectorRow(vectorCol, vectorRow).display();
	cout << ">>>calculate product of matrix and vector" << endl;
	matrix.display();
	vectorCol.display();
	multiply_matrix_by_vector(matrix, vectorCol).display();
	cout << endl;
	cout << ">>>calculate product of matrix and matrix" << endl;
	matrix.display();
	matrix2.display();
	multiply_matrix_by_matrix(matrix, matrix2).display();
	cout << ">>>strike out row and col" << endl;
	matrix.display();
	Matrix striked_matrix = strike_out(matrix, 0, 0);
	striked_matrix.display();
	matrix.display();
	matrix.strike_out(1, 1).display();

	cout << ">>>calculate determinant" << endl;
	matrix2 = Matrix(4, 4);
	matrix2.set_matrix(2);
	Matrix matrix3 = Matrix(1, 1);
	matrix3.set_matrix(2);
	Matrix matrix4 = Matrix(2, 2);
	matrix4(0, 0) = 4; matrix4(0, 1) = 5;
	matrix4(1, 0) = 3; matrix4(1, 1) = 9;
	Matrix matrix5 = Matrix(5, 5);
	matrix5.set_diagonal_matrix(2);
	Matrix matrix6 = Matrix(4, 4);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			matrix6(i, j) = i + j;

	matrix3.display();
	cout << "determinant: " << matrix3.determinant() << endl;
	matrix4.display();
	cout << "determinant: " << matrix4.determinant() << endl;
	matrix2.display();
	cout << "determinant: " << matrix2.determinant() << endl;
	matrix.display();
	cout << "determinant: " << matrix.determinant() << endl;
	matrix5.display();
	cout << "determinant: " << matrix5.determinant() << endl;
	matrix6.display();
	cout << "determinant: " << matrix6.determinant() << endl << endl;
	
	cout << ">>>transpose matrix" << endl;
	matrix4.display();
	matrix4.transpose().display();
	matrix = Matrix(3, 5);
	matrix.set_matrix(3);
	matrix(1, 3) = 100;
	matrix.display();
	matrix.transpose().display();
	
	cout << ">>>inverse matrix" << endl;
	matrix = Matrix(4, 4);
	matrix(0, 0) = 2; matrix(0, 1) = 3; matrix(0, 2) = 7; matrix(0, 3) = 9;
	matrix(1, 0) = 15; matrix(1, 1) = 0; matrix(1, 2) = 2; matrix(1, 3) = 1;
	matrix(2, 0) = 11; matrix(2, 1) = 1; matrix(2, 2) = 8; matrix(2, 3) = 3;
	matrix(3, 0) = 5; matrix(3, 1) = 9; matrix(3, 2) = 4; matrix(3, 3) = 13;
	cout << "based matrix:" << endl;
	matrix.display();
	cout << "determinant: " << matrix.determinant() << endl;
	cout << "inversed matrix:" << endl;
	matrix2 = matrix.inverse();
	matrix2.display();
	cout << "check: based * inversed" << endl;
	matrix3 = matrix * matrix2;
	matrix3.display();

	cout << ">>>swap matrices" << endl;
	matrix.display();
	matrix2.display();
	swap_matrices(&matrix, &matrix2);
	matrix.display();
	matrix2.display();

	int i = 0;
}

void test_spline1D_function()
{
	Spline1D_linear spline;
	Spline1D_cubic splineC;
	vector<double> X;
	vector<double> F;

	/*create and display data for spline class*/
	cout << ">>>create and display data for 1D linear spline class" << endl;
	create_data(&X, &F);
	spline = Spline1D_linear(X, F);
	spline.display();

	/*output spline in spline_initial.txt*/
	cout << ">>>output initial 1D linear spline in spline_initial.txt" << endl;
	const char *file_name = "spline_initial.txt";
	ofstream ostr;
	ostr.open(file_name);
	spline.print(ostr);
	ostr.close();

	/*calculate value using linear functions*/
	cout << ">>>output result 1D linear spline in spline_result.txt" << endl;
	Spline1D_linear new_spline = spline.get_spline(10);
	file_name = "spline_result.txt";
	ostr.open(file_name);
	new_spline.print(ostr);
	ostr.close();

	/*********************************************************************************/

	/*create and display data for spline class*/
	cout << endl << ">>>create and display data for 1D cubic spline class" << endl;
	create_data(&X, &F);
	splineC = Spline1D_cubic(X, F);
	splineC.display();

	/*output spline in spline_initial.txt*/
	cout << ">>>output initial 1D cubic spline in spline_initial.txt" << endl;
	file_name = "spline_initial.txt";
	ostr.open(file_name);
	splineC.print(ostr);
	ostr.close();

	/*calculate value using cubic functions*/
	cout << ">>>output result 1D cubic spline in spline_result.txt" << endl;
	Spline1D_cubic new_splineC = splineC.get_spline(20);
	file_name = "spline_result.txt";
	ostr.open(file_name);
	new_splineC.print(ostr);
	ostr.close();

	/*calculate df value using cubic functions*/
	cout << ">>>output result 1D derivative cubic spline in spline_result.txt" << endl;
	new_splineC = splineC.get_dfspline(10);
	file_name = "spline_result.txt";
	ostr.open(file_name);
	new_splineC.print(ostr);
	ostr.close();


	int i = 0;

}

void test_spline2D_function()
{
	Spline2D_linear spline;
	Spline2D_cubic splineC;
	vector<double> X;
	vector<double> Y;
	Matrix Z = Matrix(10,20);

	/*create and display data for spline class*/
	cout << ">>>create and display data for 2D linear spline class" << endl;
	create_data(&X, &Y, &Z);
	spline = Spline2D_linear(X, Y, Z);
	spline.display();

	/*output spline in spline_initial.txt*/
	cout << ">>>output 2D linear spline in spline_initial.txt" << endl;
	const char *file_name = "spline_initial.txt";
	ofstream ostr;
	ostr.open(file_name);
	spline.print(ostr);
	//spline.print(ostr, 16);
	ostr.close();

	/*calculate value using bilinear functions*/
	cout << ">>>output 2D linear spline in spline_result.txt" << endl;
	Spline2D_linear new_spline = spline.get_spline(10, 10);
	file_name = "spline_result.txt";
	ostr.open(file_name);
	new_spline.print(ostr);
	ostr.close();

	/*********************************************************************************/

	/*create and display data for spline class*/
	cout << ">>>create and display data for 2D cubic spline class" << endl;
	create_data(&X, &Y, &Z);
	splineC = Spline2D_cubic(X, Y, Z);
	splineC.display();

	/*output spline in spline_initial.txt*/
	cout << ">>>output 2D cubic spline in spline_initial.txt" << endl;
	file_name = "spline_initial.txt";
	ostr.open(file_name);
	splineC.print(ostr);
	ostr.close();

	/*calculate value using bilinear functions*/
	cout << ">>>output 2D cubic spline in spline_result.txt" << endl;
	Spline2D_cubic new_splineC = splineC.get_spline(10, 10);
	file_name = "spline_result.txt";
	ostr.open(file_name);
	new_splineC.print(ostr);
	ostr.close();

	int i = 0;
}

void test_mesh_elements_node()
{
	cout << ">>>test creating nodes" << endl;
	Node3D node;
	node.display();
	node.display(16);
	node = Node3D(1, 2, 3, 0, true);
	node.display();
	node = Node3D(Point3D(4, 5, 6), 1, true);
	node.display();
	node.set_node(Point3D(7, 8, 9), 2, false);
	node.display();
	node.set_node(10, 11, 12, 3, true);
	node.display();
	Point3D point;
	point = node.get_coordinates();
	point.display();
	double x = node.get_coordinates()[0];
	double y = node.get_coordinates()[1];
	double z = node.get_coordinates()[2];
	int number = node.get_number();
	bool needful = node.get_needful();
	cout << number << " " << x << " " << y << " " << z << " " << needful << endl;
	node.reset();
	node.display();

	cout << ">>>output nodes in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	node.print(ostr);
	node.print(ostr, 15);
	ostr.close();
}

void test_mesh_elements_firstBC()
{
	cout << ">>>test creating firstBC" << endl;
	FirstBC fBC;
	fBC.display();
	fBC = FirstBC(1, 1);
	fBC.display();
	fBC.set_firstBC(2, 2);
	fBC.display();
	fBC.reset();
	int number = fBC.get_number();
	int n_formula = fBC.get_n_formula();
	cout << number << " " << n_formula << endl;

	cout << ">>>output nodes in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	fBC.print(ostr);
	ostr.close();
}

void test_mesh_elements_face()
{
	Face face;
	face.display();
	vector<int> numbers = vector<int>(4, 2);
	face = Face(numbers, 1);
	face.display();
	face.reset();
	face.display();
	face.set_face(numbers, 5);
	numbers = face.get_numbers();
	int number = face.get_number(2);
	int n_formula = face.get_n_formula();
	cout << number << " " << n_formula << endl;
	display_stlvector(numbers);

	cout << ">>>output faces in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	face.print(ostr);
	ostr.close();
}

void test_mesh_elements_fe()
{
	FE fe;
	fe.display();
	vector<int> numbers = vector<int>(8, 3);
	fe = FE(numbers, 1, true);
	fe.display();
	fe.reset();
	fe.display();
	fe.set_fe(numbers, 2, true);
	numbers = fe.get_numbers();
	int n_area = fe.get_n_area();
	int needful = fe.get_needful();
	int number = fe.get_number(2);
	display_stlvector(numbers);
	cout << n_area << " " << needful << " " << number << endl;

	cout << ">>>output fes in test_file.txt" << endl;
	const char *file_name = "test_file.txt";
	ofstream ostr;
	ostr.open(file_name);
	fe.print(ostr);
	ostr.close();
}

void test_mesh_builder()
{
	MeshBuilder mesh_builder;
	mesh_builder.set_layer_boundary();
	mesh_builder.set_anomalies();
	mesh_builder.set_fragmentation();
	mesh_builder.set_formula();
	mesh_builder.build_mesh();
	mesh_builder.get_mesh();
}

int main()
{
	/*-----TESTING Point2D`S METHODS-----*/
	//test_point2D();

	/*-----TESTING Point3D`S METHODS-----*/
	//test_point3D();

	/*-----TESTING Vector`S METHODS-----*/
	//test_vector();

	/*-----TESTING Vector3D`S METHODS-----*/
	//test_vector3D();

	/*-----TESTING Matrix`S FUNCTION -----*/
	//test_matrix();

	/*-----TESTING COMMON FUNCTION -----*/
	//test_common_function_point();
	//test_common_function_vector();
	//test_common_function_vector3D();
	//test_common_function_matrix();

	/*-----TESTING SPLINE FUNCTION -----*/
	//test_spline1D_function();
	//test_spline2D_function();

	/*-----TESTING MESH FUNCTION -----*/
	//test_mesh_elements_node();
	//test_mesh_elements_firstBC();
	//test_mesh_elements_face();
	//test_mesh_elements_fe();
	test_mesh_builder();

	return 0;
}
#include "point.hpp"
#include <math.h>

/*
 *
 * Constructor
 *
 */
point::point() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

point::point(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

point::point(const point& p) {
	this->x = p.get_x();
	this->y = p.get_y();
	this->z = p.get_z();
}

/*
 *
 * Setter and Getter
 *
 */

int point::get_x() const {
	return this->x;
}

int point::get_y() const {
	return this->y;
}

int point::get_z() const {
	return this->z;
}

void point::set_x(int x) {
	this->x = x;
}

void point::set_y(int y) {
	this->y = y;
}

void point::set_z(int z) {
	this->z = z;
}

void point::set_coord(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

/*
 *
 * Transformation
 *
 */

point point::scale(float scale, int x_origin, int y_origin, int z_origin) {
	this->x = floor((this->x - x_origin) * scale + x_origin);
	this->y = floor((this->y - y_origin) * scale + y_origin);
	this->z = floor((this->z - z_origin) * scale + z_origin);

	return *this;
}

point point::rotate(float angle, int x_origin, int y_origin, int z_origin) {
	float s = sin(angle);
	float c = cos(angle);

	int x = this->x;
	int y = this->y;
	int z = this->z;

	this->x = floor( c * (x - x_origin) + s * (y - y_origin)) + x_origin;
	this->y = floor( c * (y - y_origin) - s * (x - x_origin)) + y_origin;
	this->z = floor( c * (z - z_origin) - s * (z - z_origin)) + z_origin;

	return *this;
}

point point::move(int delta_x, int delta_y, int delta_z) {
	point p(this->get_x() + delta_x, this->get_y() + delta_y, this->get_z() + delta_z);

	return p;
}

/*
 *
 * Comparator function
 *
 */

bool point::cmp_x(const point& p1, const point& p2) {
	return p1.get_x() < p2.get_x();
}

bool point::cmp_y(const point& p1, const point& p2) {
	return p1.get_y() < p2.get_y();
}

bool point::cmp_z(const point& p1, const point& p2) {
	return p1.get_z() < p2.get_z();
}

/*
 * Prespective Projection
 *
 */
point point::camera_tranform(point camera_position, double o_x, double o_y, double o_z) {

	double m1[] = {
		1, 0, 0,
		0, cos(-o_x), -sin(-o_x),
		0, sin(-o_x), cos(-o_x)
	};

	double m2[] = {
		cos(-o_y), 0, sin(-o_y),
		0, 1, 0,
		-sin(-o_y), 0, cos(-o_y)
	};

	double m3[] = {
		cos(-o_z), -sin(-o_z), 0,
		sin(-o_z), cos(-o_z), 0,
		0, 0, 1
	};

	double offset[] = {
		(double) x - camera_position.get_x(),
		(double) y - camera_position.get_y(),
		(double) z - camera_position.get_z()
	};

	matrix M1(3, 3, m1);
	matrix M2(3, 3, m2);
	matrix M3(3, 3, m3);
	matrix Offset(3, 1, offset);

	matrix result_1 = matrix::multiplication(M1,M2);
	matrix result_2 = matrix::multiplication(result_1, M3);
	matrix result = matrix::multiplication(result_2, Offset);

	point to_return;
	to_return.set_x((int) result.at(0, 0));
	to_return.set_y((int) result.at(1, 0));
	to_return.set_z((int) result.at(2, 0));

	return to_return;

}

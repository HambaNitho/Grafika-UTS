#ifndef _POIN_H
#define _POIN_H

#include <cmath>
#include <vector>
//#include "multiplication.hpp"

class point {
public:
	// Constructor
	point();
	point(int x, int y, int z = 0);
	point(const point& p);

	// Setter and getter
	int get_x() const;
	int get_y() const;
	int get_z() const;
	void set_x(int x);
	void set_y(int y);
	void set_z(int z);
	void set_coord(int x, int y, int z = 0);

	// Comparator function
	static bool cmp_x(const point& p1, const point& p2);
	static bool cmp_y(const point& p1, const point& p2);
	static bool cmp_z(const point& p1, const point& p2);

	// Transformasi
	point move(int delta_x = 0, int delta_y = 0, int delta_z = 0);
	point scale(float scale, int x_origin, int y_origin, int z_origin = 0);
	point rotate(float angle, int x_origin, int y_origin, int z_origin = 0);

	// Prespective Projection
	//point camera_tranform(point camera_position, double o_x, double o_y, double o_z);

private:
	int x;
	int y;
	int z;
};

#endif

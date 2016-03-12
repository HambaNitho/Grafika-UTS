#ifndef _BEZIER_H
#define _BEZIER_H

#include <cmath>
#include <vector>
#include "point.hpp"
#include "line.hpp"
#include "canvas.hpp"

class bezier {
public:
	// Constructor
	bezier();
	bezier(std::vector<point> points);

	// Setter and getter
	std::vector<point> get_points();
	bool is_surface();
	void set_points(std::vector<point> points);
	
	// Transformasi
	void add_point(point p, int position);
	void delete_point(int position);
	void move_point(int position, int delta_x = 0, int delta_y = 0, int delta_z = 0);

	void recursive_bezier(std::vector<point> points, double t, uint32_t color);
	//void draw_bezier(uint32_t color);
	int* getPascalTriangle (int n);
	void draw_bezier(std::vector<point> points, double ratio, uint32_t color);

private:
	std::vector<point> points;
	std::vector<point> b_points;
	double tolerance;
};

#endif

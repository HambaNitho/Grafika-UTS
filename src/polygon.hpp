/*
 * Husni Munaya / 13513022
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "include.hpp"
#include "canvas.hpp"
#include "color.hpp"
#include "point.hpp"

class polygon {
public:
	// Constructor
	polygon();
	void add_point(int x, int y);
	
	void add_point(point p);
	
	void set_point(int index, point new_value);
	
	void reset();
	
	void resize(int n_points);

	void draw_stroke(int x = 0, int y = 0, uint32_t color = 0xffffffff);
	
	void draw_fill(int x = 0 , int y = 0, uint32_t color = 0xffffffff);
	
	std::vector<int> scanline(int y);
	
	// Getter
	std::vector<point> get_points();
	
	// Transformation
	void scale(float scale);
	
	void rotate(float rotate);
private:
	
	float scale_factor;
	
	float rotate_factor;
	
	std::vector<point> points;
};

#endif

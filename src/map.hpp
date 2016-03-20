/*
 * Faisal Prabowo / 13513022
 */

 #ifndef _MAP_H
 #define _MAP_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "canvas.hpp"
#include "polygon.hpp"
#include "bezier.hpp"

 class map {
	 public:
	 	map();
	 	void map_add_point(std::string filename, polygon &p, int x_offset, int y_offset);
	 	void map_add_point_bezier(std::string filename, std::vector<point> &p, int x_offset, int y_offset);
	 	void draw_map(int x_offset, int y_offset);
	 	void set_scale(int n_scale);
	 	std::vector<polygon> get_map_polygons();

	 private:
	 	int scale;
	 	std::vector<polygon> map_polygons;

 };

 #endif

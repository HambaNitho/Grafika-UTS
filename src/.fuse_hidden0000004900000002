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
	 	void map_add_point(std::string filename, polygon &p);
	 	void map_add_point_bezier(std::string filename, std::vector<point> &p);
	 	void draw_map();
	 	void set_scale(int n_scale);

	 private:
	 	int scale;

 };

 #endif

/*
 * Faisal Prabowo / 13513022
 */

 #ifndef _MAP_H
 #define _MAP_H

 #include <iostream>
 #include "canvas.hpp"
 #include "polygon.hpp"
 #include "bezier.hpp"

 class map {
	 public:
	 	map();
	 	void draw_map();
	 	void draw_contour();
	 	void set_scale(int n_scale);

	 private:
	 	int scale;

 };

 #endif

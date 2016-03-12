#ifndef _FILL_H
#define _FILL_H

#include "polygon.hpp"
#include "line.hpp"
#include "canvas.hpp"
#include <list>
#include <vector>

using namespace std;

class fillo {
public:

	fillo(list<polygon> polygons, list<uint32_t> colors);
	void fill_polygons();
	void allocate_polygon(polygon pg, uint32_t color, int y_pos);
	void allocate_color(int x1, int x2, int y, uint32_t color);

private:
	list<point> free_space;
	list<polygon> polygons;
	list<uint32_t> colors;
};

#endif
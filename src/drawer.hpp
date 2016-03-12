#ifndef _DRAWER_H
#define _DRAWER_H

#include <vector>
#include "include.hpp"
#include "canvas.hpp"
#include "color.hpp"
#include "point.hpp"
#include "polygon.hpp"

class drawer {
public:
	static drawer* get_instance();
	void draw();
	void add_polygon(polygon p, uint32_t color);
private:
	drawer();
	static drawer* instance;
	std::vector<polygon> polygons;
	std::vector<uint32_t> colors;
};
#endif

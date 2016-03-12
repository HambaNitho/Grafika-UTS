#include "drawer.hpp"

drawer* drawer::instance;

drawer::drawer() {}

void drawer::draw() {
	for (int x = 0 ; x < polygons.size(); x++) {
		polygons[x].draw_fill(0 , 0, colors[x]);
		polygons[x].draw_stroke(0 , 0, colors[x]);
	}
}

void drawer::add_polygon(polygon p, uint32_t color) {
	polygons.push_back(p);
	colors.push_back(color);
}


drawer* drawer::get_instance() {
	if (drawer::instance) {
		return drawer::instance;
	}

	return drawer::instance = new drawer();
}

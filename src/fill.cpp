#include "fill.hpp"
#include <stdio.h>

using namespace std;

fillo::fillo(list<polygon> polygons, list<uint32_t> colors) {
	// list<point> free_space;
	this->polygons = polygons;
	this->colors = colors;
}

void fillo::fill_polygons() {
	list<polygon>::iterator i; list<uint32_t>::iterator color;
	// screen resolution
	int v_res = canvas::get_instance()->get_var_info().yres;
	int h_res = canvas::get_instance()->get_var_info().xres;
	for (int y = 0; y < v_res; y++) {
		//printf("y = %d\n",y);
		i = polygons.begin(); color = colors.begin();
		int j=0;
		free_space.push_back(point(0,h_res));
		while ( (i != polygons.end()) && (!free_space.empty()) ) { // allocate colors of every visible polygons
			//printf("i = %d\n",j);
			allocate_polygon(*i, *color, y);
			i++; color++; j++;
		}
		free_space.clear();
	}
}

void fillo::allocate_polygon(polygon pg, uint32_t color, int y_pos) {
	std::vector<point> sorted_y_pts = pg.get_points();
	sort(sorted_y_pts.begin(), sorted_y_pts.end(), point::cmp_y);

	int topY = sorted_y_pts[0].get_y();
	int bottomY = sorted_y_pts[sorted_y_pts.size() - 1].get_y();
	if (y_pos >= topY && y_pos <= bottomY) {

		vector<int> x_pos = pg.scanline(y_pos); // vector<int> scanline(polygon pg, int y_pos) gets intersections
		for (int i = 0; i < 2; i++) { // even-odd fillo
			allocate_color(x_pos[i], x_pos[i+1], y_pos, color);
			i++;
		}

	}
}

// free space
//      |-------------|
//
// request
//                      |--|
// |--|
// |----||
//      ||-------------|
//      |------------||
//       |-----------||
void fillo::allocate_color(int x1, int x2, int y, uint32_t color) {
	list<point>::iterator i = free_space.begin(), i2;
	int temp;
	while ( (i != free_space.end()) && (!free_space.empty()) ) {
		if (x1 >= i->get_y()) { // case current free space not sufficient
			i++;
		} else if (x1 < i->get_x()) { // 
			if (x2 < i->get_x()){
				break;
			}
			else {
				x1 = i->get_x();
			}
		} else {
			if (x2 > i->get_y()) {
				/////////////////////////draw_line(x1, i->get_y());
				point p1(x1,y); point p2(i->get_y(),y);
				line l(p1,p2);
				temp = x1;
				x1 = i->get_y();
				i->set_y(x1);
				i++;
			} else {
				/////////////////////////draw_line(x1, x2);
				point p1(x1,y); point p2(x2,y);
				line l(p1,p2);
				l.draw(color);
				if (x1 == i->get_x()) {
					i->set_x(x2);
				} else {
					i2 = i;
					i2++;
					point p(x2,i->get_y());
					free_space.insert(i2, p);
					i->set_y(x1);
				}
			}
			if (i->get_x() == i->get_y()){
				free_space.erase(i);
			}
			else {
				i++;
			}
		}
	}
}
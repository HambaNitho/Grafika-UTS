#include "polygon.hpp"
#include "line.hpp"
#include <iostream>
#include <algorithm>

polygon::polygon() {
	this->scale_factor = 1;
	this->rotate_factor = 0;
}

void polygon::add_point(int x, int y) {
	point p(x, y);
	this->points.push_back(p);
}

void polygon::add_point(point p) {
	point p0(p.get_x(), p.get_y());
	this->points.push_back(p0);
}

void polygon::set_point(int index, point new_value) {
	points[index] = new_value;
}

void polygon::draw_stroke(int x, int y, uint32_t color) {
	int x_origin = points[0].get_x() + x;
	int y_origin = points[0].get_y() + y;

	for (int i = 0; i < points.size() -1; i++) {
		point p1 = points[i].move(x, y).scale(scale_factor, x_origin, y_origin).rotate(rotate_factor, x_origin, y_origin);
		point p2 = points[i+1].move(x, y).scale(scale_factor, x_origin, y_origin).rotate(rotate_factor, x_origin, y_origin);

		line l(p1, p2);
		l.draw(color);
	}

	point p1 = points[points.size() - 1].move(x, y).scale(scale_factor, x_origin, y_origin).rotate(rotate_factor, x_origin, y_origin);
	point p2 = points[0].move(x, y).scale(scale_factor, x_origin, y_origin).rotate(rotate_factor, x_origin, y_origin);

	line l(p1, p2);
	l.draw(color);
}

std::vector<point> polygon::get_points() {
	return points;
}

void polygon::reset() {
	points.clear();
}

void polygon::resize(int n_points) {
	points.resize(n_points);
}

void polygon::draw_fill(int x, int y, uint32_t color) {
	// Cari titik paling kiri
	std::vector<point> sorted_x_pts = points;
	sort(sorted_x_pts.begin(), sorted_x_pts.end(), point::cmp_x);

	std::vector<point> sorted_y_pts = points;
	sort(sorted_y_pts.begin(), sorted_y_pts.end(), point::cmp_y);

	int leftX = sorted_x_pts[0].get_x();
	int rightX = sorted_x_pts[sorted_x_pts.size() - 1].get_x();

	int topY = sorted_y_pts[0].get_y();
	int bottomY = sorted_y_pts[sorted_y_pts.size() - 1].get_y();


	for (int i = topY; i <= bottomY; i++) {
		
		// printf("%d\n", i);
		
		std::vector<point> intersect;
		for (int j = 0; j < points.size(); j++) {
			// Cek perpotongan

			// printf("%d, %d",points[j].get_x(), points[j].get_y());
			// printf(" %d, %d\n",points[(j + 1) % points.size()].get_x(), points[(j + 1) % points.size()].get_y());


			int ymax = std::max(points[j].get_y(), points[(j+1) % points.size()].get_y());
			int ymin = std::min(points[j].get_y(), points[(j+1) % points.size()].get_y());

			int xmax = std::max(points[j].get_x(), points[(j+1) % points.size()].get_x());
			int xmin = std::min(points[j].get_x(), points[(j+1) % points.size()].get_x());

			if (i >= ymin && i <= ymax){// && i != points[j].get_y()) {
				float deltaX = points[j].get_x() - points[(j+1)%points.size()].get_x();
				float deltaY = points[j].get_y() - points[(j+1)%points.size()].get_y();
				float gradien = 0;
				
				if (deltaX != 0 && deltaY != 0) {
					gradien = deltaX/deltaY;	
				}


				int intersect_y = i;
				int intersect_x;


				if (deltaX == 0) {
					intersect_x = xmin;
				} else {
					if (gradien < 0) {
						intersect_x = ((ymax - i) * (xmax - xmin) / (ymax - ymin)) + xmin;
					} else if (gradien > 0) {
						intersect_x = ((i - ymin) * (xmax - xmin) / (ymax - ymin)) + xmin;
					}
				}

				// printf("berpotongan di %d, %d\n", intersect_x, intersect_y);
				point p(intersect_x, intersect_y);
				intersect.push_back(p);

			} else {
				// printf("tidak berpotongan\n");
			}
		}

		sort(intersect.begin(), intersect.end(), point::cmp_x);
		if (intersect[0].get_y() != intersect[1].get_y())
		printf("draw from %d, %d to %d, %d at i = %d\n", intersect[0].get_x(), intersect[0].get_y(), intersect[1].get_x(), intersect[1].get_y(), i);
		int k = 1;
		if (intersect[0].get_x() == intersect[1].get_x() && intersect.size() > 2)
			k++;
		line l(intersect[0], intersect[k]);
		l.draw(color);
	}
}

std::vector<int> polygon::scanline(int y) {
	
	int i = y;
	std::vector<int> intersect;
	for (int j = 0; j < points.size(); j++) {
		// Cek perpotongan

		// printf("%d, %d",points[j].get_x(), points[j].get_y());
		// printf(" %d, %d\n",points[(j + 1) % points.size()].get_x(), points[(j + 1) % points.size()].get_y());


		int ymax = std::max(points[j].get_y(), points[(j+1) % points.size()].get_y());
		int ymin = std::min(points[j].get_y(), points[(j+1) % points.size()].get_y());

		int xmax = std::max(points[j].get_x(), points[(j+1) % points.size()].get_x());
		int xmin = std::min(points[j].get_x(), points[(j+1) % points.size()].get_x());

		if (i >= ymin && i <= ymax){// && i != points[j].get_y()) {
			float deltaX = points[j].get_x() - points[(j+1)%points.size()].get_x();
			float deltaY = points[j].get_y() - points[(j+1)%points.size()].get_y();
			float gradien = 0;
			
			if (deltaX != 0 && deltaY != 0) {
				gradien = deltaX/deltaY;	
			}


			int intersect_y = i;
			int intersect_x;


			if (deltaX == 0) {
				intersect_x = xmin;
			} else {
				if (gradien < 0) {
					intersect_x = ((ymax - i) * (xmax - xmin) / (ymax - ymin)) + xmin;
				} else if (gradien > 0) {
					intersect_x = ((i - ymin) * (xmax - xmin) / (ymax - ymin)) + xmin;
				}
			}

			// printf("berpotongan di %d, %d\n", intersect_x, intersect_y);
			intersect.push_back(intersect_x);

		} else {
			// printf("tidak berpotongan\n");
		}
	}

	sort(intersect.begin(), intersect.end());
	
	int k = 1;
	if (intersect[0] == intersect[1] && intersect.size() > 2)
		k++;
	intersect[1] = intersect[k];
	return intersect;
}

void polygon::scale(float scale) {
	this->scale_factor = scale;
}

void polygon::rotate(float rotate) {
	this->rotate_factor = rotate;
}

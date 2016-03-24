/*
 * Husni Munaya / 13513022
 */

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
	std::vector<point> new_points = points;


	int x_origin = new_points[0].get_x() + x;
	int y_origin = new_points[0].get_y() + y;

	// Transformation
	for (int i = 0; i < new_points.size(); i++) {
		new_points[i] = new_points[i].move(x, y)
									 .scale(scale_factor, x_origin, y_origin)
									 .rotate(rotate_factor, x_origin, y_origin);
	}

	for (int i = 0; i < new_points.size(); i++) {
		line l(new_points[i], new_points[(i+1) % new_points.size()]);
		l.draw(color);
	}
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
	std::vector<point> new_points = points;
	int x_origin = new_points[0].get_x() + x;
	int y_origin = new_points[0].get_y() + y;

	// Transformation
	for (int i = 0; i < new_points.size(); i++) {
		new_points[i] = new_points[i].move(x, y)
									.scale(scale_factor, x_origin, y_origin)
									.rotate(rotate_factor, x_origin, y_origin);
	}

	std::vector<point> sorted_x_pts = new_points;
	sort(sorted_x_pts.begin(), sorted_x_pts.end(), point::cmp_x);
	std::vector<point> sorted_y_pts = new_points;
	sort(sorted_y_pts.begin(), sorted_y_pts.end(), point::cmp_y);

	int leftX = sorted_x_pts[0].get_x();
	int rightX = sorted_x_pts[sorted_x_pts.size() - 1].get_x();
	int topY = sorted_y_pts[0].get_y();
	int bottomY = sorted_y_pts[sorted_y_pts.size() - 1].get_y();

	for (int i = topY; i <= bottomY; i++) {
		std::vector<point> intersect;
		for (int j = 0; j < new_points.size(); j++) {
			// Cek perpotongan
			int ymax = std::max(new_points[j].get_y(), new_points[(j+1) % new_points.size()].get_y());
			int ymin = std::min(new_points[j].get_y(), new_points[(j+1) % new_points.size()].get_y());
			int xmax = std::max(new_points[j].get_x(), new_points[(j+1) % new_points.size()].get_x());
			int xmin = std::min(new_points[j].get_x(), new_points[(j+1) % new_points.size()].get_x());

			if (i >= ymin && i <= ymax){ // && i != new_points[j].get_y()) {
				float deltaX = new_points[j].get_x() - new_points[(j+1)%new_points.size()].get_x();
				float deltaY = new_points[j].get_y() - new_points[(j+1)%new_points.size()].get_y();
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

				point p(intersect_x, intersect_y);
				intersect.push_back(p);

			} else {
				// printf("tidak berpotongan\n");
			}
		}

		sort(intersect.begin(), intersect.end(), point::cmp_x);
		for (int k = 0; k < intersect.size() - 1; k++) {
			if (k % 2 == 0) {
				line l(intersect[k], intersect[k + 1]);
				l.draw(color);
			}	
		}
	}
}	

std::vector<int> polygon::scanline(int y) {
	
	int i = y;
	std::vector<int> intersect;
	for (int j = 0; j < points.size() - 1; j++) {

		int ymax = std::max(points[j].get_y(), points[(j+1) % points.size()].get_y());
		int ymin = std::min(points[j].get_y(), points[(j+1) % points.size()].get_y());
		int xmax = std::max(points[j].get_x(), points[(j+1) % points.size()].get_x());
		int xmin = std::min(points[j].get_x(), points[(j+1) % points.size()].get_x());

		if (i > ymin && i < ymax) {
			float deltaX = points[j].get_x() - points[(j+1)%points.size()].get_x();
			float deltaY = points[j].get_y() - points[(j+1)%points.size()].get_y();
			
			if (deltaX == 0) {
				intersect.push_back(points[j].get_x());
			}
			else if (deltaX/deltaY < 0) { 
				int intersect_x = ((ymax - i) * (xmax - xmin) / (ymax - ymin)) + xmin;
				intersect.push_back(intersect_x);
			} else if (deltaX/deltaY > 0) { 
				int intersect_x = ((i - ymin) * (xmax - xmin) / (ymax - ymin)) + xmin;
				intersect.push_back(intersect_x);
			} 		
		}
		else if (i == ymin && i == ymax) {
			if (points[j].get_x() > points[(j-1) % points.size()].get_x() && points[j].get_y() == points[(j-1) % points.size()].get_y()) {
				if (points[(j-2) % points.size()].get_y() < points[(j-1) % points.size()].get_y() && points[(j+1) % points.size()].get_y() < points[j].get_y()) {
					intersect.push_back(points[j].get_x());
				}
				else if (points[(j-2) % points.size()].get_y() > points[(j-1) % points.size()].get_y() && points[(j+1) % points.size()].get_y() > points[j].get_y()) {
					intersect.push_back(points[j].get_x());
				}
			}
			else if (points[j].get_x() < points[(j+1) % points.size()].get_x() && points[j].get_y() == points[(j+1) % points.size()].get_y()) {
				if (points[(j-1) % points.size()].get_y() < points[j].get_y() && points[(j+2) % points.size()].get_y() < points[(j+1) % points.size()].get_y()) {
					intersect.push_back(points[j].get_x());
				}
				else if (points[(j-1) % points.size()].get_y() > points[j].get_y() && points[(j+2) % points.size()].get_y() > points[(j+1) % points.size()].get_y()) {
					intersect.push_back(points[j].get_x());
				}
			}

			else if (points[j].get_x() > points[(j+1) % points.size()].get_x() && points[j].get_y() == points[(j+1) % points.size()].get_y()) {
				if (points[(j-1) % points.size()].get_y() < points[j].get_y() && points[(j+2) % points.size()].get_y() < points[(j+1) % points.size()].get_y()) {
					intersect.push_back(points[j].get_x());
				}
				else if (points[(j-1) % points.size()].get_y() > points[j].get_y() && points[(j+2) % points.size()].get_y() > points[(j+1) % points.size()].get_y()) {
					intersect.push_back(points[j].get_x());
				}
			}
			
			else {
				if (points[(j-1) % points.size()].get_y() < points[j].get_y() && points[(j+2) % points.size()].get_y() < points[(j+1) % points.size()].get_y()) {
					intersect.push_back(points[j].get_x());
				}
				else if (points[(j-1) % points.size()].get_y() > points[j].get_y() && points[(j+2) % points.size()].get_y() > points[(j+1) % points.size()].get_y()) {
					intersect.push_back(points[j].get_x());
				}
			}
		}
		else if (i == ymin) {

			if (i == points[j].get_y()) {
				if (points[(j-1) % points.size()].get_y() <= i) intersect.push_back(points[j].get_x());
			}
			// else {
			// 	if (points[j+2].get_y() < i) intersect.push_back(points[j+1].get_x());
			// }

		}
		else if (i == ymax) {

			if (i == points[j].get_y()) {
				if (points[(j-1) % points.size()].get_y() >= i) intersect.push_back(points[j].get_x());
			}
			/*else {
				if (points[j+2].get_y() > i) intersect.push_back(points[j+1].get_x());
			}*/

		}
	}

	sort(intersect.begin(), intersect.end());

	return intersect;
			
}

void polygon::scale(float scale) {
	this->scale_factor = scale;
}

void polygon::rotate(float rotate) {
	this->rotate_factor = rotate;
}

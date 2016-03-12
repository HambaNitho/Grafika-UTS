#include "bezier.hpp"
#include "canvas.hpp"

// Constructor
bezier::bezier() {
	point p1(0, 0);
	point p2(100, 0);
	points.push_back(p1);
	points.push_back(p2);
	tolerance = 2;
}
bezier::bezier(std::vector<point> points) {
	this->points = points;
	tolerance = 2;
}

// Setter and getter
std::vector<point> bezier::get_points() {
	return points;
}
bool bezier::is_surface() {
	return (points[0].get_x() == points[points.size()].get_x()) && (points[0].get_y() == points[points.size()].get_y());
}
void bezier::set_points(std::vector<point> points) {
	this->points = points;
}

// Transformasi
void bezier::add_point(point p, int position) {
	points.insert(points.begin() + position, p);
}
void bezier::delete_point(int position) {
	points.erase(points.begin() + position);
}
void bezier::move_point(int position, int delta_x, int delta_y, int delta_z) {
	points[position].move(delta_x, delta_y, delta_z);
}

int * bezier::getPascalTriangle (int n) {
	
	int * * arr = (int **)malloc(sizeof(int) * 2 * n);

	for (int j = 0 ; j < n; j++){
		arr[j] = (int *)malloc(sizeof(int) * 2 * n);		
	}
 
  // Iterate through every line and print integer(s) in it
  for (int line = 0; line < n; line++)
  {
    // Every line has number of integers equal to line number
    for (int i = 0; i <= line; i++)
    {
      // First and last values in every row are 1
      if (line == i || i == 0)
           arr[line][i] = 1;
      else // Other values are sum of values just above and left of above
           arr[line][i] = arr[line-1][i-1] + arr[line-1][i];
    }
  }
  return arr[n-1];
}

void bezier::recursive_bezier(std::vector<point> points, double t, uint32_t color) {
	
	int i, x, y;
	if (points.size() == 1) {
		canvas::get_instance()->draw_pixel(points[0].get_x(), points[0].get_y(), color);
		b_points.push_back(point(points[0].get_x(), points[0].get_y()));
	} else {
		std::vector<point> newpoints;
		for (i = 0; i < points.size()-1; i++) {
			x = (1 - t) * points[i].get_x() + t * points[i+1].get_x();
			y = (1 - t) * points[i].get_y() + t * points[i+1].get_y();
			newpoints.push_back(point(x, y));
			//b_points.push_back(point(x, y));
		}
		recursive_bezier(newpoints, t, color);
	}
}


void bezier::draw_bezier(std::vector<point> points, double ratio, uint32_t color)
{
	double t = ratio;
	b_points.push_back(points[0]);
	//recursive_bezier(points[0], points[1],
	//       points[2], points[3], color);
	while (t <= 1) {
		recursive_bezier(points, t, color);
		t += ratio;
	}
	//b_points.push_back(points[3]);
	for (int i = 0; i < b_points.size()-1; i++) {
		line l(b_points[i], b_points[(i+1) % b_points.size()]);
		l.draw();
	}
}
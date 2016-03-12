#include <iostream>
#include "gl.hpp"

using namespace std;

int main() {
	point p1(100,100);
	point p2(150,50);
	point p3(200,100);
	point p4(250,50);
	point p5(300,100);
	point p6(350,400);
	polygon p;
	p.add_point(p1);
	p.add_point(p2);
	p.add_point(p3);
	p.add_point(p4);
	p.add_point(p5);
	p.add_point(p6);
	list<polygon> polygons;
	list<uint32_t> colors;
	polygons.push_back(p);
	colors.push_back(0xffFFFFFF);
	fillo fl(polygons,colors);
	fl.fill_polygons();
    canvas::get_instance()->render();

  return 0;
}

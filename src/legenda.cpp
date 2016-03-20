#include "gl.hpp"

int main() {

	point position(0,0);
	
	polygon p;
	p.add_point(position.get_x(), position.get_y());
	p.add_point(position.get_x()+135, position.get_y());
	p.add_point(position.get_x()+135, position.get_y()+170);
	p.add_point(position.get_x(), position.get_y()+170);
	p.draw_stroke();

	font f;
	f.set_size(3);
	f.draw_string("LEGENDA", position.get_x()+5, position.get_y()+5);

	for (int i=0; i<5; i++) {
		polygon rect;
		rect.add_point(position.get_x()+40, position.get_y()+i*20+50);
		rect.add_point(position.get_x()+60, position.get_y()+i*20+50);
		rect.add_point(position.get_x()+60, position.get_y()+(i+1)*20+50);
		rect.add_point(position.get_x()+40, position.get_y()+(i+1)*20+50);
		rect.draw_stroke();
		switch (i) {
			case 0: rect.draw_fill(1,1,0x64A211); break;
			case 1: rect.draw_fill(1,1,0x8CB54F); break;
			case 2: rect.draw_fill(1,1,0xDFE53E); break;
			case 3: rect.draw_fill(1,1,0xDEB946); break;
			case 4: rect.draw_fill(1,1,0x0A32FF); break;
		}
	}

	f.set_size(1);
	f.draw_string("1000M", position.get_x()+70, position.get_y()+68);
	f.draw_string("500M", position.get_x()+70, position.get_y()+88);
	f.draw_string("100M", position.get_x()+70, position.get_y()+108);
	f.draw_string("0M", position.get_x()+70, position.get_y()+128);

	canvas::get_instance()->render();
}
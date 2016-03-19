#include "gl.hpp"


int main() {
	font f;


	f.draw_string("HUSNI", 0, 0);

	canvas::get_instance()->render();
}
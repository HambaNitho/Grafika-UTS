#include "gl.hpp"


int main() {
	font f;


	f.draw_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", 0, 0);

	canvas::get_instance()->render();
}
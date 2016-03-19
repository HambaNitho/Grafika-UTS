#include "gl.hpp"


int main() {
	font f;

	f.set_size(3);
	f.draw_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", 0, 0);

	canvas::get_instance()->render();
}
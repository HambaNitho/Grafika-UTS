#include "gl.hpp"

int screen_width = canvas::get_instance()->get_var_info().xres - 5;
int screen_height = canvas::get_instance()->get_var_info().yres - 5;
int vertical_split_xres = (screen_width / 4) * 3;
int margin_default = 10;

void draw_frame();

int main() {

  draw_frame();

  canvas::get_instance()->render();

  return 0;
}

void draw_frame() {
  // Minimap
  int minimap_top_left_x = vertical_split_xres + margin_default;
  int minimap_top_left_y = 100;
  int minimap_height = screen_height / 3;

  // Legend
  int legend_top_left_x = vertical_split_xres + margin_default;
  int legend_top_left_y = (screen_height / 4) * 3 - margin_default;
  int legend_height = screen_height / 4;

  polygon outer_frame;
  outer_frame.add_point(0, 0);
  outer_frame.add_point(screen_width, 0);
  outer_frame.add_point(screen_width, screen_height);
  outer_frame.add_point(0, screen_height);
  outer_frame.draw_stroke();

  line vertical_split_line(vertical_split_xres, 0, vertical_split_xres, screen_height);
  vertical_split_line.draw();

  font f;
  f.set_size((minimap_height / 5) / 7);
  f.draw_string("MINIMAP", vertical_split_xres + margin_default, margin_default);

  polygon minimap_frame;
  minimap_frame.add_point(minimap_top_left_x, minimap_top_left_y);
  minimap_frame.add_point(screen_width - margin_default, minimap_top_left_y);
  minimap_frame.add_point(screen_width - margin_default, minimap_top_left_y + minimap_height);
  minimap_frame.add_point(minimap_top_left_x, minimap_top_left_y + minimap_height);
  minimap_frame.draw_stroke();

  polygon legend_frame;
  legend_frame.add_point(legend_top_left_x, legend_top_left_y);
  legend_frame.add_point(screen_width - margin_default, legend_top_left_y);
  legend_frame.add_point(screen_width - margin_default, legend_top_left_y + legend_height);
  legend_frame.add_point(legend_top_left_x, legend_top_left_y + legend_height);
  legend_frame.draw_stroke();

  point legend_top_left_position(legend_top_left_x + margin_default, legend_top_left_y + margin_default);

	f.set_size((legend_height / 6) / 7);
	f.draw_string("LEGENDA", legend_top_left_position.get_x(), legend_top_left_position.get_y());

  int block_size = legend_height / 7;
	for (int i = 0; i < 5; i++) {
		polygon rect;
		rect.add_point(legend_top_left_position.get_x() + 40, legend_top_left_position.get_y() + i * block_size + 50);
		rect.add_point(legend_top_left_position.get_x() + 40 + block_size, legend_top_left_position.get_y() + i * block_size + 50);
		rect.add_point(legend_top_left_position.get_x() + 40 + block_size, legend_top_left_position.get_y() + (i + 1) * block_size + 50);
		rect.add_point(legend_top_left_position.get_x() + 40, legend_top_left_position.get_y() + (i + 1) * block_size + 50);
		rect.draw_stroke();
		switch (i) {
			case 0: rect.draw_fill(1, 1, 0x64A211); break;
			case 1: rect.draw_fill(1, 1, 0x8CB54F); break;
			case 2: rect.draw_fill(1, 1, 0xDFE53E); break;
			case 3: rect.draw_fill(1, 1, 0xDEB946); break;
			case 4: rect.draw_fill(1, 1, 0x0A32FF); break;
		}
	}

	f.set_size((legend_height / 10) / 7);
	f.draw_string("1000M", legend_top_left_position.get_x() + 40 + block_size + margin_default, legend_top_left_position.get_y() + (2 * block_size));
	f.draw_string("500M", legend_top_left_position.get_x() + 40 + block_size + margin_default, legend_top_left_position.get_y() + (3 * block_size));
	f.draw_string("100M", legend_top_left_position.get_x() + 40 + block_size + margin_default, legend_top_left_position.get_y() + (4 * block_size));
	f.draw_string("0M", legend_top_left_position.get_x() + 40 + block_size + margin_default, legend_top_left_position.get_y() + (5 * block_size));

}

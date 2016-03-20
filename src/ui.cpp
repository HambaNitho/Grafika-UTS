#include "gl.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <vector>
#include "map.hpp"

using namespace std;

int screen_width = canvas::get_instance()->get_var_info().xres - 5;
int screen_height = canvas::get_instance()->get_var_info().yres - 5;
int vertical_split_xres = (screen_width / 4) * 3;
int margin_default = 10;

// Minimap
int minimap_top_left_x = vertical_split_xres + margin_default;
int minimap_top_left_y = (10 * margin_default);
int minimap_height = screen_height / 3;

// Instruction
int instruction_top_left_x = vertical_split_xres + (10 * margin_default);
int instruction_top_left_y = (screen_height / 4) * 2 - (5 * margin_default);

// Legend
int legend_top_left_x = vertical_split_xres + margin_default;
int legend_top_left_y = (screen_height / 4) * 3 - margin_default;
int legend_height = screen_height / 4;

void draw_frame();

int main() {

  initscr();
  noecho();
  timeout(-1);
  int c;

  point view_pos(0,0);
  point clipping_pos(vertical_split_xres + margin_default, 10 * margin_default);
  view v(screen_height, vertical_split_xres, view_pos, clipping_pos, 0.1);

  map m;
  m.set_scale(2.5);
  m.draw_map(minimap_top_left_x, minimap_top_left_y);

  vector<polygon> maps = m.get_map_polygons();

  while (true) {
    draw_frame();

    std::list<polygon> polygons;
    std::list<uint32_t> colors;

    for (int i = 0; i < maps.size(); i++) {
      maps[i].draw_stroke();
      v.draw(maps[i]);
      polygons.push_back(maps[i]);
      colors.push_back(0xDEB946);
    }

    fillo fl(polygons, colors);
    fl.fill_polygons();

    canvas::get_instance()->render();

    c = getch();
    switch(c) {
      case 110:       // key m
        v.zoom(-0.01, (10 * margin_default)+(screen_height / 3), screen_width - margin_default );
        break;
      case 109:       // key m
        v.zoom(0.01, (10 * margin_default)+(screen_height / 3), screen_width - margin_default );
        break;
      case 65:       // key up
        if (v.get_clip_pos().get_y() > (10 * margin_default))
          v.move_clip(0, -4);
        break;
      case 66:       // key down
        if (v.get_clip_pos().get_y() + v.get_clip_height() + 4 < (10 * margin_default)+(screen_height / 3))
          v.move_clip(0, 4);
        break;
      case 67:       // key right
        if (v.get_clip_pos().get_x() + v.get_clip_width() + 4 < screen_width - margin_default)
          v.move_clip(4, 0);
        break;
      case 68:       // key left
        if (v.get_clip_pos().get_x() > vertical_split_xres + margin_default)
          v.move_clip(-4, 0);
        break;
      default:
        v.move_clip(0, 0);
        break;
    }

    canvas::get_instance()->clear();
  }

  canvas::get_instance()->render();

  return 0;
}

void draw_frame() {

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

  polygon arrow;
  arrow.add_point(5, 0);
  arrow.add_point(10, 7);
  arrow.add_point(7, 7);
  arrow.add_point(7, 14);
  arrow.add_point(3, 14);
  arrow.add_point(3, 7);
  arrow.add_point(0, 7);

  arrow.scale(1.4);
  arrow.draw_stroke(instruction_top_left_x - (2 * margin_default), instruction_top_left_y);
  arrow.rotate(3.14);
  arrow.draw_stroke(instruction_top_left_x - (2 * margin_default), instruction_top_left_y + (minimap_height / 16) + (3 * margin_default));
  arrow.rotate(-3.14 / 2);
  arrow.draw_stroke(instruction_top_left_x - margin_default, instruction_top_left_y + (2 * (minimap_height / 16)) + (3 * margin_default));
  arrow.rotate(3.14 / 2);
  arrow.draw_stroke(instruction_top_left_x - (3 * margin_default), instruction_top_left_y + (3 * (minimap_height / 16)) + (4 * margin_default));

  f.set_size((minimap_height / 16) / 7);
  f.draw_string("SCROLL UP", instruction_top_left_x, instruction_top_left_y);
  f.draw_string("SCROLL DOWN", instruction_top_left_x, instruction_top_left_y + (minimap_height / 16) + margin_default);
  f.draw_string("SCROLL RIGHT", instruction_top_left_x, instruction_top_left_y +  (2 * (minimap_height / 16)) + (2 * margin_default));
  f.draw_string("SCROLL LEFT", instruction_top_left_x, instruction_top_left_y + (3 * (minimap_height / 16)) + (3 * margin_default));
  f.draw_char('N', instruction_top_left_x - (3 * margin_default), instruction_top_left_y + (4 * (minimap_height / 16)) + (4 * margin_default));
  f.draw_string("ZOOM IN", instruction_top_left_x, instruction_top_left_y + (4 * (minimap_height / 16)) + (4 * margin_default));
  f.draw_char('M', instruction_top_left_x - (3 * margin_default), instruction_top_left_y + (5 * (minimap_height / 16)) + (5 * margin_default));
  f.draw_string("ZOOM OUT", instruction_top_left_x, instruction_top_left_y + (5 * (minimap_height / 16)) + (5 * margin_default));
  f.draw_char('J', instruction_top_left_x - (3 * margin_default), instruction_top_left_y + (6 * (minimap_height / 16)) + (6 * margin_default));
  f.draw_string("ROTATE LEFT", instruction_top_left_x, instruction_top_left_y + (6 * (minimap_height / 16)) + (6 * margin_default));
  f.draw_char('K', instruction_top_left_x - (3 * margin_default), instruction_top_left_y + (7 * (minimap_height / 16)) + (7 * margin_default));
  f.draw_string("ROTATE RIGHT", instruction_top_left_x, instruction_top_left_y + (7 * (minimap_height / 16)) + (7 * margin_default));


  polygon legend_frame;
  legend_frame.add_point(legend_top_left_x, legend_top_left_y);
  legend_frame.add_point(screen_width - margin_default, legend_top_left_y);
  legend_frame.add_point(screen_width - margin_default, legend_top_left_y + legend_height);
  legend_frame.add_point(legend_top_left_x, legend_top_left_y + legend_height);
  legend_frame.draw_stroke();

  point legend_top_left_position(legend_top_left_x + margin_default, legend_top_left_y + margin_default);

	f.set_size((legend_height / 6) / 7);
	f.draw_string("LEGENDA", legend_top_left_position.get_x(), legend_top_left_position.get_y());

  int block_size = legend_height / 8;
	for (int i = 0; i < 5; i++) {
		polygon rect;
		rect.add_point(legend_top_left_position.get_x() + 40, legend_top_left_position.get_y() + (i + 2) * block_size);
		rect.add_point(legend_top_left_position.get_x() + 40 + block_size, legend_top_left_position.get_y() + (i + 2) * block_size);
		rect.add_point(legend_top_left_position.get_x() + 40 + block_size, legend_top_left_position.get_y() + (i + 3) * block_size);
		rect.add_point(legend_top_left_position.get_x() + 40, legend_top_left_position.get_y() + (i + 3) * block_size);
		rect.draw_stroke();
		switch (i) {
			case 0: rect.draw_fill(1, 1, 0xDEB946); break;
      case 1: rect.draw_fill(1, 1, 0xDFE53E); break;
			case 2: rect.draw_fill(1, 1, 0x8CB54F); break;
			case 3: rect.draw_fill(1, 1, 0x64A211); break;
			case 4: rect.draw_fill(1, 1, 0x0A32FF); break;
		}
	}

	f.set_size((legend_height / 12) / 7);
	f.draw_string("1000M", legend_top_left_position.get_x() + 40 + block_size + margin_default,
    legend_top_left_position.get_y() + (2 * block_size) + (2 * margin_default));
	f.draw_string("500M", legend_top_left_position.get_x() + 40 + block_size + margin_default,
    legend_top_left_position.get_y() + (3 * block_size) + (2 * margin_default));
	f.draw_string("100M", legend_top_left_position.get_x() + 40 + block_size + margin_default,
    legend_top_left_position.get_y() + (4 * block_size) + (2 * margin_default));
	f.draw_string("0M", legend_top_left_position.get_x() + 40 + block_size + margin_default,
    legend_top_left_position.get_y() + (5 * block_size) + (2 * margin_default));

}

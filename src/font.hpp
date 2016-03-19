/*
 * Husni Munaya / 13513022
 */

#ifndef _FONT_H
#define _FONT_H

#include <iostream>
#include "canvas.hpp"


class font {

public:
	font();
	void set_size(int font_size);
	void draw_char(char c, int x, int y, uint32_t color = 0xffffffff);
	void draw_string(std::string s, int x, int y, uint32_t color = 0xffffffff);

private:
	int font_size;
	int font_width;
	int font_height;

	void copy_matrix(int M1[7][5], int M2[7][5]);
	void draw_block(int x, int y, uint32_t color);
};

#endif
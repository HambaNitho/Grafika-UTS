#include "font.hpp"
#include <stdio.h>

font::font() {
	font_size = 2;
	font_width = 5;
	font_height = 7;
}

void font::set_size(int font_size) {
	this->font_size = font_size;
}

void font::copy_matrix(int M1[7][5], int M2[7][5]) {
    for (int i = 0; i < font_height; i++) {
        for (int j = 0; j < font_width; j++) {
            M2[i][j] = M1[i][j];
        }
    }
}

void font::draw_block(int x, int y, uint32_t color) {
	for (int i = 0; i < font_size; i++)
		for (int j = 0; j < font_size; j++)
			canvas::get_instance()->draw_pixel(i + x, j + y, color);
}

void font::draw_char(char c, int x, int y, uint32_t color) {
	int coordinate[7][5];

	int coordinateA[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1}
	};

	int coordinateB[7][5] = {
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 0}
	};

	int coordinateI[7][5] = {
	    {0, 1, 1, 1, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 1, 1, 1, 0}
	};

	int coordinateT[7][5] = {
	    {1, 1, 1, 1, 1},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0}
	};

	int coordinateN[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 1, 0, 0, 1},
	    {1, 0, 1, 0, 1},
	    {1, 0, 0, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1}
	};

	int coordinateR[7][5] = {
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1}
	};

	int coordinateH[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1}
	};

	int coordinateM[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 1, 0, 1, 1},
	    {1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1}
	};

	int coordinateW[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 1, 0, 1},
	    {1, 1, 0, 1, 1},
	    {1, 0, 0, 0, 1}
	};

	int coordinateO[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	int coordinateC[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	int coordinateS[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 0},
	    {0, 1, 1, 1, 0},
	    {0, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	int coordinateY[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 0, 1, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0}
	};

	int coordinateU[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	switch(c) {
	    case 'A':
	        copy_matrix(coordinateA, coordinate);
	        break;
	    case 'B':
	        copy_matrix(coordinateB, coordinate);
	        break;
	    case 'C':
	        copy_matrix(coordinateC, coordinate);
	        break;
	    case 'H':
	        copy_matrix(coordinateH, coordinate);
	        break;
	    case 'I':
	        copy_matrix(coordinateI, coordinate);
	        break;
	    case 'M':
	        copy_matrix(coordinateM, coordinate);
	        break;
	    case 'N':
	        copy_matrix(coordinateN, coordinate);
	        break;
	    case 'O':
	        copy_matrix(coordinateO, coordinate);
	        break;
	    case 'R':
	        copy_matrix(coordinateR, coordinate);
	        break;
	    case 'S':
	        copy_matrix(coordinateS, coordinate);
	        break;
	    case 'T':
	        copy_matrix(coordinateT, coordinate);
	        break;
	    case 'U':
	        copy_matrix(coordinateU, coordinate);
	        break;
	    case 'W': 
	        copy_matrix(coordinateW, coordinate);
	        break;
	    case 'Y': 
	        copy_matrix(coordinateY, coordinate);
	        break;
	}

	for (int i = 0; i < font_height; i++) {
		for (int j = 0; j < font_width; j++) {
			if (coordinate[i][j] != 0)
			draw_block(j * font_size + x, i * font_size + y, color);
		}
	}
}


void font::draw_string(std::string s, int x, int y, uint32_t color) {
	for (int i = 0; i < s.length(); i++) {
		draw_char(s[i], x + i*(font_size* (font_width + 1)), y);
	}
}




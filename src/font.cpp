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
	int coordinate[7][5] = {
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

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

	int coordinateC[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	int coordinateD[7][5] = {
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 0}
	};

	int coordinateE[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1}
	};

	int coordinateF[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0}
	};

	int coordinateG[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1}
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


	int coordinateI[7][5] = {
	    {0, 1, 1, 1, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 1, 1, 1, 0}
	};

	int coordinateJ[7][5] = {
	    {1, 1, 1, 1, 0},
	    {0, 0, 0, 1, 0},
	    {0, 0, 0, 1, 0},
	    {0, 0, 0, 1, 0},
	    {0, 0, 0, 1, 0},
	    {1, 0, 0, 1, 0},
	    {0, 1, 1, 0, 0}
	};

	int coordinateK[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 1, 0},
	    {1, 0, 1, 0, 0},
	    {1, 1, 0, 0, 0},
	    {1, 0, 1, 0, 0},
	    {1, 0, 0, 1, 0},
	    {1, 0, 0, 0, 1}
	};

	int coordinateL[7][5] = {
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1}
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

	int coordinateN[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 1, 0, 0, 1},
	    {1, 0, 1, 0, 1},
	    {1, 0, 0, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
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

	int coordinateP[7][5]= {
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0}
	};

	int coordinateQ[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 1, 0, 1},
	    {1, 0, 0, 1, 1},
	    {1, 1, 1, 1, 1}
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

	int coordinateS[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 0},
	    {0, 1, 1, 1, 0},
	    {0, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
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


	int coordinateU[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	int coordinateV[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 0, 1, 0},
	    {0, 1, 0, 1, 0},
	    {0, 1, 0, 1, 0},
	    {0, 0, 1, 0, 0}
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

	int coordinateX[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 0, 1, 0},
	    {0, 0, 1, 0, 0},
	    {0, 1, 0, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1}
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

	int coordinateZ[7][5] = {
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 1, 0},
	    {0, 0, 1, 0, 0},
	    {0, 1, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1}
	};

	int coordinate0[7][5] = {
	    {0, 1, 1, 1, 0},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {0, 1, 1, 1, 0}
	};

	int coordinate1[7][5] = {
	    {0, 1, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 0, 1, 0, 0},
	    {0, 1, 1, 1, 0}
	};

	int coordinate2[7][5] = {
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1}
	};

	int coordinate3[7][5] = {
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1}
	};

	int coordinate4[7][5] = {
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1}
	};

	int coordinate5[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1}
	};

	int coordinate6[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0},
	    {1, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1}
	};

	int coordinate7[7][5] = {
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1}
	};

	int coordinate8[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1}
	};

	int coordinate9[7][5] = {
	    {1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 1},
	    {1, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1},
	    {0, 0, 0, 0, 1},
	    {0, 0, 0, 0, 1},
	    {1, 1, 1, 1, 1}
	};


	int coordinatePlus[7][5] = {
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	};

	int coordinateMin[7][5] = {
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
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
	    case 'D':
	        copy_matrix(coordinateD, coordinate);
	        break;
	    case 'E':
	        copy_matrix(coordinateE, coordinate);
	        break;
	    case 'F':
	        copy_matrix(coordinateF, coordinate);
	        break;
	    case 'G':
	        copy_matrix(coordinateG, coordinate);
	        break;
	    case 'H':
	        copy_matrix(coordinateH, coordinate);
	        break;
	    case 'I':
	        copy_matrix(coordinateI, coordinate);
	        break;
	    case 'J':
	        copy_matrix(coordinateJ, coordinate);
	        break;
	     case 'K':
	        copy_matrix(coordinateK, coordinate);
	        break;
	    case 'L':
	        copy_matrix(coordinateL, coordinate);
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
	    case 'P':
	        copy_matrix(coordinateP, coordinate);
	        break;
	    case 'Q':
	        copy_matrix(coordinateQ, coordinate);
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
	    case 'V':
	        copy_matrix(coordinateV, coordinate);
	        break;
	    case 'W':
	        copy_matrix(coordinateW, coordinate);
	        break;
	    case 'X':
	        copy_matrix(coordinateX, coordinate);
	        break;
	    case 'Y':
	        copy_matrix(coordinateY, coordinate);
	        break;
	    case 'Z':
	        copy_matrix(coordinateZ, coordinate);
	        break;
	    case '0':
	        copy_matrix(coordinate0, coordinate);
	        break;
	    case '1':
	        copy_matrix(coordinate1, coordinate);
	        break;
	    case '2':
	        copy_matrix(coordinate2, coordinate);
	        break;
	    case '3':
	        copy_matrix(coordinate3, coordinate);
	        break;
	    case '4':
	        copy_matrix(coordinate4, coordinate);
	        break;
	    case '5':
	        copy_matrix(coordinate5, coordinate);
	        break;
	    case '6':
	        copy_matrix(coordinate6, coordinate);
	        break;
	    case '7':
	        copy_matrix(coordinate7, coordinate);
	        break;
	    case '8':
	        copy_matrix(coordinate8, coordinate);
	        break;
	    case '9':
	        copy_matrix(coordinate9, coordinate);
	        break;
	    case '+':
	        copy_matrix(coordinatePlus, coordinate);
	        break;
	    case '-':
	        copy_matrix(coordinateMin, coordinate);
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

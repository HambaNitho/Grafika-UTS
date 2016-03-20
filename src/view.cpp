#include "view.hpp"
#include "polygon.hpp"

/*
 * 
 * Constructor
 *
 */

view::view() {
	this->height = 0;
	this->width = 0;
	this->position.set_coord(0,0);
	this->clip_position.set_coord(0,0);
	this->window_height = canvas::get_instance()->get_var_info().yres;
	this->window_width = canvas::get_instance()->get_var_info().xres;
	set_ratio();
}

view::view(int height, int width, point position, point clip_position, float scale) {
	this->height = height;
	this->width = width;
	this->position.set_coord(position.get_x(),position.get_y());
	this->clip_position.set_coord(clip_position.get_x(),clip_position.get_y());
	this->window_height = height * scale;
	this->window_width = width * scale;
	set_ratio();
}

/*
 * 
 * Setter and Getter
 *
 */

int view::get_width() const {
	return width;
}

int view::get_height()const {
	return height;
}

point view::get_position() const {
	return position;
}

point view::get_clip_pos() const {
	return clip_position;
}

int view::get_clip_height() const {
	return window_height;
}

int view::get_clip_width() const {
	return window_width;
}

void view::set_width(int width) {
	this->width = width;
}

void view::set_height(int height) {
	this->height = height;
}

void view::set_position(int x, int y) {
	this->position.set_coord(x,y);
}

point view::clipping(line Line, int l, int r, int b, int t, int idx) {
	int new_x, new_y;
	int x1, x2, y1, y2;

	x1 = Line.get_first_point().get_x();
	x2 = Line.get_last_point().get_x();
	y1 = Line.get_first_point().get_y();
	y2 = Line.get_last_point().get_y();

	if (l==1 && r==0 && b==0 && t==1) {
		// perpotongannya ada di left atau top
		// anggap di left
		new_x = position.get_x();
		float temp = ((float)(y2 - y1)/(x2 - x1)) * (new_x - x1) + y1;
		new_y = (int) temp;
		if (new_y<position.get_y() || new_y>position.get_y()+height) {
			// ternyata ada di top
			new_y = position.get_y();
			temp = ( (float) (x2 - x1) / (y2 - y1) ) * (new_y - y1) + x1;
			new_x = (int) temp;
		}
	}
	else if (l==0 && r==0 && b==0 && t==1) {
		// perpotongannya ada di top
		new_y = position.get_y();
		float temp = ( (float) (x2 - x1) / (y2 - y1) ) * (new_y - y1) + x1;
		new_x = (int) temp;
	}
	else if (l==0 && r==1 && b==0 && t==1) {
		// perpotongannya ada di right atau top
		// anggap di right
		new_x = position.get_x() + width;
		float temp = ( (float)(y2 - y1) / (x2 - x1) ) * (new_x - x1) + y1;
		new_y = (int) temp;
		if (new_y<position.get_y() || new_y>position.get_y()+height) {
			// ternyata ada di top
			new_y = position.get_y();
			float temp = ( (float) (x2 - x1) / (y2 - y1) ) * (new_y - y1) + x1;
			new_x = (int) temp;
		}
	}
	else if (l==1 && r==0 && b==0 && t==0) {
		// perpotongannya ada di left
		new_x = position.get_x();
		float temp = ((float)(y2 - y1)/(x2 - x1)) * (new_x - x1) + y1;
		new_y = (int) temp;
	}
	else if (l==0 && r==1 && b==0 && t==0) {
		// perpotongannya ada di right
		new_x = position.get_x() + width;
		float temp = ( (float)(y2 - y1) / (x2 - x1) ) * (new_x - x1) + y1;
		new_y = (int) temp;
	}
	else if (l==1 && r==0 && b==1 && t==0) {
		// perpotongannya ada di left atau bottom
		// anggap di left
		new_x = position.get_x();
		float temp = ((float)(y2 - y1)/(x2 - x1)) * (new_x - x1) + y1;
		new_y = (int) temp;
		if (new_y<position.get_y() || new_y>position.get_y()+height) {
			// ternyata ada di bottom
			new_y = position.get_y() + height;
			temp = ((float)(x2 - x1)/(y2 - y1)) * (new_y - y1) + x1;
			new_x = (int) temp;
		}
	}
	else if (l==0 && r==0 && b==1 && t==0) {
		// perpotongannya ada di bottom
		new_y = position.get_y() + height;
		float temp = ((float)(x2 - x1)/(y2 - y1)) * (new_y - y1) + x1;
		new_x = (int) temp;
	}
	else if (l==0 && r==1 && b==1 && t==0) {
		// perpotongannya ada di right atau bottom
		// anggap di right
		new_x = position.get_x() + width;
		float temp = ( (float)(y2 - y1) / (x2 - x1) ) * (new_x - x1) + y1;
		new_y = (int) temp;
		if (new_y<position.get_y() || new_y>position.get_y()+height) {
			// ternyata ada di bottom
			new_y = position.get_y() + height;
			temp = ((float)(x2 - x1)/(y2 - y1)) * (new_y - y1) + x1;
			new_x = (int) temp;
		}
	}
	else {
		if (idx==1)
			return Line.get_first_point();
		else
			return Line.get_last_point();
	}
	point new_point(new_x,new_y);
	return new_point;
}

void view::draw(polygon p) {
	
	// Draw clipped area
	int cx1 = clip_position.get_x();
	int cy1 = clip_position.get_y();
	int cx2 = cx1 + window_width;
	int cy2 = cy1 + window_height;

	line cl1(cx1, cy1, cx2, cy1);
	line cl2(cx2, cy1, cx2, cy2);
	line cl3(cx2, cy2, cx1, cy2);
	line cl4(cx1, cy2, cx1, cy1);

	cl1.draw(0xffff0000); cl2.draw(0xffff0000); cl3.draw(0xffff0000); cl4.draw(0xffff0000);

	std::vector<point> points = p.get_points();
	
	for (int i = 0; i < points.size(); i++) {
		
		point p1 = points[i];
		point p2 = points[(i + 1) % points.size()];


		int x1 = p1.get_x();
		int y1 = p1.get_y();
		int x2 = p2.get_x();
		int y2 = p2.get_y();

		fb_var_screeninfo vinfo = canvas::get_instance()->get_var_info();


		// Get view-clipped ratio, save scale instead?
		float ratio_x = (float)this->width /  this->window_width;
		float ratio_y = (float)this->height / this->window_height;
		
		//view.y = (map.y - view.project_position_y) * view.ratio_y + view.position_y;
		//view.x = (map.x - view.project_position_x) * view.ratio_x + view.position_x;
		
		// ______________________________________________________
		//|                                                      |
		//| ________________                                     |
		//||                |                                    |
		//||   clipped      |                                    |        _____________________
		//||                |                                    |       |                     |
		//||________________|     MAP                            |       |                     |
		//|                                                      |       |        view         |
		//|                                                      |       |                     |
		//|                                                      |       |                     |
		//|                                                      |       |_____________________|
		//|                                                      |
		//|______________________________________________________|

		int v1x = (x1 - clip_position.get_x()) * ratio_x + position.get_x();
		int v1y = (y1 - clip_position.get_y()) * ratio_y + position.get_y();

		int v2x = (x2 - clip_position.get_x()) * ratio_x + position.get_x();
		int v2y = (y2 - clip_position.get_y()) * ratio_y + position.get_y();

		line new_l(v1x, v1y, v2x, v2y);

		int l1,r1,b1,t1,l2,r2,b2,t2;

		if (v1x >= position.get_x()) l1=0; else l1=1;
		if (v1x > position.get_x()+width) r1=1; else r1=0; 
		if (v1y > position.get_y()+height) b1=1; else b1=0;
		if (v1y >= position.get_y()) t1=0; else t1=1;

		if (v2x >= position.get_x()) l2=0; else l2=1;
		if (v2x > position.get_x()+width) r2=1; else r2=0; 
		if (v2y > position.get_y()+height) b2=1; else b2=0;
		if (v2y >= position.get_y()) t2=0; else t2=1;

		if (l1==0 && r1==0 && b1==0 && t1==0 && l2==0 && r2==0 && b2==0 && t2==0) {
			// garis visible
			new_l.draw();
		}
		else {
			int logicbit[4];
			logicbit[0] = l1 && l2;
			logicbit[1] = r1 && r2;
			logicbit[2] = b1 && b2;
			logicbit[3] = t1 && t2;

			if ((logicbit[0] || logicbit[1] || logicbit[2] || logicbit[3]) == 0) {
				// clipping point
				point p1, p2;
				p1 = clipping (new_l, l1, r1, b1, t1, 1);
				p2 = clipping (new_l, l2, r2, b2, t2, 2);
				line clipped_line(p1, p2);
				clipped_line.draw();
			}
		}

	}
}

void view::move_clip(int delta_x, int delta_y) {
	if (clip_position.get_x() + delta_x < clip_position.get_x() + window_width)
		clip_position.set_x(clip_position.get_x() + delta_x);
	if (clip_position.get_y() + delta_y < clip_position.get_y() + window_height)
		clip_position.set_y(clip_position.get_y() + delta_y);
}

void view::zoom(float scale) {
	this->window_height += height_ratio*scale;
	this->window_width += width_ratio*scale;
}

void view::set_ratio() {
	
	int a,b,c;
	a = width;
	b = height;
	while ( a != 0 ) {
	   c = a; a = b%a;  b = c;
	}
	width_ratio = width/b;
	height_ratio = height/b;
}
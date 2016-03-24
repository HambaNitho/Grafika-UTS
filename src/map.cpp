#include "map.hpp"

map::map(){
	scale = 1;
}

void map::map_add_point(std::string filename, polygon &p, int x_offset, int y_offset){
    int size = scale, a, b;
    std::string path = "map/" + filename + ".txt";
    std::ifstream map(path.c_str());
    while (map >> a >> b){
        p.add_point(a*size + x_offset, b*size + y_offset);
    }
    map.close();
}

void map::map_add_point_bezier(std::string filename, std::vector<point> &p, int x_offset, int y_offset){
    int size = scale, a, b;
    std::string path = "map/" + filename + ".txt";
    std::ifstream map(path.c_str());
    while (map >> a >> b){
        p.push_back(point(a*size + x_offset,b*size + y_offset));
    }
    map.close();
}

void map::draw_map(int x_offset, int y_offset){
	/* Polygon Section */
    polygon bali, nusapenida, ijo, kuning, oren1, oren2, oren3, oren4, oren5, oren6;

    map_add_point("kuning", kuning, x_offset, y_offset);
    // kuning.draw_stroke();

    map_add_point("oren1", oren1, x_offset, y_offset);
    // oren1.draw_stroke();

    map_add_point("oren2", oren2, x_offset, y_offset);
    // oren2.draw_stroke();

    map_add_point("oren3", oren3, x_offset, y_offset);
    // oren3.draw_stroke();

    map_add_point("oren4", oren4, x_offset, y_offset);
    // oren4.draw_stroke();

    map_add_point("oren5", oren5, x_offset, y_offset);
    // oren5.draw_stroke();
    
    map_add_point("oren6", oren6, x_offset, y_offset);
    // oren6.draw_stroke();

    map_add_point("bali", bali, x_offset, y_offset);
    // bali.draw_stroke();

/*    map_add_point("ijo", ijo);
    ijo.draw_stroke();*/

    map_add_point("nusapenida", nusapenida, x_offset, y_offset);
    // nusapenida.draw_stroke();

    map_polygons.push_back(bali);
    map_polygons.push_back(kuning);
    map_polygons.push_back(oren1);
    map_polygons.push_back(oren2);
    map_polygons.push_back(oren3);
    map_polygons.push_back(oren4);
    map_polygons.push_back(oren5);
    map_polygons.push_back(oren6);
    map_polygons.push_back(nusapenida);


    /* Bezier Section */
    std::vector<point> ijo_layer;

    map_add_point_bezier("ijo_bezier", ijo_layer, x_offset, y_offset);
    bezier ijo_bezier(ijo_layer);
    double t = 0.01f;
    // ijo_bezier.make_bezier(ijo_bezier.get_points(), t);
    // ijo_bezier.draw_bezier(0xffffffff);


    canvas::get_instance()->render();
}

std::vector<polygon> map::get_map_polygons() {
    return map_polygons;
}

void map::set_scale(int n_scale){
	scale = n_scale;  
}

// int main(){
// 	map m;

// 	m.set_scale(5);
// 	m.draw_map();
//     std::vector<polygon> maps = m.get_map_polygons();

// 	return 0;
// }
#include <iostream>
#include "gl.hpp"

using namespace std;

int main() {

    face Face;

    Face.draw_face();
    canvas::get_instance()->render();
    
    sleep(2);
    canvas::get_instance()->clear();

    Face.reset();
    Face.smile();
    Face.draw_face();
    canvas::get_instance()->render();

    sleep(2);
    canvas::get_instance()->clear();

    Face.reset();
    Face.sad();
    Face.draw_face();
    canvas::get_instance()->render();

    sleep(2);
    canvas::get_instance()->clear();

    Face.reset();
    Face.shock();
    Face.draw_face();
    canvas::get_instance()->render();

  return 0;
}

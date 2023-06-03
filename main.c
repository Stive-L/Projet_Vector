
#include <stdio.h>
#include "shapes.c"
#include "area.c"


int main() {

    Area * draw_zone = create_area(12,14); // hauteur, largeur
    Shape * shape1 = create_line_shape(5,5,10,10);
    //Shape * shape1 = create_line_shape(3,9,13,5);
    Shape * shape2 = create_cercle_shape(5,5,4);
    add_shape_to_area(draw_zone,shape1);
    add_shape_to_area(draw_zone,shape2);
    draw_area(draw_zone);
    print_area(draw_zone);
    /*
    erase_area(draw_zone);
    draw_area(draw_zone);
    print_area(draw_zone);
    delete_area(draw_zone);
     */

    return 0;
}

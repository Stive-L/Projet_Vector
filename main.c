
#include <stdio.h>
#include "shapes.c"
#include "area.c"


int main() {

    Area * draw_zone = create_area(25,25);
    //Shape *shape1 = create_square_shape(10,10,5);
    //Shape * shape1 = create_rectangle_shape(2,2,3,5);
    int n = 3;
    int tab[3][2] = {{1,3},
                     {4,2},
                     {6,5}};
    int **tab_2 = malloc(n*sizeof(int*));
    for (int i = 0; i< n ; i++){
        tab_2[i] = tab[i];
    }
    Shape * shape1 = create_polygon_shape(tab_2,2);
    add_shape_to_area(draw_zone,shape1);
    draw_area(draw_zone);
    print_area(draw_zone);
    /*
    Area * draw_zone = create_area(12,14); // hauteur, largeur
    Shape * shape1 = create_line_shape(5,5,10,10);
    Shape * shape1 = create_line_shape(3,9,13,5);
    Shape * shape2 = create_cercle_shape(5,5,4);Q
    add_shape_to_area(draw_zone,shape1);
    add_shape_to_area(draw_zone,shape2);
    draw_area(draw_zone);
    print_area(draw_zone);

    erase_area(draw_zone);
    draw_area(draw_zone);
    print_area(draw_zone);
    delete_area(draw_zone);
     */


    return 0;
}

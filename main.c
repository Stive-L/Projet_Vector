//
// Created by Stive on 19/05/2023.
//
#include <stdio.h>
#include "shapes.c"
#include "area.c"
#include "commandes.c"

int main() {

    Area * area = create_area(20,20);
    int exit = 0;
    while (exit == 0){
        Command * cmd = create_command();
        read_from_stdin(cmd);
        exit = read_exec_command(cmd, area);
        if (exit == 1){
            free_cmd(cmd);
        }
    }
    /* Partie débug/Test
    Area * draw_zone = create_area(25,25);
    Shape *shape1 = create_square_shape(10,10,5);
    //Shape * shape1 = create_rectangle_shape(2,2,3,5);

    //int points_list[] = {1, 2, 3, 4, 5, 6};
    //Shape * shape1 = create_polygon_shape(points_list,  6);
    //print_polygon(shape1->ptrShape);
    //delete_polygon(shape1->ptrShape);

    add_shape_to_area(draw_zone,shape1);
    draw_area(draw_zone);
    print_area(draw_zone);
    //Area * draw_zone = create_area(12,14); // hauteur, largeur
    //Shape * shape1 = create_line_shape(5,5,10,10);
    //Shape * shape1 = create_line_shape(3,9,13,5);
    //Shape * shape2 = create_circle_shape(5,5,4);
    //add_shape_to_area(draw_zone,shape1);
    //add_shape_to_area(draw_zone,shape2);
    //draw_area(draw_zone);
    //print_area(draw_zone);
    erase_area(draw_zone);
    draw_area(draw_zone);
    print_area(draw_zone);
    delete_area(draw_zone);
     */
    return 0;
}

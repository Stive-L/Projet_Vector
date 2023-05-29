//
// Created by Stive on 29/05/2023.
//

#include "area.h"
#include <stdlib.h>
#include <stdio.h>

// Area
Area* create_area(unsigned int width, unsigned int height){
    Area * nouv_area = malloc(sizeof(Area));
    nouv_area ->width = width;
    nouv_area -> height = height;
    nouv_area -> MAT = malloc(height * sizeof(int *));
    for (int i = 0; i < height;i++){
        nouv_area-> MAT[i] = malloc(width * sizeof(int));
    }
    nouv_area->nb_shapes = 0;
    return nouv_area;
}

void add_shape_to_area(Area* area, Shape* shape){
    area->shapes[area->nb_shapes] = shape;
    area->nb_shapes += 1;
}

void clear_area(Area * area){
    for(int i = 0;i<(area->height);i++){
        for(int j = 0; j<(area->width);j++){
            area->MAT[i][j] = 0;
        }
    }
}

void erase_area(Area * area){
    for(int i = 0; i<(area->nb_shapes);i++){
        delete_shape(area->shapes[i]);
    }
    area->nb_shapes = 0;
}

void delete_area(Area *area){
    for(int i = 0; i<(area->height);i++){
        free(area->MAT[i]);
    }
    free(area->MAT);
    area->width = 0;
    area->height=0;

    erase_area(area);
}
/*
void draw_area(Area *area){
    for (int i = 0; i<(area->nb_shapes);i++){
        Pixel ** stock = create_shape_to_pixel(area->shapes[i]);
        for (int j = 0; j<stock[i];j++){
            for (int k =0; k<)
        }
    }
}
*/

void print_area(Area * area){
    for (int i = 0;i <(area->height);i++){
        for (int j = 0;j<(area->width);j++){
            if (area->MAT[i][j] == 0){
                printf("%c", 46); // 46 en ASCII correspond à "."
            }
            else {
                printf("%c", 35); // 35 en ASCII correspond à "#"
            }
        }
        printf("\n");
    }
}
// Pixel
Pixel * create_pixel(int px, int py){
    Pixel * nouv_pix = malloc(sizeof(Pixel));
    nouv_pix -> px = px;
    nouv_pix -> py = py;
    return nouv_pix;
}

void delete_pixel(Pixel * pixel){
    free(pixel);
    pixel = NULL;
}

void pixel_point(Shape* shape, Pixel*** pixel_tab, int * nb_pixels){
    Point * pt = (Point*) shape -> ptrShape;
    *pixel_tab = malloc(sizeof(Pixel*));
    *pixel_tab[0] = create_pixel(pt->pos_x,pt->pos_y);
    *nb_pixels = 1;
}

void pixel_line(Shape* line, Pixel *** pixel_tab, int* nb_pixels){
    Line * l = line-> ptrShape;

}
//
// Created by Stive on 29/05/2023.
//
// Testdqdqq
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
    int dx = (l->p2->pos_x) - (l->p1->pos_x);
    int dy = (l->p2->pos_y) - (l->p1->pos_y);
    int dmin,dmax;
    if (dx <= dy) {
        dmin = dx;
        dmax = dy; // Taille totale
    }
    else{
        dmin = dy;
        dmax = dx; // Taille totale
    }
    int nb_segs = dmin +1;
    int taille_base = dmax / nb_segs;
    int segments[nb_segs];
    for (int i = 0; i<nb_segs;i++){
        segments[i] = taille_base;
    }
    int restants = (dmax+1)%(dmin+1);
    int *cumuls = (int *)malloc(nb_segs*sizeof(int));
    cumuls[0]=0;
    for (int i = 1; i < nb_segs;i++)
    {
        cumuls[i] = ((i*restants)%(dmin+1) < ((i-1)*restants)%(dmin+1));
        segments[i] = segments[i]+cumuls[i];
    }
    for (int i = 0; i<nb_segs-1;i++){
        for (int j = 0;j <  segments[i];j++ ) {
            if (dy < 0) {
                if (dx > abs(dy)) {
                    *pixel_tab[*nb_pixels] = create_pixel(++(l->p1->pos_x), (l->p1->pos_y)--);
                    *nb_pixels += 1;
                } else {
                    *pixel_tab[*nb_pixels] = create_pixel((l->p1->pos_x)++, --(l->p1->pos_y));
                    *nb_pixels += 1;
                }
            } else {
                if (dx > dy) {
                    *pixel_tab[*nb_pixels] = create_pixel(++(l->p1->pos_x), (l->p1->pos_y)++);
                    *nb_pixels += 1;
                } else {
                    *pixel_tab[*nb_pixels] = create_pixel((l->p1->pos_x)++, ++(l->p1->pos_y));
                    *nb_pixels += 1;
                }
            }
        }
    }
}

void pixel_circle(Shape * shape, Pixel *** pixel_tab, int *nb_pixels){
    Circle * c = shape->ptrShape;
    int x = 0;
    int y = c -> rayon;
    int d = c -> rayon-1;

    Pixel * px = NULL;
    while (y >= x){

        //1
        px = create_pixel((c ->pos->pos_x)+x, (c -> pos->pos_y)+y);
        pixel_tab[*nb_pixels++] = px;

        //2
        px = create_pixel((c ->pos->pos_x)+y, (c ->pos->pos_y)+x);
        pixel_tab[*nb_pixels++] = px;

        //3
        px = create_pixel((c->pos->pos_x)-x,(c->pos->pos_y)+y);
        pixel_tab[*nb_pixels++] = px;

        //4
        px = create_pixel((c->pos->pos_x)-y,(c->pos->pos_y)+x);
        pixel_tab[*nb_pixels++] = px;

        //5
        px = create_pixel((c->pos->pos_x)+x,(c->pos->pos_y)-y);
        pixel_tab[*nb_pixels++] = px;

        //6
        px = create_pixel((c->pos->pos_x)+y, (c->pos->pos_y)-x);
        pixel_tab[*nb_pixels++] = px;

        //7
        px = create_pixel((c->pos->pos_x)-x,(c->pos->pos_y)-y);
        pixel_tab[*nb_pixels++] = px;

        //8
        px = create_pixel((c->pos->pos_x)-y, (c->pos->pos_y)-x);
        pixel_tab[*nb_pixels++] = px;

        if (d>=(2*x)){
            d -= 2*x+1;
            x++;
        }
        else if (d<2*(c->rayon-y)){
            d+= 2*y-1;
            y--;
        }
        else{
            d += 2 * (y-x-1);
            y--;
            x++;
        }
    }
}

void pixel_square(Shape * square, Pixel ***  pixel_tab, int * nb_pixels){

}
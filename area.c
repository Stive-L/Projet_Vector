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

void draw_area(Area *area){
    for (int i = 0; i<(area->nb_shapes);i++){
        int nb_pixels;
        //printf("test");
        Pixel ** pix = create_shape_to_pixel(area->shapes[i],&nb_pixels);
        printf("%d", nb_pixels);
        /*
        for (int j = 0;j <nb_pixels;j++){
            Pixel * pix_2 = pix[j];
            area->MAT[pix_2->px][pix_2->py] = 1;
            printf("test5\n");
            //delete_pixel(pix_2);
        }
         */
        //delete_pixel_shape(&pix,nb_pixels);
    }
    printf("test4");
}


void print_area(Area * area){
    printf("test3");
    for (int i = 0;i <(area->height);i++){
        printf("test2\n");
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
        *pixel_tab[*nb_pixels++] = px;

        //2
        px = create_pixel((c ->pos->pos_x)+y, (c ->pos->pos_y)+x);
        *pixel_tab[*nb_pixels++] = px;

        //3
        px = create_pixel((c->pos->pos_x)-x,(c->pos->pos_y)+y);
        *pixel_tab[*nb_pixels++] = px;

        //4
        px = create_pixel((c->pos->pos_x)-y,(c->pos->pos_y)+x);
        *pixel_tab[*nb_pixels++] = px;

        //5
        px = create_pixel((c->pos->pos_x)+x,(c->pos->pos_y)-y);
        *pixel_tab[*nb_pixels++] = px;

        //6
        px = create_pixel((c->pos->pos_x)+y, (c->pos->pos_y)-x);
        *pixel_tab[*nb_pixels++] = px;

        //7
        px = create_pixel((c->pos->pos_x)-x,(c->pos->pos_y)-y);
        *pixel_tab[*nb_pixels++] = px;

        //8
        px = create_pixel((c->pos->pos_x)-y, (c->pos->pos_y)-x);
        *pixel_tab[*nb_pixels++] = px;

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
    Square * carre = square->ptrShape;

    Shape * new_l_haute = create_line_shape(carre->pos->pos_x, carre->pos->pos_y,carre->pos->pos_x, (carre->pos->pos_y)+(carre->length));
    pixel_line(new_l_haute, pixel_tab, nb_pixels);

    Shape * new_l_droite = create_line_shape(carre->pos->pos_x,carre->pos->pos_y+carre->length,carre->pos->pos_x+carre->length,carre->pos->pos_y+carre->length);
    pixel_line(new_l_droite, pixel_tab, nb_pixels);

    Shape * new_l_bas = create_line_shape(carre->pos->pos_x+carre->length,carre->pos->pos_y+carre->length, carre->pos->pos_x+carre->length, carre->pos->pos_y);
    pixel_line(new_l_bas,pixel_tab,nb_pixels);

    Shape * new_l_gauche = create_line_shape(carre->pos->pos_x+carre->length, carre->pos->pos_y, carre ->pos->pos_x,carre->pos->pos_y);
    pixel_line(new_l_gauche,pixel_tab,nb_pixels);

}

void pixel_rectangle(Shape * rectangle, Pixel *** pixel_tab,int * nb_pixels){
    Rectangle * rect = rectangle ->ptrShape;

    Shape * new_rect_haut = create_line_shape(rect->pos->pos_x,rect->pos->pos_y,rect->pos->pos_x,rect->pos->pos_y+rect->longueur);
    pixel_line(new_rect_haut,pixel_tab,nb_pixels);

    Shape * new_rect_droite = create_line_shape(rect->pos->pos_x,rect->pos->pos_y+rect->longueur, rect->pos->pos_x+rect->largeur,rect->pos->pos_y+rect->longueur);
    pixel_line(new_rect_droite,pixel_tab,nb_pixels);

    Shape * new_rect_bas = create_line_shape(rect->pos->pos_x+rect->largeur,rect->pos->pos_y+rect->longueur, rect->pos->pos_x+rect->largeur,rect->pos->pos_y);
    pixel_line(new_rect_bas,pixel_tab,nb_pixels);

    Shape * new_rect_gauche = create_line_shape(rect->pos->pos_x+rect->largeur,rect->pos->pos_y, rect->pos->pos_x,rect->pos->pos_y);
    pixel_line(new_rect_gauche,pixel_tab,nb_pixels);

}

void pixel_polygon(Shape * polygon, Pixel *** pixel_tab, int * nb_pixels){
    Polygon * poly = polygon -> ptrShape;
    for (int i = 0; i<(poly->n)-1;i++){
        Shape * new = create_line_shape(poly->points[i]->pos_x,poly->points[i]->pos_y,poly->points[i+1]->pos_x,poly->points[i+1]->pos_y);
        pixel_line(new,pixel_tab,nb_pixels);
    }
    Shape * new = create_line_shape(poly->points[poly->n]->pos_x,poly->points[poly->n]->pos_y,poly->points[poly->n+1]->pos_x,poly->points[poly->n+1]->pos_y);
    pixel_line(new,pixel_tab,nb_pixels);
}



Pixel ** create_shape_to_pixel(Shape * shape, int * nb_pixels){
        Pixel ** pix_tab = NULL;
        //*nb_pixels = 0;
        switch(shape -> shape_type){
            case POINT:{
                pixel_point(shape,&pix_tab, nb_pixels);
                break;
            }
            case LINE:{
                pixel_line(shape,&pix_tab,nb_pixels);
                break;
            }
            case CIRCLE:{
                pixel_circle(shape,&pix_tab,nb_pixels);
                break;
            }
            case SQUARE:{
                pixel_square(shape,&pix_tab,nb_pixels);
                break;
            }
            case RECTANGLE:{
                pixel_rectangle(shape,&pix_tab,nb_pixels);
                break;
            }
            case POLYGON:{
                pixel_polygon(shape,&pix_tab,nb_pixels);
                break;
            }
        }
        return pix_tab;
}

void delete_pixel_shape(Pixel *** pixel, int nb_pixels){
    for (int i = 0;i<nb_pixels;i++){
        delete_pixel((*pixel)[i]);
    }
    free(*pixel);
    *pixel = NULL;

}
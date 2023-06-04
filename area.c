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

    nouv_area -> MAT = calloc(width, sizeof(BOOL *));
    for (int i=0;i<width;i++) {
        nouv_area->MAT[i] = calloc(height, sizeof(int));
    }
    nouv_area->nb_shapes = 0;
    return nouv_area;
}

void add_shape_to_area(Area* area, Shape* shape){
    area->shapes[area->nb_shapes] = shape;
    area->nb_shapes += 1;
}

// On initialise tous les pixels à 0
void clear_area(Area * area){
    for(int i = 0;i<(area->width);i++){
        for(int j = 0; j<(area->height);j++){
            area->MAT[i][j] = 0;
        }
    }
}
// On supprime toutes les formes dessinés
void erase_area(Area * area){
    for(int i = 0; i<(area->nb_shapes);i++){
        delete_shape(area->shapes[i]);
    }
    area->nb_shapes = 0;
}

// Supprime une zone de dessin avec l'ensemble des formes associées
void delete_area(Area *area){
    for(int i = 0; i<(area->width);i++){
        free(area->MAT[i]);
    }
    free(area->MAT);
    free(area);
}

void draw_area(Area *area){
    for (int i = 0; i<(area->nb_shapes);i++){
        int nb_pixels = 0;
        //printf("test");
        Pixel ** pix = create_shape_to_pixel(area->shapes[i],&nb_pixels);
        //printf("Test3");
        //printf("%d", nb_pixels);
        for (int j = 0;j <nb_pixels;j++){
            //printf("test2");
            Pixel * pix_2 = pix[j];
            if (pix_2->px >= 0 && pix_2->px < area->width && pix_2->py >= 0 && pix_2->py < area->height) {
                area->MAT[pix_2->px][pix_2->py] = 1;
                //printf("test5\n");
            }
            //free(pix_2);
            //pix_2 = NULL;
        }

        //free(pix);
        //pix = NULL;
    }
    //printf("test4");
}


void print_area(Area * area){
    //printf("test3");
    for (int i = 0;i <(area->width);i++){ // Hauteur
        //printf("test2\n");
        for (int j = 0;j<(area->height);j++){ // Largeur
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
    if (dx <= abs(dy)) {
        dmin = dx;
        dmax = abs(dy); // Taille totale
    }
    else{
        dmin = abs(dy);
        dmax = dx; // Taille totale
    }
    int nb_segs = dmin +1;
    int taille_totale = dmax + 1;

    *pixel_tab = malloc(taille_totale*sizeof(Pixel*)); // Allocation mémoire

    int taille_base = taille_totale / nb_segs;
    int segments[nb_segs];
    for (int i = 0; i<nb_segs;i++){
        segments[i] = taille_base;
    }

    int restants = (dmax + 1) % (dmin + 1);
    int *cumuls = (int *)malloc(nb_segs * sizeof(int));
    cumuls[0] = 0;

    for (int i = 2; i < nb_segs + 1; i++)
    {
        //printf("%d\n",segments[i]);
        cumuls[i - 1] = ((i * restants) % (dmin + 1) < ((i - 1) * restants) % (dmin + 1));
        segments[i - 1] += cumuls[i - 1];
        //printf("%d\n",cumuls[i]);
        //printf("segment de %d: %d\n", i - 1, segments[i - 1]);
    }

     //cumuls[0]=0;

    int temp_x = l->p1->pos_x;
    int temp_y = l->p1->pos_y;

    for (int i = 0; i<nb_segs;i++){
        for (int j = 0;j <segments[i];j++ ) {
            if (dy < 0) { // On trace vers le bas, c'est à dire Ya > Yb
                if (dx > abs(dy)) {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel((temp_y),(temp_x)++);
                } else {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel((temp_y)--,(temp_x));
                }
            } else { // On trace vers le haut, c'est à dire Ya < Yb
                if (dx > dy) {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel((temp_x)++, (temp_y));
                } else {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel((temp_x), (temp_y)++);
                }
            }
            //*nb_pixels += 1 ;
            //printf("Après : %d, %d\n", l->p1->pos_x, l->p1->pos_y);
        }

        if (dy < 0) {
            if (dx > abs(dy)) {
                --(temp_y);
            } else {
                (temp_x)++;
            }
        } else {
            if (dx > dy) {
                (temp_y)++;
            } else {
                (temp_x)++;
            }
        }

    }
}


void pixel_circle(Shape * shape, Pixel *** pixel_tab, int *nb_pixels){
    Circle * c = shape->ptrShape;

    *pixel_tab = malloc((c -> rayon * 8) * sizeof(Pixel*)); // Allocation mémoire
    int x = 0;
    int y = c -> rayon;
    int d = c -> rayon-1;

    Pixel * px = NULL;
    while (y >= x){

        //1
        px = create_pixel((c ->pos->pos_x)+x, (c -> pos->pos_y)+y);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //2
        px = create_pixel((c ->pos->pos_x)+y, (c ->pos->pos_y)+x);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //3
        px = create_pixel((c->pos->pos_x)-x,(c->pos->pos_y)+y);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //4
        px = create_pixel((c->pos->pos_x)-y,(c->pos->pos_y)+x);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //5
        px = create_pixel((c->pos->pos_x)+x,(c->pos->pos_y)-y);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //6
        px = create_pixel((c->pos->pos_x)+y, (c->pos->pos_y)-x);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //7
        px = create_pixel((c->pos->pos_x)-x,(c->pos->pos_y)-y);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

        //8
        px = create_pixel((c->pos->pos_x)-y, (c->pos->pos_y)-x);
        (*pixel_tab)[(*nb_pixels)++] = px;
        //*nb_pixels += 1;

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
    *pixel_tab = malloc(carre->length * carre->length * sizeof(Pixel *));
    int x = carre->pos->pos_x;
    int y = carre->pos->pos_y;
    int longueur = carre ->length;

    Pixel *px = NULL;
    // haut
    for (int i = 0; i < longueur; i++)
    {
        px = create_pixel(x, y + i);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

    // droite
    for (int i = 0; i < longueur ; i++)
    {
        px = create_pixel(x + i, y + longueur - 1);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

    // bas
    for (int i = 0; i < longueur ; i++)
    {
        px = create_pixel(x + longueur - 1 , y + i);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

    //gauche
    for (int i = 0; i < longueur ; i++)
    {
        px = create_pixel(x + i , y);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }
}

void pixel_rectangle(Shape * rectangle, Pixel *** pixel_tab,int * nb_pixels){
    //printf("testrect");
    Rectangle * rect = rectangle->ptrShape;
    //printf("testrect 6 ");
    *pixel_tab = malloc((rect->longueur * 2 + rect->largeur * 2 - 4) * sizeof(Pixel *)); // Allocation mémoire : "-4" car on ne compte, en double, pas les coins
    //printf("testrect 4 ");
    int x = rect->pos->pos_x;
    int y = rect->pos->pos_y;
    int largeur = rect->largeur;
    int longueur = rect->longueur;
    //printf("%d %d", largeur, longueur);
    //printf("testrect 2 ");
    // haut

    for (int i = 0; i < longueur; i++)
    {
        Pixel * px = create_pixel(x, y + i);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

    //bas
    for (int i = 1 ;i<longueur-1;i++){
        Pixel * px = create_pixel(x + largeur - 1 , y + i);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

    //gauche
    for (int i = 1; i < largeur; i++)
    {
        Pixel * px = create_pixel(x + i , y);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

    //droite
    for (int i = 1 ; i < largeur ; i++)
    {
        Pixel * px = create_pixel(x + i , y+longueur-1);
        (*pixel_tab)[(*nb_pixels)++] = px;
    }

}

void pixel_polygon(Shape * polygon, Pixel *** pixel_tab, int * nb_pixels){
    Polygon * poly = polygon -> ptrShape;
    *pixel_tab = malloc(poly->n * sizeof(Pixel *));
    for (int i = 0; i<poly->n/2;i++){
        if (i != (poly->n/2)-1) {
            Shape *new = create_line_shape(poly->points[i]->pos_x, poly->points[i]->pos_y, poly->points[i + 1]->pos_x,poly->points[i + 1]->pos_y);
            //Shape *new = create_line_shape(poly->points[i]->pos_y, poly->points[i]->pos_x, poly->points[i + 1]->pos_y,poly->points[i + 1]->pos_y);
            pixel_line(new, pixel_tab, nb_pixels);
        }
        else{
            break;
        }
    }

    /*
    Shape * new = create_line_shape(poly->points[poly->n]->pos_x,poly->points[poly->n]->pos_y,poly->points[poly->n+1]->pos_x,poly->points[poly->n+1]->pos_y);
    pixel_line(new,pixel_tab,nb_pixels);
    */
}


Pixel ** create_shape_to_pixel(Shape * shape, int * nb_pixels){
        Pixel ** pix_tab = NULL;
        //*nb_pixels = 0;
        //printf("%d", *nb_pixels);
        switch(shape -> shape_type){
            case POINT:{
                pixel_point(shape,&pix_tab, nb_pixels);
                break;
            }
            case LINE:{
                //printf("%d", *nb_pixels);
                pixel_line(shape,&pix_tab,nb_pixels);
                //printf("%d", *nb_pixels);
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
//
// Created by Stive on 27/05/2023.
//

#ifndef PROJET_SHAPES_H
#define PROJET_SHAPES_H

//Structure Point----------------------------------------------------
typedef struct {
    int pos_x;
    int pos_y;
}Point;
Point * create_point(int px, int py);
void delete_point(Point * point);
void print_point(Point * p);


//Structure Line-----------------------------------------------------
typedef struct{
    Point *p1;
    Point *p2;
}Line;
Line *create_line(Point * p1, Point * p2);
void delete_line(Line * line);
void print_line(Line * line);

//Structure Square-----------------------------------
typedef struct{
    Point * pos;
    int length; // longueur
}Square;
Square *create_square(Point * point, int length);
void delete_square(Square * square);
void print_square(Square * square);


// Structure Rectangle
typedef struct{
    Point * pos;
    int longueur;
    int largeur;
}Rectangle;
Rectangle *create_rectangle(Point * point, int width, int height);
void delete_rectangle(Rectangle * rectangle);
void print_rectangle(Rectangle * rectangle);


// Structure Circle
typedef struct{
    Point * pos;
    int rayon;
}Circle;
Circle *create_circle(Point * center, int radius);
void delete_circle(Circle * circle);
void print_circle(Circle * circle);


// Structure Polygon
typedef struct {
    int n; // Le nombre de point
    Point ** points; // tableau 1D dynamique de Point*
}Polygon;
Polygon *create_polygon(int n, Point** tab);
void delete_polygon(Polygon * polygon);
void print_polygon(Polygon * polygon);



// Structure Shape
typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;
typedef struct shape {
    int id; // identifiant unique de la forme
    SHAPE_TYPE shape_type; // type de la forme pointé
    void *ptrShape; // pointeur sur n'importe quelle forme
}Shape;

Shape *create_empty_shape(SHAPE_TYPE shape_type);
Shape *create_point_shape(int px, int py);
Shape *create_line_shape(int px1, int py1, int px2, int py2);
Shape *create_square_shape(int px, int py, int length);
Shape *create_rectangle_shape(int px, int py, int width, int height);
Shape *create_circle_shape(int px, int py, int radus);
Shape *create_polygon_shape(int lst[], int n);
void delete_shape(Shape * shape);
void print_shape(Shape * shape);

unsigned int get_next_id();

#endif //PROJET_SHAPES_H


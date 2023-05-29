
#include <stdio.h>
#include "shapes.c"


int main() {
    Shape * f1 = create_line_shape(10, 15, 21, 25);
    print_shape(f1);
    delete_shape(f1);
    return 0;
}

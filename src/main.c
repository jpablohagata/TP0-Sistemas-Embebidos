#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "shape.h"
#include "rectangle.h"
#include "line.h"


#define MAX_IMG_NAME	20

#define N_ROWS			200 	// Cantidad de filas
#define N_COLS			200		// Cantidad de columnas


/* Ejemplo de uso de las funciones de la clase "imagen" */

int main(void){
	
	char img_name[MAX_IMG_NAME];
	image_t * img = (image_t *)malloc(sizeof(image_t));
	if (!img) return EXIT_FAILURE;
//	rectangle_t * rectangle = (rectangle_t *)malloc(sizeof(rectangle_t));
//	if (!rectangle) return EXIT_FAILURE;
	line_t * line = (line_t *)malloc(sizeof(line_t));
	if (!line) return EXIT_FAILURE;

	image_ctor(img,N_ROWS,N_COLS);

//	rectangle_ctor(rectangle, 1, 1, 10, 15);
//	rectangle_rotate(rectangle, 90);
//	shape_move(rectangle->super, 5, 5);
//	rectangle_plot(rectangle,img);

	line_ctor(line, 1, 1, 10, 20);
	line_plot(line, img);
	
	sprintf(img_name,"./images/img%.3d.pbm",0);
	image_to_file(img,img_name);
	image_dtor(img);

//	rectangle_dtor(rectangle);
//	free(rectangle);
	line_dtor(line);
	free(line);
	free(img);

	return EXIT_SUCCESS;
}
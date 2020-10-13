#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "shape.h"
#include "rectangle.h"
#include "line.h"
#include <stdint.h>


#define MAX_IMG_NAME	20
#define N_ROWS			200 	// Cantidad de filas
#define N_COLS			200		// Cantidad de columnas
#define FRAMES 			72		// Cantidad de frames del video

static bool generate_video(uint32_t width,uint32_t height,uint32_t total_frames){
	image_t * image_ptr;
	rectangle_t * rectangle_ptr;
	uint32_t initial_position_x,initial_position_y;
	uint32_t rectangle_width,rectangle_height;
	char img_name[MAX_IMG_NAME];

	initial_position_x = 0;
	initial_position_y = 0;
	rectangle_width = width/8;
	rectangle_height = height/8;


	//Armamos la estructura inicial de la imagen
	if((image_ptr = (image_t *)malloc(sizeof(image_t))) == false){
		return false;
	}
	if((rectangle_ptr = (rectangle_t *) malloc(sizeof(rectangle_t))) == false){
		free(image_ptr);
		return false;
	}

	for(register size_t i = 0; i < total_frames; i++){
		// Creamos la imagen (el canvas sobre el que se va a dibujar el objeto)
		if(!image_ctor(image_ptr,height,width)){
			free(image_ptr);
			free(rectangle_ptr);
			return false;
		}
		// Creamos el objeto (en este caso un rectangulo)
		if((rectangle_ctor(rectangle_ptr,initial_position_x, initial_position_y, 
					rectangle_height,rectangle_width)) == false){
			image_dtor(image_ptr);
			free(image_ptr);
			free(rectangle_ptr);
			return false;
		}

		rectangle_rotate(rectangle_ptr,i);
		rectangle_move(rectangle_ptr,4*i,4*i);

		// Agregamos el objeto a la imagen
		if((rectangle_plot(rectangle_ptr,image_ptr)) == false){
			rectangle_dtor(rectangle_ptr);
			image_dtor(image_ptr);
			free(image_ptr);
			free(rectangle_ptr);
			return false;
		}

		//Creamos el archivo en memoria
		sprintf(img_name,"./video/img%.3d.pbm",i);
		image_to_file(image_ptr,img_name);
		image_dtor(image_ptr);
		rectangle_dtor(rectangle_ptr);
	}
	free(image_ptr);
	free(rectangle_ptr);
	return true;
}


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

// Generamos el video

	if(generate_video(N_ROWS,N_COLS,FRAMES) == true){
		puts("Video generado");
	}

	return EXIT_SUCCESS;
}
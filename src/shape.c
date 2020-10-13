#include "shape.h"
#include "image.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define DEG2RAD PI/180

bool shape_ctor(shape_t *me, coordinates_array_t *array, uint32_t position_x, uint32_t position_y){
	coordinate_t * coord;

	coord = (coordinate_t *)malloc(sizeof(coordinate_t));
	if (!coord) return false;

	coord->x = position_x;
	coord->y = position_y;

	me->array = array;
	me->position = coord;

	return true;
}

void shape_dtor(shape_t *me){
	for (register uint32_t i=0; i<me->array->n_array; i++) {
		free(me->array->coordinates[i]);
	}
	free(me->array->coordinates);
	free(me->array);
	free(me->position);
}

bool shape_move(shape_t *me, uint32_t dx, uint32_t dy){
	for (register uint32_t i=0; i<me->array->n_array; i++){
		me->array->coordinates[i]->x += dx;
		me->array->coordinates[i]->y += dy;
	}

	return true;
}

bool shape_rotate(shape_t *me, float angle){
	uint32_t x,y;
	
	for (register uint32_t i=0; i<me->array->n_array; i++){
		x = me->array->coordinates[i]->x;
		y = me->array->coordinates[i]->y;
		me->array->coordinates[i]->x = 
			x*cos(angle*DEG2RAD)-y*sin(angle*DEG2RAD);
		me->array->coordinates[i]->y =
			x*sin(angle*DEG2RAD)+y*cos(angle*DEG2RAD);
	}
	return true;
}

float shape_distance_from(shape_t *s1, shape_t *s2){

	uint32_t x, y;
	x = s1->position->x-s2->position->x;
	y = s1->position->y-s2->position->y;

	return sqrt(x*x+y*y);

}

bool shape_plot(shape_t *me, image_t *image){
	uint32_t x,y;
	uint32_t img_width,img_height;

	img_width = image_get_width(image);
	img_height = image_get_height(image);

	for (register uint32_t i=0; i<me->array->n_array; i++) {
		x = me->array->coordinates[i]->x;
		y = me->array->coordinates[i]->y;
		if(x < img_width && y < img_height){
			image_write(image,x,y, HIGH);
		}
	}
	return true;
}
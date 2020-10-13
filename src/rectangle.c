#include "shape.h"
#include "rectangle.h"
#include <stdint.h>
#include <stdlib.h>

bool rectangle_ctor(rectangle_t *me, uint32_t position_x, uint32_t position_y, 
					uint32_t height, uint32_t width) {

	shape_t * shape = (shape_t *)malloc(sizeof(shape_t));
	coordinates_array_t * coord_arr = (coordinates_array_t *)malloc(sizeof(coordinates_array_t));
	coordinate_t ** coords = (coordinate_t **)malloc(width*height*sizeof(coordinate_t *));

	if ( !shape || !coord_arr || !coords ) {
		free(shape);
		free(coord_arr);
		free(coords);
		return false;
	}

	me->super = shape;
	coord_arr->n_array = width*height;
	coord_arr->coordinates = coords;

	uint32_t coord_id = 0;
	for (register uint32_t i=0; i<width; i++) {
		for (register uint32_t j=0; j<height; j++) {

			coords[coord_id] = (coordinate_t *)malloc(sizeof(coordinate_t));
			if (!coords[coord_id]){
				shape_dtor(me->super);
				return false;
			}
			
			coords[coord_id]->x = position_x + i;
			coords[coord_id]->y = position_y + j;
			coord_id++;
		}
	}

	shape_ctor(me->super, coord_arr, position_x, position_y);

	return true;
}

void rectangle_dtor(rectangle_t *me) {
	shape_dtor(me->super);
}

bool rectangle_rotate(rectangle_t *me, float angle){
	return shape_rotate(me->super, angle);
}

bool rectangle_move(rectangle_t * me, uint32_t dx, uint32_t dy){
	return shape_move(me->super,dx,dy);
}

uint32_t rectangle_get_area(rectangle_t *me){
	return me->super->array->n_array;
}

bool rectangle_plot(rectangle_t *me, image_t *image){
	return shape_plot(me->super, image);
}

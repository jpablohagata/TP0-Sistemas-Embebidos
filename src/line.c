#include "shape.h"
#include "line.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

bool line_ctor(line_t *me, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){

	// Get the lenght in points of the line
	uint32_t lenght = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

	// Memory allocations
	shape_t * shape = (shape_t *)malloc(sizeof(shape_t));
	coordinates_array_t * coord_arr = (coordinates_array_t *)malloc(sizeof(coordinates_array_t));
	coordinate_t ** coords = (coordinate_t **)malloc(lenght*sizeof(coordinate_t *));

	if ( !shape || !coord_arr || !coords ) {
		free(shape);
		free(coord_arr);
		free(coords);
		return false;
	}

	me->super = shape;
	coord_arr->n_array = lenght;
	coord_arr->coordinates = coords;

	// Get the slope of the line
	// TODO: fix
	float_t m;
	if (x1 != x2) m = (y2-y1)/(x2-x1);
	else return false;

	// Set the coordinates
	uint32_t coord_id = 0;
	for (register uint32_t i=0; i<lenght; i++) {
		coords[coord_id] = (coordinate_t *)malloc(sizeof(coordinate_t));
		if (!coords[coord_id]){
			shape_dtor(me->super);
			return false;
		}

		coords[coord_id]->x = x1+i;
		coords[coord_id]->y = (x1+i)*m;
		coord_id++;
	}

	// Create the shape with the coordinates
	shape_ctor(me->super, coord_arr, x1, y1);
	me->start = coords[0];
	me->end = coords[coord_id-1];

	return true;
}

void line_dtor(line_t *me){
	shape_dtor(me->super);
}


bool line_rotate(line_t *me, float angle){
	return shape_rotate(me->super, angle);
}


bool line_scale(line_t *me, float factor){
	// TODO
	return true;
}


float line_get_lenght(line_t *me){
	uint32_t x1, x2, y1, y2;
	x1 = me->start->x;
	x2 = me->start->y;
	y1 = me->end->x;
	y2 = me->end->y;
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));;
}

bool line_plot(line_t *me, image_t *image){
	return shape_plot(me->super, image);
}

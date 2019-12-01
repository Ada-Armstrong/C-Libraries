#ifndef __GRAPHICS_SHAPE_H__
#define __GRAPHICS_SHAPE_H__

/* Header for the Brensenham line and circle algorithms. Uses only 
 * integer operations and works for any slope. For more info check out
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm and
 * https://en.wikipedia.org/wiki/Midpoint_circle_algorithm. */

#include <stdlib.h>
#include <math.h>	/* Only dependency is ceilf(), consider removing */

struct posn {
	int x;
	int y;
};

typedef struct posn *Vec2;


/* Returns an array of struct posns that approximate the line between (x0, y0)
 * and (x1, y1). Allocates these posns to the heap, client is responsible of
 * freeing. */
Vec2 draw_line(int x0, int y0, int x1, int y1, int *len);


/* Returns an array of struct posns that approximates the circle centered at
 * the point (x0, y0). Allocates these posns to the heap, client is responsible
 * of freeing. */
Vec2 draw_circle(int x0, int y0, int radius, int *len);


/* Returns an array of struct posns that appromimates the traingle described by
 * the points (x0, y0), (x1, y1), (x2, y2) according to the top-left rule.
 * Allocates these posns to the heap, client is responsible of freeing */
Vec2 draw_triangle(float x0, float y0, float x1, float y1,
		float x2, float y2, int *len);

#endif

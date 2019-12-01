#include <assert.h>
#include "shape.h"

int main()
{
	int len = 0;
	Vec2 line = draw_line(0, 0, 100, 34, &len);
	assert(line);
	free(line);

	len = 0;
	Vec2 circle = draw_circle(5, 0, 69, &len);
	assert(circle);
	free(circle);

	len = 0;
	Vec2 tri = draw_triangle(0, 0, 40.2, 20.6, 10, 3.1, &len);
	assert(tri);
	free(tri);

	return 0;
}

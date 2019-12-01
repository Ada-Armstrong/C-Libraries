#include "shape.h" 

static inline void draw_high(int x0, int y0, int x1, int y1, 
		Vec2 pixels, int *len)
{
	int dx;
	int dy;
	int p;
	int x;
	int y;
	int xi;
   	struct posn pixel;

	dx = x1 - x0;
    	dy = y1 - y0;
	
	if (dx < 0) {
		xi = -1;
		dx = -dx;
	} else {
		xi = 1;
	}

	x = x0;
	y = y0;
 
	p = (dx << 1) - dy;
	 
	while(y <= y1) {
		pixel.x = x;
		pixel.y = y;	
		pixels[*len] = pixel;
		if(p >= 0) {
			x = x + xi; 
			p = p - (dy << 1);
		}

		p = p + (dx << 1);
		y = y + 1;
		*len += 1;
	}
}

static inline void draw_low(int x0, int y0, int x1, int y1, 
		Vec2 pixels, int *len)
{
	int dx;
	int dy;
	int p;
	int x;
	int y;
	int yi;
   	struct posn pixel;

	dx = x1 - x0;
    	dy = y1 - y0;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	} else {
		yi = 1;
	}

	x = x0;
	y = y0;
 
	p = (dy << 1) - dx;
	 
	while(x <= x1) {
		pixel.x = x;
		pixel.y = y;	
		pixels[*len] = pixel;
		if(p >= 0) {
			y = y + yi; 
			p = p - (dx << 1);
		}

		p = p + (dy << 1);
		x = x + 1;
		*len += 1;
	}
}

static inline void draw_dia(int x0, int y0, int x1, int y1, 
		Vec2 pixels, int *len)
{
	int dy;
	int yi;
	struct posn pixel;

	dy = y1 - y0;
	if (dy < 0) {
		yi = -1;
	} else {
		yi = 1;
	}

	while (x0 <= x1) {
		pixel.x = x0;
		pixel.y = y0;
		pixels[*len] = pixel;
		x0 += 1;
		y0 += yi;
		*len += 1;
	}	
}

Vec2 draw_line(int x0, int y0, int x1, int y1, int *len)
{
	int max = x0 > y0? x0: y0;	
	Vec2 pixels = malloc(max * sizeof(*pixels));
	if (!pixels)
		return NULL;

	if (abs(y1 - y0) < abs(x1 - x0)) {
		if (x0 > x1) {
			draw_low(x1, y1, x0, y0, pixels, len);
		} else {
			draw_low(x0, y0, x1, y1, pixels, len);
		}
	} else if (abs(y1 - y0) == abs(x1 - x0)) {
		if (x0 > x1) {
			draw_dia(x1, y1, x0, y0, pixels, len);
		} else {
			draw_dia(x0, y0, x1, y1, pixels, len);
		}
	} else {
		if (y0 > y1) {
			draw_high(x1, y1, x0, y0, pixels, len);
		} else {
			draw_high(x0, y0, x1, y1, pixels, len);
		}
	}

	return pixels;
}

static inline struct posn ret_posn(int x, int y)
{
	struct posn p = {x, y};
	return p;
}

Vec2 draw_circle(int x0, int y0, int radius, int *len)
{
	int n;
	int x;
	int y;
	int dx;
	int dy;
	int err;

	n = radius << 3;
	Vec2 pixels = malloc(n * sizeof(*pixels));
	if (!pixels)
		return NULL;

	x = radius - 1;
	y = 0;
	dx = 1;
	dy = 1;
	err = dx - (radius << 1);

	while (x >= y) {
		/* mirrors the point for all eight octants */	
		pixels[(*len)++] = ret_posn(x0 + x, y0 + y);
		pixels[(*len)++] = ret_posn(x0 + y, y0 + x);	
		pixels[(*len)++] = ret_posn(x0 - y, y0 + x);	
		pixels[(*len)++] = ret_posn(x0 - x, y0 + y);	
		pixels[(*len)++] = ret_posn(x0 - x, y0 - y);	
		pixels[(*len)++] = ret_posn(x0 - y, y0 - x);	
		pixels[(*len)++] = ret_posn(x0 + y, y0 - x);	
		pixels[(*len)++] = ret_posn(x0 + x, y0 - y);	

		if (err < 0) {
			++y;
			err += dy;
			dy += 2;
		} else {
			--x;
			dx += 2;
			err += dx - (radius << 1);
		}
	}

	return pixels;	
}

static inline int draw_bot_flat_tri(float x0, float y0, float x1, float y1,
		float x2, float y2, Vec2 pixels, int *len, int *maxlen)
{
	const float m0 = (x1 - x0) / (y1 - y0);
	const float m1 = (x2 - x0) / (y2 - y0);
	
	const int ystart = (int)ceilf(y0 - 0.5f);
	const int yend = (int)ceilf(y2 - 0.5f);

	float px0, px1;
	int xstart, xend;
	struct posn pixel;
	Vec2 tmp;

	for (int y = ystart; y < yend; ++y) {
		px0 = m0 * ((float)y + 0.5f - y0) + x0;
		px1 = m1 * ((float)y + 0.5f - y0) + x0;
		
		xstart = (int)ceilf(px0 - 0.5f);
		xend = (int)ceilf(px1 - 0.5f);
	
		pixel.y = y;

		*maxlen += xend - xstart;
		tmp = realloc(pixels, *maxlen * sizeof(*pixels)); 
		if (!tmp) {
			free(pixels);
			return 0;
		}
		pixels = tmp;
	
		for (int x = xstart; x < xend; ++x) {
			pixel.x = x;
			pixels[*len] = pixel;
			*len += 1;
		}	
	}
	
	return 1;
}

static inline int draw_top_flat_tri(float x0, float y0, float x1, float y1,
		float x2, float y2, Vec2 pixels, int *len, int *maxlen)
{
	const float m0 = (x2 - x0) / (y2 - y0);
	const float m1 = (x2 - x1) / (y2 - y1);
	
	const int ystart = (int)ceilf(y0 - 0.5f);
	const int yend = (int)ceilf(y2 - 0.5f);

	float px0, px1;
	int xstart, xend;
	struct posn pixel;
	Vec2 tmp;

	for (int y = ystart; y < yend; ++y) {
		px0 = m0 * ((float)y + 0.5f - y0) + x0;
		px1 = m1 * ((float)y + 0.5f - y1) + x1;
		
		xstart = (int)ceilf(px0 - 0.5f);
		xend = (int)ceilf(px1 - 0.5f);
	
		pixel.y = y;
		
		*maxlen += xend - xstart;

		tmp = realloc(pixels, *maxlen * sizeof(*pixels)); 
		if (!tmp) {
			free(pixels);
			return 0;
		}
		pixels = tmp;
	
		for (int x = xstart; x < xend; ++x) {
			pixel.x = x;
			pixels[*len] = pixel;
			*len += 1;
		}	
	}

	return 1;
}

Vec2 draw_triangle(float x0, float y0, float x1, float y1,
		float x2, float y2, int *len)
{
	*len = 0;
	int maxlen = 0;

	Vec2 pixels = malloc(sizeof(*pixels));
	if (!pixels)
		return NULL;

	float temp_x;
	float temp_y;

	/* order by y value */
	if (y1 < y0) {
		temp_x = x0;
		temp_y = y0;
		x0 = x1;
		y0 = y1;
		x1 = temp_x;
		y1 = temp_y;
	}
	if (y2 < y1) {
		temp_x = x1;
		temp_y = y1;
		x1 = x2;
		y1 = y2;
		x2 = temp_x;
		y2 = temp_y;
	}
	if (y1 < y0) {
		temp_x = x0;
		temp_y = y0;
		x0 = x1;
		y0 = y1;
		x1 = temp_x;
		y1 = temp_y;
	}

	int ret;
	if (y0 == y1) {
		/* flat top */
		if (x1 < x0) {
			ret = draw_top_flat_tri(x1, y1, x0, y0, x2, y2,
					pixels, len, &maxlen);
		} else {
			ret = draw_top_flat_tri(x0, y0, x1, y1, x2, y2,
					pixels, len, &maxlen);
		}	
	} else if (y1 == y2) {
		/* flat bottom */	
		if (x2 < x1) {
			ret = draw_bot_flat_tri(x0, y0, x2, y2, x1, y1,
					pixels, len, &maxlen);
		} else {
			ret = draw_bot_flat_tri(x0, y0, x1, y1, x2, y2,
					pixels, len, &maxlen);
		}
	} else {
		/* split into flat top and flat bottom triangles */
		const float x3 = ((x2 - x0) * (y1 - y0) / (y2 - y0)) + x0;
		const float y3 = y1;
		if (x1 < x3) {
			ret = draw_top_flat_tri(x1, y1, x3, y3, x2, y2,
					pixels, len, &maxlen);
			if (ret) {
				/* first draw successful */
				draw_bot_flat_tri(x0, y0, x1, y1, x3, y3,
						pixels, len, &maxlen);
			}
		} else {
			ret = draw_top_flat_tri(x3, y3, x1, y1, x2, y2,
					pixels, len, &maxlen);
			if (ret) {
				/* first draw successful */
				draw_bot_flat_tri(x0, y0, x3, y3, x1, y1,
						pixels, len, &maxlen);
			}
		}
	}

	return ret ? pixels : NULL;
}

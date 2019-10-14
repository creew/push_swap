#include "fdf.h"

void	draw_line(t_fdf *fdf, t_point *p1, t_point *p2)
{
	t_point	delta;
	t_point	dyx;
	int error;
	int deltaerr;
	int y;
	int diry;

	deltax = ABS(p2.x - p1.x);
	deltay = ABS(p2.y - p1.y);
	error = 0;
	deltaerr = deltay;
	y = y0;
	diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x)
	for x from x0 to x1
		plot(x,y);
		error = error + deltaerr;
		if 2 * error >= deltax
			y := y + diry
			error := error - deltax
}

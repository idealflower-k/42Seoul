#include "fdf_bonus.h"

void	draw_line(t_coord **coords, t_img *img, t_map *map)
{
	draw_width(coords, img, map);
	draw_height(coords, img, map);
}

void	draw_width(t_coord **coords, t_img *img, t_map *map)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			set_color_width(map, x, y);
			draw(img, &coords[y][x], &coords[y][x + 1], map);
			x++;
		}
		y++;
	}
}

void	draw_height(t_coord **coords, t_img *img, t_map *map)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height - 1)
		{
			set_color_height(map, x, y);
			draw(img, &coords[y][x], &coords[y + 1][x], map);
			y++;
		}
		x++;
	}
}

void	draw(t_img *img, t_coord *coord0, t_coord *coord1, t_map *map)
{
	t_draw	*draw;
	int		step;

	step = 0;
	draw = set_draw(coord0, coord1);
	while (draw)
	{
		my_mlx_pixel_put(img, draw->x[0], draw->y[0], \
			get_color(coord0, draw, step, map));
		if (bresenham_line_algo(draw) == 0)
			break ;
		step++;
	}
	free(draw);
}

t_draw	*set_draw(t_coord *coord0, t_coord *coord1)
{
	t_draw	*draw;

	if (!coord0 || !coord1)
		return (0);
	draw = ft_malloc(sizeof(t_draw));
	draw->x[0] = coord0->x;
	draw->x[1] = coord1->x;
	draw->y[0] = coord0->y;
	draw->y[1] = coord1->y;
	draw->z[0] = coord0->z;
	draw->z[1] = coord1->z;
	draw->dx = abs(coord1->x - coord0->x);
	draw->dy = -abs(coord1->y - coord0->y);
	draw->error = draw->dx + draw->dy;
	draw->sx = 1;
	draw->sy = 1;
	if (coord1->x < coord0->x)
		draw->sx = -1;
	if (coord1->y < coord0->y)
		draw->sy = -1;
	return (draw);
}

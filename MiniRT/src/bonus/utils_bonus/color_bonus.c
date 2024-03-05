#include "defs_bonus.h"
#include "minirt_bonus.h"
#include "utils_bonus.h"

static inline uint32_t	_color_calc(double rgb)
{
	return (0xFF * clamp(rgb, 0, 1));
}

uint32_t	rgba_to_color(t_rgb rgb)
{
	return (_color_calc(rgb.x) << 16 | \
			_color_calc(rgb.y) << 8 | \
			_color_calc(rgb.z));
}

t_rgb	rgb_init_int(const int r, const int g, const int b)
{
	const t_rgb	rgb = {
		(double)r / 0xFF,
		(double)g / 0xFF,
		(double)b / 0xFF};

	return (rgb);
}

t_rgb	rgba_min(t_rgb a, t_rgb b)
{
	if (a.x > b.x)
		a.x = b.x;
	if (a.y > b.y)
		a.y = b.y;
	if (a.z > b.z)
		a.z = b.z;
	return (a);
}

t_rgb	color_to_rgba(char *color, const int endian)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (endian)
	{
		color++;
		r = *color++;
		g = *color++;
		b = *color++;
	}
	else
	{
		b = *color++;
		g = *color++;
		r = *color++;
	}
	return (rgb_init_int(r, g, b));
}

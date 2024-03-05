#include "parser_bonus.h"
#include "utils_bonus.h"
#include "render_bonus.h"
#include "design_patterns_bonus.h"

static bool	_vaildation_plane(t_plane *plane)
{
	if (plane->type != PL
		|| !check_normal_vec(plane->normal_vec3)
		|| !check_rgb(&plane->rgb)
		|| plane->scale <= 0 || plane->scale > 100
		|| fabs(1 - vec3_length(plane->normal_vec3)) > EPSILON)
		return (false);
	return (true);
}

static inline void	_set_plane_info(t_plane *plane, char **line)
{
	plane->type = PL;
	plane->point = parser_vec3(line[1], POINT_ERR);
	plane->normal_vec3 = parser_vec3(line[2], VEC_ERR);
	plane->rgb = parser_vec3(line[3], RGB_ERR);
	if (line[4])
		plane->scale = check_to_double(line[4]);
	else
		plane->scale = 42;
}

static inline t_obj	*_set_obj_info(t_plane plane, t_obj_option *option)
{
	t_obj			*obj;

	obj = ft_malloc(sizeof(t_obj));
	obj->type = PL;
	obj->content.plane = plane;
	obj->get_t = get_plane_dist;
	obj->set_r = set_plane_record;
	obj->option = option;
	obj->next = NULL;
	return (obj);
}

void	parser_plane(char **line)
{
	const int		len = ft_arrlen((void **)line);
	t_obj_option	*option;
	t_plane			plane;

	if (!(len == 4 || len == 7 || len == 9 || len == 10))
		error_handler(PL_ERR);
	_set_plane_info(&plane, line);
	if (len != 4)
		option = option_allocator(line, 5, PL_ERR);
	else
		option = NULL;
	if (!_vaildation_plane(&plane) || !vaildation_option(option))
	{
		ft_free_all_arr(line);
		error_handler(PL_ERR);
	}
	objsadd_back(&singleton()->objs, _set_obj_info(plane, option));
}

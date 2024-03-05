#include "parser_bonus.h"
#include "utils_bonus.h"
#include "render_bonus.h"
#include "design_patterns_bonus.h"

static bool	_vaildation_cylinder(t_cylinder *cylinder)
{
	if (cylinder->type != CY
		|| !check_normal_vec(cylinder->normal_vec3)
		|| !check_rgb(&cylinder->rgb)
		|| cylinder->diameter <= 0
		|| cylinder->height <= 0
		|| fabs(1 - vec3_length(cylinder->normal_vec3)) > EPSILON)
		return (false);
	return (true);
}

static inline void	_set_cylinder_info(t_cylinder *cylinder, char **line)
{
	cylinder->type = CY;
	cylinder->center_point = parser_vec3(line[1], POINT_ERR);
	cylinder->normal_vec3 = parser_vec3(line[2], VEC_ERR);
	cylinder->diameter = check_to_double(line[3]);
	cylinder->height = check_to_double(line[4]);
	cylinder->rgb = parser_vec3(line[5], RGB_ERR);
}

static inline t_obj	*_set_obj_info(t_cylinder cylinder, t_obj_option *option)
{
	t_obj			*obj;

	obj = ft_malloc(sizeof(t_obj));
	obj->type = CY;
	obj->content.cylinder = cylinder;
	obj->get_t = get_cylinder_dist;
	obj->set_r = set_cylinder_record;
	obj->option = option;
	obj->next = NULL;
	return (obj);
}

void	parser_cylinder(char **line)
{
	const int		len = ft_arrlen((void **)line);
	t_obj_option	*option;
	t_cylinder		cylinder;

	if (!(len == 6 || len == 8 || len == 10 || len == 11))
		error_handler(CY_ERR);
	_set_cylinder_info(&cylinder, line);
	option = option_allocator(line, 6, CY_ERR);
	if (!_vaildation_cylinder(&cylinder) || !vaildation_option(option))
	{
		ft_free_all_arr(line);
		error_handler(CY_ERR);
	}
	objsadd_back(&singleton()->objs, _set_obj_info(cylinder, option));
}

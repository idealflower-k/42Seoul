#include "parser_bonus.h"
#include "utils_bonus.h"
#include "render_bonus.h"
#include "design_patterns_bonus.h"

static bool	_vaildation_sphere(t_sphere *sphere)
{
	if (sphere->type != SP)
		return (false);
	if (!check_rgb(&sphere->rgb) || sphere->diameter <= 0)
		return (false);
	return (true);
}

static inline void	_set_sphere_info(t_sphere *sphere, char **line)
{
	sphere->type = SP;
	sphere->center_point = parser_vec3(line[1], POINT_ERR);
	sphere->diameter = check_to_double(line[2]);
	sphere->radius = sphere->diameter / 2;
	sphere->rgb = parser_vec3(line[3], RGB_ERR);
}

static inline t_obj	*_set_obj_info(t_sphere sphere, t_obj_option *option)
{
	t_obj			*obj;

	obj = ft_malloc(sizeof(t_obj));
	obj->type = SP;
	obj->content.sphere = sphere;
	obj->get_t = get_sphere_dist;
	obj->set_r = set_sphere_record;
	obj->option = option;
	obj->next = NULL;
	return (obj);
}

void	parser_sphere(char **line)
{
	const int		len = ft_arrlen((void **)line);
	t_obj_option	*option;
	t_sphere		sphere;

	if (!(len == 4 || len == 6 || len == 8 || len == 9))
		error_handler(SP_ERR);
	_set_sphere_info(&sphere, line);
	option = option_allocator(line, 4, SP_ERR);
	if (!_vaildation_sphere(&sphere) || !vaildation_option(option))
	{
		ft_free_all_arr(line);
		error_handler(SP_ERR);
	}
	objsadd_back(&singleton()->objs, _set_obj_info(sphere, option));
}

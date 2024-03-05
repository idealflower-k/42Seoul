#include "defs.h"
#include "minirt.h"
#include "utils.h"
#include "render.h"

t_vec3	reflect(t_vec3 a, t_vec3 b)
{
	return (vec3_minus(vec3_scalar_multi(b, vec3_inner_product(a, b) * 2), a));
}

bool	in_shadow(t_obj *objs, t_record *record, t_vec3 light_dir,
		double light_len)
{
	const t_ray	light_ray = ray_init(vec3_plus(record->point, \
			vec3_scalar_multi(record->normal_vec3, EPSILON)), light_dir);
	t_record	new_record;

	new_record.t = light_len;
	return (find_obj_in_pixel(objs, (t_ray *)&light_ray, &new_record));
}

#include "tensor.h"

t_vec3	vec3_plus(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_minus(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_multi(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return (vec3_init(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		));
}

double	vec3_inner_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

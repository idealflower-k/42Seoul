#ifndef TENSOR_H
# define TENSOR_H

# include <math.h>
# include <stdbool.h>

# define EPSILON 1e-6

typedef struct s_uv		t_uv;
typedef struct s_vec3	t_vec3;
typedef struct s_vec4	t_vec4;
typedef struct s_mat4	t_mat4;
typedef struct s_mat3	t_mat3;

struct					s_uv
{
	double				u;
	double				v;
};

struct					s_vec3
{
	double				x;
	double				y;
	double				z;
};

struct					s_vec4
{
	double				x;
	double				y;
	double				z;
	double				w;
};

struct					s_mat4
{
	t_vec4				a;
	t_vec4				b;
	t_vec4				c;
	t_vec4				d;
};

struct					s_mat3
{
	t_vec3				a;
	t_vec3				b;
	t_vec3				c;
};

// oper
t_vec3					vec3_init(double x, double y, double z);
t_vec4					vec4_init(double x, double y, double z, double w);
t_vec3					vec3_plus(t_vec3 a, t_vec3 b);
t_vec3					vec3_minus(t_vec3 a, t_vec3 b);
t_vec3					vec3_multi(t_vec3 a, t_vec3 b);
t_vec3					vec3_cross_product(t_vec3 a, t_vec3 b);
double					vec3_inner_product(t_vec3 a, t_vec3 b);

// oper2
t_vec3					vec3_scalar_divide(t_vec3 vec3, double scalar);
t_vec3					vec3_scalar_multi(t_vec3 vec3, double scalar);
t_vec3					vec3_scalar_minus(t_vec3 vec3, double scalar);

// utils
double					vec3_square_length(t_vec3 vec3);
double					vec3_length(t_vec3 vec3);
t_vec3					vec3_unit(t_vec3 vec3);
t_vec3					vec3_scale(t_vec3 vec3, float s);
bool					is_vec3_same(t_vec3 a, t_vec3 b);

// utils2
void					set_ab_axis_from_c(t_vec3 *a, t_vec3 *b,
							const t_vec3 *c);

double					degree_to_radian(double degree);

bool					root_formula(double a, double b, double c,
							double root[2]);
// vec4_oper

t_vec4					vec4_plus(t_vec4 a, t_vec4 b);
t_vec4					vec4_scalar_multi(t_vec4 vec4, double scalar);

//  vec4_utils
t_vec3					vec4_to_vec3(t_vec4 from);

// mat3_init
t_mat3					mat3_init(t_vec3 a, t_vec3 b, t_vec3 c);

// mat3_oper
t_vec3					mat3_vec3_multi(const t_mat3 *matrix,
							const t_vec3 *vec);

#endif

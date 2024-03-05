#ifndef STRUCT_H
# define STRUCT_H

# include "enum.h"
# include "minirt.h"

typedef struct s_mlx_assets	t_mlx_assets;
typedef struct s_vec3		t_rgb;
typedef struct s_ambient	t_ambient;
typedef struct s_ray		t_ray;
typedef struct s_canvas		t_canvas;
typedef struct s_camera		t_camera;
typedef struct s_scene		t_scene;
typedef struct s_spot_light	t_spot_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_vec3		t_point3;
typedef struct s_meta		t_meta;
typedef struct s_record		t_record;
typedef struct s_obj		t_obj;
typedef struct s_quad_coeff	t_quad_coeff;
typedef struct s_hooks		t_hooks;
typedef struct s_img		t_img;

typedef double				(*t_get_obj_dist)(t_obj *, const t_ray *);
typedef t_object_type		(*t_get_obj_record)(t_obj *, const t_ray *,
			t_record *);

struct						s_quad_coeff
{
	double					a;
	double					b;
	double					c;
};

struct						s_img
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
};

struct						s_mlx_assets
{
	void					*mlx;
	void					*win;
	t_img					img;
};

struct						s_ambient
{
	t_object_type			type;
	double					ratio;
	t_rgb					rgb;
};

struct						s_camera
{
	t_object_type			type;
	t_point3				view_point;
	t_vec3					normal_vec3;
	t_vec3					forward;
	t_vec3					up;
	t_vec3					right;
	double					fov;
	double					viewport_h;
	double					viewport_w;
	t_vec3					horizontal;
	t_vec3					vertical;
	double					focal_len;
	t_point3				left_bottom;
	double					pitch;
	double					yaw;
	t_vec3					pos;
};

struct						s_spot_light
{
	t_object_type			type;
	t_point3				light_point;
	double					ratio;
	t_rgb					rgb;
};

struct						s_sphere
{
	t_object_type			type;
	t_point3				center_point;
	double					diameter;
	double					radius;
	t_rgb					rgb;
};

struct						s_plane
{
	t_object_type			type;
	t_point3				point;
	t_vec3					normal_vec3;
	t_rgb					rgb;
};

struct						s_cylinder
{
	t_object_type			type;
	t_cy_type				p_type;
	t_point3				center_point;
	t_vec3					normal_vec3;
	double					diameter;
	double					height;
	t_rgb					rgb;
};

struct						s_ray
{
	t_point3				origin;
	t_vec3					direction;
};

struct						s_record
{
	t_point3				point;
	t_vec3					normal_vec3;
	double					t;
	t_rgb					rgb;
};

struct						s_canvas
{
	int						width;
	int						height;
	double					aspect_ratio;
};

struct						s_scene
{
	t_canvas				canvas;
};

union						u_obj
{
	t_sphere				sphere;
	t_plane					plane;
	t_cylinder				cylinder;
};

struct						s_obj
{
	t_object_type			type;
	t_get_obj_dist			get_t;
	t_get_obj_record		set_r;
	union u_obj				content;
	t_obj					*next;
};

struct						s_hooks
{
	bool					mouse_left;
	bool					mouse_right;
	double					prev_pos[2];
};

struct						s_meta
{
	t_mlx_assets			mlx_assets;
	t_ambient				ambient;
	t_scene					scene;
	t_camera				camera;
	t_hooks					hooks;
	t_list					*spot_lights;
	t_obj					*objs;
	int						fd;
};

#endif

#ifndef RENDER_H
# define RENDER_H

// render
void			render(t_meta *meta);

// sphere
double			get_sphere_dist(t_obj *obj, const t_ray *ray);
t_object_type	set_sphere_record(t_obj *obj, const t_ray *ray,
					t_record *record);

// plane
double			get_plane_dist(t_obj *obj, const t_ray *ray);
t_object_type	set_plane_record(t_obj *obj, const t_ray *ray,
					t_record *record);

// cylinder
double			get_cylinder_dist(t_obj *obj, const t_ray *ray);
t_object_type	set_cylinder_record(t_obj *obj, const t_ray *ray,
					t_record *record);
bool			is_valid_height(double t, t_cylinder *cy, t_ray *ray);
void			get_cylinder_coeff(t_cylinder *cy, t_ray *ray, double *coeff);
void			get_top_bot_t(t_cylinder *cy, t_ray *ray, double *cap_inter);
bool			is_valid_cap(double t, const t_cylinder *cy, const t_ray *ray,
					t_cy_type type);

// ray
t_ray			ray_from_camera(t_camera *camera, const double u,
					const double v);
t_ray			ray_init(t_point3 origin, t_vec3 direction);
t_point3		ray_at(const t_ray *ray, const double t);
void			set_face_normal(const t_ray *ray, t_record *record);

// hit
bool			find_obj_in_pixel(t_obj *objs, const t_ray *ray,
					t_record *record);

#endif

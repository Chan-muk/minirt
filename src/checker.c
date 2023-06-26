#include "minirt.h"

t_color	plane_checkerboard(t_vector p)
{
	double	u;
	double	v;

	u = fract(p.x * 0.2) - 0.5;
	v = fract(p.y * 0.4) - 0.5;
	if (u * v > 0.0)
		return (new_vec(1.0, 1.0, 1.0));
	return (new_vec(0, 0, 0));
}

t_color	shpere_checkerboard(t_vector p, t_hit_array *sp)
{
	double	u;
	double	v;
	double	theta;
	double	phi;
	double	size;

	size = 4;
	theta = atan((p.z - sp->center.z) / (p.x - sp->center.x));
	phi = acos((p.y - sp->center.y) / sp->radius);
	u = 1 - (theta / (2 * M_PI) + 0.5);
	v = 1 - (phi / M_PI);
	u = 0.5 - fract(u * size * 2);
	v = 0.5 - fract(v * size);
	if (u * v < 0.0)
		return (new_color(0, 0, 0));
	return (new_color(1, 1, 1));
}

t_color	cylinder_checkerboard_side(t_vector p, t_hit_array *cy)
{
	double		u;
	double		v;
	t_vector	stdvec1;
	t_vector	stdvec2;
	t_vector	vec_u;

	if (vec_len(vec_prod(cy->norm, new_vec(0, 1, 0))) == 0.0)
		stdvec1 = new_vec(0, 0, 1);
	else
		stdvec1 = unit_vec(vec_prod(cy->norm, new_vec(0, 1, 0)));
	stdvec2 = unit_vec(vec_prod(cy->norm, stdvec1));
	v = vec_dot(vec_sub(p, cy->center), cy->norm);
	vec_u = unit_vec(vec_sub(p, vec_add(cy->center, vec_mul(cy->norm, v))));
	u = atan2(vec_dot(vec_u, stdvec1), vec_dot(vec_u, stdvec2));
	u = 0.5 - fract(u * 4);
	v = 0.5 - fract(v * 4);
	if (u * v < 0.0)
		return (new_color(0, 0, 0));
	return (new_color(1, 1, 1));
}

t_color	cylinder_checkerboard_cap(t_vector p, t_hit_array *cy)
{
	double		u;
	t_vector	stdvec1;
	t_vector	stdvec2;
	t_vector	vec_u;

	if (vec_len(vec_prod(cy->norm, new_vec(0, 1, 0))) == 0.0)
		stdvec1 = new_vec(0, 0, 1);
	else
		stdvec1 = unit_vec(vec_prod(cy->norm, new_vec(0, 1, 0)));
	stdvec2 = unit_vec(vec_prod(cy->norm, stdvec1));
	u = vec_dot(vec_sub(p, cy->center), cy->norm);
	vec_u = unit_vec(vec_sub(p, vec_add(cy->center, vec_mul(cy->norm, u))));
	u = atan2(vec_dot(vec_u, stdvec1), vec_dot(vec_u, stdvec2));
	u = 0.5 - fract(u * 4);
	if (u < 0.0)
		return (new_color(0, 0, 0));
	return (new_color(1, 1, 1));
}

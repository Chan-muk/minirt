/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:19:12 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 13:19:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_cylinder_cap_color(t_hit_array *cy, t_hit_record *rec)
{
	if (cy->flag == _color)
		rec->color = cy->color;
	else if (cy->flag == _checker)
		rec->color = cylinder_checkerboard_cap(rec->p, cy);
	else if (cy->flag == _texture)
		rec->color = cylinder_texture_cap(rec->p, cy);
}

bool	_cylinder_cap(t_vector center, t_hit_array *cy, t_ray *ray, \
t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < rec->tmin)
		return (false);
	numrator = vec_dot(vec_sub(center, ray->org), cy->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	pc = vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), center));
	if ((pc * pc) > (cy->radius * cy->radius) || pc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cy->norm;
	set_face_normal(ray, rec);
	_cylinder_cap_color(cy, rec);
	return (true);
}

bool	cylinder_cap(t_hit_array *cy, t_ray *ray, t_hit_record *rec, \
double root)
{
	t_vector	point_center;
	t_vector	center_height;
	double		height;

	if (check_object_height(cy, ray, root))
		return (false);
	point_center = \
	vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center);
	center_height = vec_mul(cy->norm, cy->height);
	height = vec_dot(point_center, center_height);
	if (height < 0.0)
		return (_cylinder_cap(cy->center, cy, ray, rec));
	if (height > cy->height)
		return (_cylinder_cap(vec_add(cy->center, \
		vec_mul(cy->norm, cy->height)), cy, ray, rec));
	return (false);
}

bool	cylinder_side(double root, t_hit_array *cy, t_ray *ray, \
t_hit_record *rec)
{
	double	height;

	height = vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), \
	cy->center), cy->norm);
	if (root < rec->tmin || rec->tmax < root)
		return (false);
	if (check_object_height(cy, ray, root) == false)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = \
	unit_vec(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), \
	vec_add(cy->center, vec_mul(cy->norm, height))));
	set_face_normal(ray, rec);
	if (cy->flag == _color)
		rec->color = cy->color;
	else if (cy->flag == _checker)
		rec->color = cylinder_checkerboard_side(rec->p, cy);
	else if (cy->flag == _texture)
		rec->color = cylinder_texture_side(rec->p, cy);
	return (true);
}

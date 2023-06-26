/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:18:08 by chajung           #+#    #+#             */
/*   Updated: 2023/05/29 13:18:09 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_cone_data(t_formula *formula, t_hit_array *cone, t_ray *ray)
{
	t_vector	r_height;
	double		h;
	double		m;
	double		vh;
	double		wh;

	r_height = vec_sub(ray->org, vec_add(cone->center, \
	vec_mul(cone->norm, cone->height)));
	h = vec_len(vec_sub(cone->center, vec_add(cone->center, \
	vec_mul(cone->norm, cone->height))));
	m = (cone->radius * cone->radius) / (h * h);
	vh = vec_dot(ray->dir, cone->norm);
	wh = vec_dot(r_height, cone->norm);
	formula->a = vec_dot(ray->dir, ray->dir) - (m * (vh * vh)) - (vh * vh);
	formula->b = vec_dot(ray->dir, r_height) - (m * vh * wh) - (vh * wh);
	formula->c = vec_dot(r_height, r_height) - (m * (wh * wh)) - (wh * wh);
	formula->discriminant = \
	(formula->b * formula->b) - (formula->a * formula->c);
	formula->root_1 = (-formula->b - sqrt(formula->discriminant)) / formula->a;
	formula->root_2 = (-formula->b + sqrt(formula->discriminant)) / formula->a;
}

// t_vector	cone_normal_vector(t_hit_array *cone, t_ray *ray, double root)
// {
// 	t_point		point;
// 	t_point		height;
// 	t_vector	hp_vec;
// 	t_vector	normal_vector;

// 	point = vec_add(ray->org, vec_mul(ray->dir, root));
// 	height = vec_add(cone->center, vec_mul(cone->norm, cone->height));
// 	hp_vec = vec_sub(height, point);
// 	normal_vector = \
// 	vec_sub(hp_vec, vec_mul(ray->dir, ((vec_len(hp_vec) * vec_len(hp_vec)) \
// 	/ vec_dot(hp_vec, ray->dir))));
// 	return (unit_vec(normal_vector));
// }

t_vector	cone_normal_vector(t_hit_array *cone, t_ray *ray, double root)
{
	t_point		point;
	t_point		_point;
	t_point		height;
	t_vector	normal_vector;
	
	point = vec_add(ray->org, vec_mul(ray->dir, root));
	_point = vec_add(cone->center, vec_mul(cone->norm, \
	vec_dot(vec_sub(point, cone->center), cone->norm)));
	height = vec_add(cone->center, vec_mul(cone->norm, cone->height));
	normal_vector = vec_prod(vec_sub(point, height), \
	vec_prod(vec_sub(point, height), vec_sub(point, _point)));
	return (unit_vec(normal_vector));
}

bool	cone_side(t_hit_array *cone, t_ray *ray, t_hit_record *rec, double root)
{
	if (root < rec->tmin || rec->tmax < root)
		return (false);
	if (check_object_height(cone, ray, root) == false)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone_normal_vector(cone, ray, root);
	set_face_normal(ray, rec);
	rec->color = cone->color;
	return (true);
}

// bool	__cone_cap(t_hit_array *cone, t_ray *ray, t_hit_record *rec)
// {
// 	double	numrator;
// 	double	denominator;
// 	double	root;
// 	double	rad;

// 	denominator = vec_dot(ray->dir, cone->norm);
// 	if (fabs(denominator) < rec->tmin)
// 		return (false);
// 	numrator = vec_dot(vec_sub(cone->center, ray->org), cone->norm);
// 	root = numrator / denominator;
// 	if (root < rec->tmin || root > rec->tmax)
// 		return (false);
// 	rad = \
// 	vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cone->center));
// 	if ((rad * rad) > (cone->radius * cone->radius) || rad < 0.0)
// 		return (false);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	rec->normal = cone->norm;
// 	set_face_normal(ray, rec);
// 	rec->color = cone->color;
// 	return (true);
// }

bool	cone_cap(t_hit_array *cone, t_ray *ray, t_hit_record *rec, double height)
{
	if (check_object_height(cone, ray, height))
		return (false);
	// return (__cone_cap(cone, ray, rec));
	double	numrator;
	double	denominator;
	double	root;
	double	rad;

	denominator = vec_dot(ray->dir, cone->norm);
	if (fabs(denominator) < rec->tmin)
		return (false);
	numrator = vec_dot(vec_sub(cone->center, ray->org), cone->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	rad = \
	vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cone->center));
	if ((rad * rad) > (cone->radius * cone->radius) || rad < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone->norm;
	set_face_normal(ray, rec);
	rec->color = cone->color;
	return (true);
}

bool	hit_cone(t_hit_array *cone, t_ray *ray, t_hit_record *rec)
{
	t_formula		formula;
	t_hit_record	rec_backup;
	bool			flag;

	flag = false;
	get_cone_data(&formula, cone, ray);
	if (formula.discriminant < 0.0)
		return (flag);
	if (cone_side(cone, ray, rec, formula.root_1))
		check_data(formula.root_1, &flag, rec, &rec_backup);
	if (cone_side(cone, ray, rec, formula.root_2))
		check_data(formula.root_2, &flag, rec, &rec_backup);
	if (cone_cap(cone, ray, rec, formula.root_1))
		check_data(formula.root_1, &flag, rec, &rec_backup);
	if (cone_cap(cone, ray, rec, formula.root_2))
		check_data(formula.root_2, &flag, rec, &rec_backup);
	return (flag);
}

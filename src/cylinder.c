/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:18:08 by chajung           #+#    #+#             */
/*   Updated: 2023/05/29 13:18:09 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// bool	__test__code(t_vector center, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
// {
// 	double	numrator;
// 	double	denominator;
// 	double	root;
// 	double	pc;

// 	denominator = vec_dot(ray->dir, cy->norm);
// 	if (fabs(denominator) < rec->tmin)
// 		return (false);
// 	numrator = vec_dot(vec_sub(center, ray->org), cy->norm);
// 	root = numrator / denominator;
// 	if (root < rec->tmin || root > rec->tmax)
// 		return (false);
// 	pc = vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), center));
// 	if ((pc * pc) > (cy->radius * cy->radius) || pc < 0.0)
// 		return (false);
// 	return (true);
// }

int	cylinder_upper_cap(t_vector center, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < rec->tmin)
		return (0);
	numrator = vec_dot(vec_sub(center, ray->org), cy->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	pc = vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), center));
	if ((pc * pc) > (cy->radius * cy->radius) || pc < 0.0)
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cy->norm;
	set_face_normal(ray, rec);
	return (1);
}

int	cylinder_lower_cap(t_vector center, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < rec->tmin)
		return (0);
	numrator = vec_dot(vec_sub(center, ray->org), cy->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	pc = vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), center));
	if ((pc * pc) > (cy->radius * cy->radius) || pc < 0.0)
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vec_mul(cy->norm, -1);
	set_face_normal(ray, rec);
	return (1);
}

int	cylinder_cap(t_hit_array *cy, t_ray *ray, t_hit_record *rec, double root)
{
	t_vector	PC;
	t_vector	H;
	double		condition;

	PC = vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center);
	H = vec_mul(cy->norm, cy->height);
	condition = vec_dot(PC, H);
	if (condition < 0.0)
		return (cylinder_lower_cap(cy->center, cy, ray, rec));
	if (condition > cy->height)
		return (cylinder_upper_cap(vec_add(cy->center, vec_mul(cy->norm, cy->height)), cy, ray, rec));
	return (0);
}

int	cylinder_side(t_formula formula, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	double	root;
	double	qc;

	if (formula.discriminant < 0.0)
		return (0);
	root = (-formula.b - sqrt(formula.discriminant)) / formula.a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-formula.b + sqrt(formula.discriminant)) / formula.a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	qc = vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center), cy->norm);
	if (qc > cy->height || qc < 0.0)
		return (cylinder_cap(cy, ray, rec, root));
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = unit_vec(vec_sub(vec_add(cy->center, vec_mul(cy->norm, qc)), \
	vec_add(ray->org, vec_mul(ray->dir, root))));
	set_face_normal(ray, rec);
	rec->albedo = cy->albedo;
	return (1);
}

void	get_cylinder_data(t_formula *formula, t_hit_array *cy, t_ray *ray)
{
	t_vector	r_center;
	double		vh;
	double		wh;

	r_center = vec_sub(ray->org, cy->center);
	vh = vec_dot(ray->dir, unit_vec(vec_mul(cy->norm, cy->height)));
	wh = vec_dot(r_center, unit_vec(vec_mul(cy->norm, cy->height)));
	formula->a = vec_dot(ray->dir, ray->dir) - (vh * vh);
	formula->b = vec_dot(ray->dir, r_center) - (vh * wh);
	formula->c = vec_dot(r_center, r_center) - (wh * wh) - (cy->radius * cy->radius);
	formula->discriminant = (formula->b * formula->b) - (formula->a * formula->c);
}

bool	hit_cylinder(t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	t_formula	formula;

	get_cylinder_data(&formula, cy, ray);
	return (cylinder_side(formula, cy, ray, rec));
}

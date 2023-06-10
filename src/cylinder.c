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

int	cylinder_upper_cap(t_vector center, t_hit_array* cy, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < 0.0000000001)
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

int	cylinder_lower_cap(t_vector center, t_hit_array* cy, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < 0.0000000001)
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
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = unit_vec(vec_sub(vec_add(cy->center, vec_mul(cy->norm, qc)), \
	vec_add(ray->org, vec_mul(ray->dir, root))));
	set_face_normal(ray, rec);
	return (1);
}

void	get_data(t_formula *formula, t_hit_array *cy, t_ray *ray)
{
	formula->a = vec_len_2(vec_prod(ray->dir, cy->norm));
	formula->b = vec_dot(vec_prod(ray->dir, cy->norm), vec_prod(vec_sub(ray->org, cy->center), cy->norm));
	formula->c = vec_len_2(vec_prod(vec_sub(ray->org, cy->center), cy->norm)) - (cy->radius * cy->radius);
	formula->discriminant = (formula->b * formula->b) - (formula->a * formula->c);
	formula->denominator = vec_dot(ray->dir, cy->norm);
}

bool	hit_cylinder(t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	t_formula	formula;
	int			flag;

	get_data(&formula, cy, ray);
	flag = 0;
	
	flag += cylinder_upper_cap(vec_add(cy->center, vec_mul(cy->norm, cy->height)), cy, ray, rec);
	flag += cylinder_lower_cap(cy->center, cy, ray, rec);
	flag += cylinder_side(formula, cy, ray, rec);
	if (flag)
		return (true);
	return(false);
}

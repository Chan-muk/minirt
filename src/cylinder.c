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

bool	cylinder_cap(t_hit_array* cy, t_vector c, t_ray *r, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(r->dir, cy->norm);
	if (fabs(denominator) < 0.0000000001)
		return (false);
	numrator = vec_dot(vec_sub(c, r->org), cy->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	t_vector	P = vec_add(r->org, vec_mul(r->dir, root));
	double		pc = vec_len(vec_sub(P, c));
	if (pc * pc > (cy->radius * 0.5) * (cy->radius * 0.5) || pc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(r, root);
	rec->normal = cy->norm;
	set_face_normal(r, rec);
	return (true);
}

bool	cylinder_side(t_hit_array *cy, t_ray *r, t_hit_record *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	a = vec_len_2(vec_prod(r->dir, cy->norm));
	half_b = vec_dot(vec_prod(r->dir, cy->norm), vec_prod(vec_sub(r->org, cy->center), cy->norm));
	c = vec_len_2(vec_prod(vec_sub(r->org, cy->center), cy->norm)) - ( cy->radius * 0.5) * (cy->radius * 0.5);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	t_vector	P = vec_add(r->org, vec_mul(r->dir, root));
	double		qc = vec_dot(vec_sub(P, cy->center), cy->norm);
	if (qc > cy->height || qc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(r, root);
	rec->normal = cy->norm;
	set_face_normal(r, rec);
	return (true);
}

bool	hit_cylinder(t_hit_array *cy, t_ray *r, t_hit_record *rec)
{
	int	flag = 0;
	if (cylinder_side(cy, r, rec))
		flag++;
	t_vector	H = vec_add(cy->center, vec_mul(cy->norm, cy->height));
	if (cylinder_cap(cy, H, r, rec))
		flag++;
	if (cylinder_cap(cy, cy->center, r, rec))
		flag++;
	if (flag)
		return (true);
	return(false);
}


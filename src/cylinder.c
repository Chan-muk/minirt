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
	formula->c = \
	vec_dot(r_center, r_center) - (wh * wh) - (cy->radius * cy->radius);
	formula->discriminant = \
	(formula->b * formula->b) - (formula->a * formula->c);
	formula->root_1 = \
	(-formula->b - sqrt(formula->discriminant)) / formula->a;
	formula->root_2 = \
	(-formula->b + sqrt(formula->discriminant)) / formula->a;
}

static void	check_data(double root, bool *flag, t_hit_record *rec, \
t_hit_record *rec_backup)
{
	if (*flag == true && rec_backup->t < rec->t)
		data_backup(rec, rec_backup);
	else
	{
		data_backup(rec_backup, rec);
		*flag = true;
	}
}

bool	hit_cylinder(t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	t_formula		formula;
	t_hit_record	rec_backup;
	bool			flag;

	flag = false;
	get_cylinder_data(&formula, cy, ray);
	if (formula.discriminant < 0.0)
		return (flag);
	if (cylinder_side(formula.root_1, cy, ray, rec))
		check_data(formula.root_1, &flag, rec, &rec_backup);
	if (cylinder_side(formula.root_2, cy, ray, rec))
		check_data(formula.root_2, &flag, rec, &rec_backup);
	if (cylinder_cap(cy, ray, rec, formula.root_1))
		check_data(formula.root_1, &flag, rec, &rec_backup);
	if (cylinder_cap(cy, ray, rec, formula.root_2))
		check_data(formula.root_2, &flag, rec, &rec_backup);
	return (flag);
}

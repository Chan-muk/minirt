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
	formula->c = vec_dot(r_center, r_center) - (wh * wh) - (cy->radius * cy->radius);
	formula->discriminant = (formula->b * formula->b) - (formula->a * formula->c);
	formula->root_1 = (-formula->b - sqrt(formula->discriminant)) / formula->a;
	formula->root_2 = (-formula->b + sqrt(formula->discriminant)) / formula->a;
}

void	data_backup(t_hit_record *rec_backup, t_hit_record *rec)
{
	rec_backup->albedo = rec->albedo;
	rec_backup->front_face = rec->front_face;
	rec_backup->normal = rec->normal;
	rec_backup->p = rec->p;
	rec_backup->t = rec->t;
	rec_backup->tmax = rec->tmax;
	rec_backup->tmin = rec->tmin;
}

bool	check_cylinder_height(t_hit_array *cy, t_ray *ray, double root)
{
	double	point_on_line;

	point_on_line = \
	vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center), cy->norm);
	if (point_on_line < 0.0 || point_on_line > cy->height)
		return (false);
	return (true);
}

bool	cylinder_upper_cap(t_vector center, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
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
	rec->albedo = cy->albedo;
	return (true);
}

bool	cylinder_lower_cap(t_vector center, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
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
	rec->normal = vec_mul(cy->norm, -1);
	set_face_normal(ray, rec);
	rec->albedo = cy->albedo;
	return (true);
}

bool	cylinder_cap(t_hit_array *cy, t_ray *ray, t_hit_record *rec, double root)
{
	t_vector	PC;
	t_vector	H;
	double		condition;

	if (check_cylinder_height(cy, ray, root))
		return (false);
	PC = vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center);
	H = vec_mul(cy->norm, cy->height);
	condition = vec_dot(PC, H);
	if (condition < 0.0)
		return (cylinder_lower_cap(cy->center, cy, ray, rec));
	if (condition > cy->height)
		return (cylinder_upper_cap(vec_add(cy->center, vec_mul(cy->norm, cy->height)), cy, ray, rec));
	return (false);
}

bool	cylinder_side(t_formula formula, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	double	root;
	double	qc;

	root = (-formula.b - sqrt(formula.discriminant)) / formula.a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-formula.b + sqrt(formula.discriminant)) / formula.a;
		if (root < rec->tmin || rec->tmax < root)
			return (false);
	}
	qc = vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center), cy->norm);
	if (qc > cy->height || qc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = \
	unit_vec(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), vec_add(cy->center, vec_mul(cy->norm, qc))));
	set_face_normal(ray, rec);
	rec->albedo = cy->albedo;
	return (true);
}

bool	_cylinder_side(double root, t_formula formula, t_hit_array *cy, t_ray *ray, t_hit_record *rec)
{
	double qc = vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cy->center), cy->norm);

	if (root < rec->tmin || rec->tmax < root)
		return (false);
	if (check_cylinder_height(cy, ray, root) == false)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = \
	unit_vec(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), vec_add(cy->center, vec_mul(cy->norm, qc))));
	set_face_normal(ray, rec);
	rec->albedo = cy->albedo;
	return (true);
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
	if (_cylinder_side(formula.root_1, formula, cy, ray, rec))
	{
		data_backup(&rec_backup, rec);
		flag = true;
	}
	if (_cylinder_side(formula.root_2, formula, cy, ray, rec))
	{
		if (flag == true && rec_backup.t < rec->t)
			data_backup(rec, &rec_backup);
		else
		{
			data_backup(&rec_backup, rec);
			flag = true;
		}
	}
	if (cylinder_cap(cy, ray, rec, formula.root_1))
	{
		if (flag == true && rec_backup.t < rec->t)
			data_backup(rec, &rec_backup);
		else
		{
			data_backup(&rec_backup, rec);
			flag = true;
		}
	}
	if (cylinder_cap(cy, ray, rec, formula.root_2))
	{
		if (flag == true && rec_backup.t < rec->t)
			data_backup(rec, &rec_backup);
		else
		{
			data_backup(&rec_backup, rec);
			flag = true;
		}
	}
	return (flag);
}

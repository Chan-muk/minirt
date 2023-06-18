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

void	get_cone_data(t_formula *formula, t_hit_array *cone, t_ray *ray)
{
	t_vector	r_height;
	double		h;
	double		m;
	double		vh;
	double		wh;

	r_height = vec_sub(ray->org, vec_add(cone->center, vec_mul(cone->norm, cone->height)));
	h = vec_len(vec_sub(cone->center, vec_add(cone->center, vec_mul(cone->norm, cone->height))));
	m = (cone->radius * cone->radius) / (h * h);
	vh = vec_dot(ray->dir, cone->norm);
	wh = vec_dot(r_height, cone->norm);

	formula->a = vec_dot(ray->dir, ray->dir) - (m * (vh * vh)) - (vh * vh);
	formula->b = vec_dot(ray->dir, r_height) - (m * vh * wh) - (vh * wh);
	formula->c = vec_dot(r_height, r_height) - (m * (wh * wh)) - (wh * wh);
	formula->discriminant = (formula->b * formula->b) - (formula->a * formula->c);
	formula->root_1 = (-formula->b - sqrt(formula->discriminant)) / formula->a;
	formula->root_2 = (-formula->b + sqrt(formula->discriminant)) / formula->a;
}

t_vector	cone_normal_vector(t_hit_array *cone, t_ray *ray, double root)
{
	t_point		point;
	t_point		height;
	t_vector	hp_vec;
	t_vector	normal_vector;

	point = vec_add(ray->org, vec_mul(ray->dir, root));
	height = vec_add(cone->center, vec_mul(cone->norm, cone->height));
	hp_vec = vec_sub(height, point);
	normal_vector = \
	vec_sub(hp_vec, vec_mul(ray->dir, ((vec_len(hp_vec) * vec_len(hp_vec)) \
	/ vec_dot(hp_vec, ray->dir))));
	return (normal_vector);
}

bool	cone_side(t_hit_array *cone, t_ray *ray, t_hit_record *rec, double root)
{
	if (root < rec->tmin || rec->tmax < root)
		return (false);
	if (check_object_height(cone, ray, root) == false)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = unit_vec(cone_normal_vector(cone, ray, root));
	set_face_normal(ray, rec);
	rec->albedo = cone->albedo;
	return (true);
}

bool	__cone_cap(t_hit_array* cone, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cone->norm);
	if (fabs(denominator) < rec->tmin)
		return (false);
	numrator = vec_dot(vec_sub(cone->center, ray->org), cone->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	pc = vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cone->center));
	if ((pc * pc) > (cone->radius * cone->radius) || pc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone->norm;
	set_face_normal(ray, rec);
	rec->albedo = cone->albedo;
	return (true);
}

bool	cone_cap(t_hit_array *cone, t_ray *ray, t_hit_record *rec, double root)
{
	t_vector	point_center;
	t_vector	center_height;;
	double		height;

	if (check_object_height(cone, ray, root))
		return (false);
	// point_center = vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cone->center);
	// center_height = vec_mul(cone->norm, cone->height);
	// height = vec_dot(point_center, center_height);

	// if (height < 0.0)
	// 	return (__cone_cap(cone, ray, rec));
	return (__cone_cap(cone, ray, rec));
	return (false);
	// printf("fail\n");
	// if (height > cone->height)
	// 	return (__cone_cap(cone, ray, rec));;
	// 	return (__cylinder_cap(vec_add(cy->center, vec_mul(cy->norm, cy->height)), cy, ray, rec));
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
	{
		data_backup(&rec_backup, rec);
		flag = true;
	}
	if (cone_side(cone, ray, rec, formula.root_2))
	{
		if (flag == true && rec_backup.t < rec->t)
			data_backup(rec, &rec_backup);
		else
		{
			data_backup(&rec_backup, rec);
			flag = true;
		}
	}
	if (cone_cap(cone, ray, rec, formula.root_1))
	{
		if (flag == true && rec_backup.t < rec->t)
			data_backup(rec, &rec_backup);
		else
		{
			data_backup(&rec_backup, rec);
			flag = true;
		}
	}
	if (cone_cap(cone, ray, rec, formula.root_2))
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

// bool	cone_cap(t_hit_array *cone, t_ray *ray, t_hit_record *rec, double root)
// {
// 	if (check_object_height(cone, ray, root))
// 		return (false);
	
// 	double	numrator;
// 	double	denominator;
// 	double	__root;

// 	t_vector	PC;
// 	t_vector	H;
// 	double		condition;

// 	PC = vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cone->center);
// 	H = vec_mul(cone->norm, cone->height);
// 	condition = vec_dot(PC, H);
// 	if (!(condition < 0.0))
// 		return (false);

// 	denominator = vec_dot(ray->dir, cone->norm);
// 	if (fabs(denominator) < rec->tmin)
// 		return (false);
// 	numrator = vec_dot(vec_sub(cone->center, ray->org), cone->norm);
// 	__root = numrator / denominator;
// 	if (__root < rec->tmin || __root > rec->tmax)
// 		return (false);


// 	t_vector	P = vec_add(ray->org, vec_mul(ray->dir, __root));
// 	double		pc = vec_len(vec_sub(P, cone->center));
// 	if ((pc * pc) > (cone->radius * cone->radius) || pc < 0.0)
// 		return (false);
// 	rec->t = __root;
// 	rec->p = ray_at(ray, __root);
// 	rec->normal = cone->norm;
// 	set_face_normal(ray, rec);
// 	return (true);
// }

// bool	cone_side(t_hit_array *cone, t_ray *ray, t_hit_record *rec)
// {
// 	// double	a;
// 	// double	half_b;
// 	// double	c;
// 	double	discriminant;
// 	double	root;

// 	t_vector	H = vec_add(cone->center, vec_mul(cone->norm, cone->height));
// 	double		h = vec_len(vec_sub(cone->center, H));
// 	double		m = (cone->radius * cone->radius) / (h * h);
// 	t_vector	w = vec_sub(ray->org, H);

// 	double		vh = vec_dot(ray->dir, cone->norm);
// 	double		wh = vec_dot(w, cone->norm);

// 	// a = vec_dot(ray->dir, ray->dir) - (m - 1) * (vec_dot(ray->dir, cone->norm) * vec_dot(ray->dir, cone->norm));
// 	// half_b = vec_dot(ray->dir, w) - (m - 1) * (vec_dot(ray->dir, cone->norm) * vec_dot(w, cone->norm));
// 	// c = vec_dot(w, w) - (m - 1) * (vec_dot(w, cone->norm) * vec_dot(w, cone->norm));
	
// 	double a = vec_dot(ray->dir, ray->dir) - (m * (vh * vh)) - (vh * vh);
// 	double half_b = vec_dot(ray->dir, w) - (m * vh * wh) - (vh * wh);
// 	double c = vec_dot(w, w) - (m * (wh * wh)) - (wh * wh);


// 	discriminant = half_b * half_b - a * c;
// 	// if (discriminant < 0)
// 	// 	return (false);
// 	// root = (-half_b - sqrt(discriminant)) / a;
// 	// if (root < rec->tmin || root > rec->tmax)
// 	// 	return (false);
	
// 	if (discriminant < 0.0)
// 		return (false);
// 	root = (-half_b - sqrt(discriminant)) / a;
// 	if (root < rec->tmin || rec->tmax < root)
// 	{
// 		root = (-half_b + sqrt(discriminant)) / a;
// 		if (root < rec->tmin || rec->tmax < root)
// 			return (false);
// 	}

// 	t_vector	P = vec_add(ray->org, vec_mul(ray->dir, root));
// 	double		qc = vec_dot(vec_sub(P, cone->center), cone->norm);
// 	if (qc > cone->height || qc < 0.0)
// 		return (false);
	
// 	t_vector	Q = vec_add(cone->center, vec_mul(cone->norm, qc));

// 	t_vector	PH = vec_sub(P, H);
// 	t_vector	PQ = vec_sub(P, Q);
// 	t_vector	C1 = vec_prod(PH, PQ);
// 	t_vector	PP = vec_prod(PH, C1);
// 	// if (qc > cone->height || qc < 0.0 || -vec_dot(cone->norm, PP) < 0)
// 	// 	return (cone_cap(cone, cone->center, ray, rec));

// 	// if (qc > cone->height || qc < 0.0)
// 	// 	return (cone_cap(cone, cone->center, ray, rec));

// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	// rec->normal = PP;
// 	rec->normal = vec_mul(PP, -1);
// 	// rec->normal = cone->norm;
// 	// rec->normal = \
// 	// unit_vec(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), vec_add(cone->center, vec_mul(cone->norm, qc))));
// 	// set_face_normal(ray, rec);

// 	set_face_normal(ray, rec);
// 	rec->albedo = cone->albedo;
// 	return (true);
// }
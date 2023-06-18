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

void	__data_backup(t_hit_record *rec_backup, t_hit_record *rec)
{
	rec_backup->albedo = rec->albedo;
	rec_backup->front_face = rec->front_face;
	rec_backup->normal = rec->normal;
	rec_backup->p = rec->p;
	rec_backup->t = rec->t;
	rec_backup->tmax = rec->tmax;
	rec_backup->tmin = rec->tmin;
}

bool	cone_cap(t_hit_array* cone, t_vector c, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(ray->dir, cone->norm);
	if (fabs(denominator) < 0.0000000001)
		return (false);
	numrator = vec_dot(vec_sub(c, ray->org), cone->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	t_vector	P = vec_add(ray->org, vec_mul(ray->dir, root));
	double		pc = vec_len(vec_sub(P, c));
	if (pc * pc > (cone->radius * 0.5) * (cone->radius * 0.5) || pc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone->norm;
	set_face_normal(ray, rec);
	return (true);
}

bool	__cone_side(double root, t_hit_array *cone, t_ray *ray, t_hit_record *rec)
{
	t_point		P = vec_add(ray->org, vec_mul(ray->dir, root));
	double		qc = vec_dot(vec_sub(P, cone->center), cone->norm);
	t_point		Q = vec_add(cone->center, vec_mul(cone->norm, qc));
	t_point		H = vec_add(cone->center, vec_mul(cone->norm, cone->height));
	t_vector	PH = vec_sub(P, H);
	t_vector	PQ = vec_sub(P, Q);
	t_vector	C1 = vec_prod(PH, PQ);
	t_vector	PP = unit_vec(vec_prod(PH, C1));

	t_vector	normal_vector;

	normal_vector = vec_prod(vec_sub(P, H), vec_prod(PH, PQ));


	if (root < rec->tmin || rec->tmax < root)
		return (false);
	if (qc > cone->height || qc < 0.0)
		return (false);

	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = unit_vec(normal_vector);
	set_face_normal(ray, rec);
	rec->albedo = cone->albedo;
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

	if (__cone_side(formula.root_1, cone, ray, rec))
	{
		__data_backup(&rec_backup, rec);
		flag = true;
	}
	// if (__cone_side(formula.root_2, formula, cone, ray, rec))
	// {
	// 	if (flag == true && rec_backup.t < rec->t)
	// 		__data_backup(rec, &rec_backup);
	// 	else
	// 	{
	// 		__data_backup(&rec_backup, rec);
	// 		flag = true;
	// 	}
	// }
	return (flag);
}

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
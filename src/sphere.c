/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:53:47 by chajung           #+#    #+#             */
/*   Updated: 2023/05/22 13:53:48 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	// 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	// 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
	rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}

t_bool		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc;
	double	a;
	// double	b; b를 half_b로 변경
	double	half_b;
	double	c;
	double	discriminant; //판별식
	double	sqrtd;
	double	root;

	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	//두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
	set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
	return (TRUE);
}

t_sphere	sphere(t_point3 center, double radius)
{
	t_sphere sp;

	sp.center = center;
	sp.radius = radius;
	sp.radius2 = radius * radius;
	return (sp);
}

// bool	hit_sphere(void *this, t_hitarg arg)
// {
// 	t_sphere	*sphere;
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	double		root;

// 	sphere = (t_sphere *)this;
// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
// 	discriminant = (b * b) - (a * c);
// 	if (discriminant < 0.0)
// 		return (false);
// 	root = (-b - sqrt(discriminant)) / a;
// 	if (root < arg.min || arg.max < root) {
// 		root = (-b + sqrt(discriminant)) / a;
// 		if (root < arg.min || arg.max < root)
// 			return (false);
// 	}
// 	arg.rec->t = root;
// 	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
// 	t_vector	outward_normal;
// 	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
// 	arg.rec->mat_ptr = sphere->mat_ptr;
// 	return (true);
// }


// double	get_find_root_1(t_sphere *sphere, t_hitarg arg, double discriminant)
// {
// 	t_vector	r_center;
// 	double		a;
// 	double		b;

// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	return ((-b - sqrt(discriminant)) / a);
// }

// double	get_find_root_2(t_sphere *sphere, t_hitarg arg, double discriminant)
// {
// 	t_vector	r_center;
// 	double		a;
// 	double		b;

// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	return ((-b + sqrt(discriminant)) / a);
// }

// double	get_sphere_discriminant(t_sphere *sphere, t_hitarg arg)
// {
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
	
// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
// 	discriminant = (b * b) - (a * c);
// 	return (discriminant);
// }

// bool	hit_sphere(void *this, t_hitarg arg)
// {
// 	t_sphere	*sphere;
// 	t_vector	outward_normal;
// 	double		discriminant;
// 	double		root;

// 	sphere = (t_sphere *)this;
// 	discriminant = get_sphere_discriminant(sphere, arg);
// 	if (discriminant < 0.0)
// 		return (false);
// 	root = get_find_root_1(sphere, arg, discriminant);
// 	if (root < arg.min || arg.max < root)
// 	{
// 		root = get_find_root_2(sphere, arg, discriminant);
// 		if (root < arg.min || arg.max < root)
// 			return (false);
// 	}
// 	arg.rec->t = root;
// 	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
// 	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
// 	arg.rec->mat_ptr = sphere->mat_ptr;
// 	return (true);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:50:39 by chajung           #+#    #+#             */
/*   Updated: 2023/05/22 13:50:40 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Chapter 9.4.: Mirrored Light Reflection */
t_vector	reflect(t_vector vec_1, t_vector vec_2)
{
	return (cal_subtract_vec(vec_1, cal_multiply_vec(vec_2, 2 * cal_inner_vec(vec_1, vec_2))));
}

bool	scatter_metal(void *this, struct s_material_arg arg)
{
	t_metal		*metal;
	t_vector	reflected;
	t_ray		ray;
	
	metal = (t_metal *)this;
	reflected = reflect(unit_vec(arg.ray_in->dir), arg.rec->normal);
	*arg.scattered = new_ray(arg.rec->p, reflected);
	*arg.attenuation = metal->albedo;
	if (cal_inner_vec(arg.scattered->dir, arg.rec->normal) > 0)
		return (true);
	else
		return (false);
}
/* Chapter 9.4.: Mirrored Light Reflection */

/* Chapter 9.3.: Modeling Light Scatter and Reflectance */
bool	near_zero(void *this)
{	// Returns true if the vector is very close to zero in all dimensions
	t_vector	*vec;
	double 		s;

	vec = (t_vector *)this;
	s = 0.00000001;
	return (fabs(vec->x) < s) && (fabs(vec->y) < s) && (fabs(vec->z) < s);
}

bool	scatter_lambertian(void *this, t_material_arg arg)
{
	t_vector		scatter_direction;
	t_lambertian	*lambertian;

	lambertian = (t_lambertian *)this;
	scatter_direction = cal_add_vec(arg.rec->normal, random_unit_vecter());
	if (near_zero(&scatter_direction))
		scatter_direction = arg.rec->normal;
	*arg.scattered = new_ray(arg.rec->p, scatter_direction);
	*arg.attenuation = lambertian->albedo;
	return (true);
}
/* Chapter 9.3.: Modeling Light Scatter and Reflectance */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:46:19 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 13:46:20 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	bumprotatevector(t_vector normal, t_vector bump)
{
	const t_vector	stdvec = {0, 0, 1};
	const double	theta = acos(vec_dot(stdvec, unit_vec(normal)));
	t_vector		axis;
	double			rot[3][3];
	t_vector		rotvec;

	if (vec_len(vec_prod(stdvec, unit_vec(normal))) == 0.0)
		return (unit_vec(normal));
	axis = unit_vec(vec_prod(stdvec, unit_vec(normal)));
	bump = unit_vec(bump);
	rot[0][0] = cos(theta) + axis.x * axis.x * (1 - cos(theta));
	rot[0][1] = axis.x * axis.y * (1 - cos(theta)) - axis.z * sin(theta);
	rot[0][2] = axis.x * axis.z * (1 - cos(theta)) + axis.y * sin(theta);
	rot[1][0] = axis.y * axis.x * (1 - cos(theta)) + axis.z * sin(theta);
	rot[1][1] = cos(theta) + axis.y * axis.y * (1 - cos(theta));
	rot[1][2] = axis.y * axis.z * (1 - cos(theta)) - axis.x * sin(theta);
	rot[2][0] = axis.z * axis.x * (1 - cos(theta)) - axis.y * sin(theta);
	rot[2][1] = axis.z * axis.y * (1 - cos(theta)) + axis.x * sin(theta);
	rot[2][2] = cos(theta) + axis.z * axis.z * (1 - cos(theta));
	rotvec.x = rot[0][0] * bump.x + rot[0][1] * bump.y + rot[0][2] * bump.z;
	rotvec.y = rot[1][0] * bump.x + rot[1][1] * bump.y + rot[1][2] * bump.z;
	rotvec.z = rot[2][0] * bump.x + rot[2][1] * bump.y + rot[2][2] * bump.z;
	return (rotvec);
}

void	shpere_bump(t_vector p, t_hit_array *sp, t_hit_record *rec)
{
	t_uvbox	o;

	o.stdvec1 = new_vec(0, 0, 1);
	o.stdvec2 =	new_vec(1, 0, 0);
	sp->norm = new_vec(0, 1, 0);
	o.v = (vec_dot(vec_sub(p, sp->center), sp->norm));
	o.vec_u = unit_vec(vec_sub(p, vec_add(sp->center, vec_mul(sp->norm, o.v))));
	o.u = -atan2(vec_dot(o.vec_u, o.stdvec1), \
	vec_dot(o.vec_u, o.stdvec2)) / (M_PI * 2);
	if (o.u > 0.0)
		o.i = ((int)(sp->texture.w * o.u) + \
	(int)(sp->texture.h * o.v) * sp->texture.w) * 3;
	else
		o.i = ((int)(sp->texture.w * o.u) + \
	(int)(sp->texture.h * o.v + 1) * sp->texture.w) * 3;
	o.v = 1 - acos(o.v / sp->radius) / M_PI;
	o.i = ((int)(sp->bump_map.w * o.u) + \
	(int)(sp->bump_map.h * o.v) * sp->bump_map.w) * 3;
	o.addr = sp->bump_map.addr;
	o.bump = new_vec(o.addr[o.i + 2] / 255.0, o.addr[o.i + 1] / 255.0, o.addr[o.i] / 255.0);
	o.bump = new_vec((o.bump.x - 0.5) * 2, (o.bump.y - 0.5) * 2, (o.bump.z - 0.5) * 2);
	rec->normal = bumprotatevector(rec->normal, o.bump);
}

void	plane_bump(t_vector p, t_hit_array *pl, t_hit_record *rec)
{
	t_uvbox	o;

	if (vec_len(vec_prod(pl->norm, new_vec(0, 1, 0))) == 0.0)
		o.stdvec1 = new_vec(0, 0, 1);
	else
		o.stdvec1 = unit_vec(vec_prod(pl->norm, new_vec(0, 1, 0)));
	o.stdvec2 = unit_vec(vec_prod(pl->norm, o.stdvec1));
	o.u = fract(vec_dot(p, o.stdvec1) * 0.2);
	o.v = fract(vec_dot(p, o.stdvec2) * 0.2);
	o.i = ((int)(pl->bump_map.w * o.u) + \
	(int)(pl->bump_map.h * o.v) * pl->bump_map.w) * 3;
	o.addr = pl->bump_map.addr;
	o.bump = new_vec(o.addr[o.i + 2] / 255.0, o.addr[o.i + 1] / 255.0, o.addr[o.i] / 255.0);
	o.bump = new_vec((o.bump.x - 0.5) * 2, (o.bump.y - 0.5) * 2, (o.bump.z - 0.5) * 2);
	rec->normal = bumprotatevector(rec->normal, o.bump);
}

void	cylinder_bump_side(t_vector p, t_hit_array *cy, t_hit_record *rec)
{
	t_uvbox	o;

	if (vec_len(vec_prod(cy->norm, new_vec(0, 1, 0))) == 0.0)
		o.stdvec1 = new_vec(0, 0, 1);
	else
		o.stdvec1 = unit_vec(vec_prod(cy->norm, new_vec(0, 1, 0)));
	o.stdvec2 = unit_vec(vec_prod(cy->norm, o.stdvec1));
	o.v = (vec_dot(vec_sub(p, cy->center), cy->norm));
	o.vec_u = unit_vec(vec_sub(p, vec_add(cy->center, vec_mul(cy->norm, o.v))));
	o.u = -atan2(vec_dot(o.vec_u, o.stdvec1), \
	vec_dot(o.vec_u, o.stdvec2)) / (M_PI * 2);
	o.v /= cy->height;
	if (o.u > 0.0)
		o.i = ((int)(cy->bump_map.w * o.u) + \
	(int)(cy->bump_map.h * o.v) * cy->bump_map.w) * 3;
	else
		o.i = ((int)(cy->bump_map.w * o.u) + \
	(int)(cy->bump_map.h * o.v + 1) * cy->bump_map.w) * 3;
	o.addr = cy->bump_map.addr;
	o.bump = new_vec(o.addr[o.i + 2] / \
	255.0, o.addr[o.i + 1] / 255.0, o.addr[o.i] / 255.0);
	o.bump = \
	new_vec((o.bump.x - 0.5) * 2, (o.bump.y - 0.5) * 2, (o.bump.z - 0.5) * 2);
	rec->normal = bumprotatevector(rec->normal, o.bump);
}

void	cylinder_bump_cap(t_vector p, t_hit_array *cy, t_hit_record *rec)
{
	t_uvbox	o;

	if (vec_len(vec_prod(cy->norm, new_vec(0, 1, 0))) == 0.0)
		o.stdvec1 = new_vec(0, 0, 1);
	else
		o.stdvec1 = unit_vec(vec_prod(cy->norm, new_vec(0, 1, 0)));
	o.stdvec2 = unit_vec(vec_prod(cy->norm, o.stdvec1));
	o.v = (vec_dot(vec_sub(p, cy->center), cy->norm));
	o.vec_u = unit_vec(vec_sub(p, vec_add(cy->center, vec_mul(cy->norm, o.v))));
	o.u = -atan2(vec_dot(o.vec_u, o.stdvec1), \
	vec_dot(o.vec_u, o.stdvec2)) / (M_PI * 2);
	o.v /= cy->height;
	if (o.v < 0.5)
		o.i = ((int)(cy->texture.w * o.u) + 1 * cy->texture.w) * 3;
	else
		o.i = ((int)(cy->texture.w * o.u) + \
		(cy->texture.h - 1) * cy->texture.w) * 3;
	o.addr = cy->bump_map.addr;
	o.bump = new_vec(o.addr[o.i + 2] / \
	255.0, o.addr[o.i + 1] / 255.0, o.addr[o.i] / 255.0);
	o.bump = \
	new_vec((o.bump.x - 0.5) * 2, (o.bump.y - 0.5) * 2, (o.bump.z - 0.5) * 2);
	rec->normal = bumprotatevector(rec->normal, o.bump);
}

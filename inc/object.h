/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:18:46 by chajung           #+#    #+#             */
/*   Updated: 2023/06/10 11:18:50 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_formula	t_formula;
typedef struct s_hit_record	t_hit_record;
typedef struct s_hit_array	t_hit_array;

struct s_formula
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vector	center;
	double	center_h;
	// double	numrator;
	double	denominator;
};

struct s_hit_record
{
	t_point		p;
	t_vector	normal;
	double		tmin;
	double		tmax;
	double		t;
	bool		front_face;
};

struct s_hit_array
{
	int			type;
	t_vector	center;
	t_vector	norm;
	t_vector	color;
	double		radius;
	double		height;
};

bool	hit_sphere(t_hit_array *sp, t_ray *ray, t_hit_record *rec);
bool	hit_world(t_hit_array *array, t_ray *r, t_hit_record *rec);
void	set_face_normal(t_ray *r, t_hit_record *rec);
bool	hit_cylinder(t_hit_array *cy, t_ray *r, t_hit_record *rec);
bool	hit_plane(t_hit_array *pl, t_ray *r, t_hit_record *rec);

#endif

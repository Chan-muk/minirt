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
typedef	struct s_scene		t_scene;

struct s_formula
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root_1;
	double	root_2;
};

struct s_hit_record
{
	t_point		p;
	t_vector	normal;
	double		tmin;
	double		tmax;
	double		t;
	bool		front_face;
	t_vector	albedo;
};

struct s_hit_array
{
	int			type;
	t_vector	center;
	t_vector	norm;
	t_vector	color;
	double		radius;
	double		height;
	t_vector	light_color;
	double		bright_ratio;
	t_vector	albedo;
};

bool	hit_sphere(t_hit_array *sp, t_ray *ray, t_hit_record *rec);
bool	hit_world(t_scene *scene);
void	set_face_normal(t_ray *r, t_hit_record *rec);
bool	hit_cylinder(t_hit_array *cy, t_ray *r, t_hit_record *rec);
bool	hit_plane(t_hit_array *pl, t_ray *r, t_hit_record *rec);
bool	hit_cone(t_hit_array *cone, t_ray *ray, t_hit_record *rec);

#endif

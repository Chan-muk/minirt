/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:05:42 by chajung           #+#    #+#             */
/*   Updated: 2023/04/23 12:05:43 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* renewal */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

# include "mlx.h"
# include "structure.h"
# include "../libft/inc/libft.h"

bool	hit_sphere(t_hitarray *sp, t_ray *ray, t_hit_record *rec);
bool	hit_world(t_hitarray *array, t_ray *r, t_hit_record *rec);
void	set_face_normal(t_ray *r, t_hit_record *rec);
bool	hit_cylinder(t_hitarray *cy, t_ray *r, t_hit_record *rec);
bool	hit_plane(t_hitarray* pl, t_ray *r, t_hit_record *rec);

/* init */
void		initialize(int argc, char **argv, t_mlx *mlx);

/* hooks */
void		set_hooks(t_mlx *mlx);

/* utils */
void		exit_with_str(const char *str, int exit_code);

/* color */
void	color_window(t_mlx *mlx);

/* sphere */
t_sphere	sphere(t_point center, double radius);
// bool		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);

/* cal */
t_vector		new_vec(double x, double y, double z);
t_point	new_point(double x, double y, double z);
t_point	new_color(double r, double g, double b);
void		set_vec(t_vector *vec, double x, double y, double z);
double		vec_len_2(t_vector vec);
double		vec_len(t_vector vec);
t_vector		vec_add(t_vector vec, t_vector vec2);
t_vector		vec_add_(t_vector vec, double x, double y, double z);
t_vector		vec_sub(t_vector vec, t_vector vec2);
t_vector		vec_sub_(t_vector vec, double x, double y, double z);
t_vector		vec_mul(t_vector vec, double t);
t_vector		vec_mul_(t_vector vec, t_vector vec2);
t_vector		vec_div(t_vector vec, double t);
double		vec_dot(t_vector vec, t_vector vec2);
t_vector		vec_prod(t_vector vec, t_vector vec2);
t_vector		unit_vec(t_vector vec);
t_vector		vec_cmp(t_vector vec1, t_vector vec2);
t_ray		ray(t_point orig, t_vector dir);
t_point	ray_at(t_ray *ray, double t);

/* renewal */

// # include <stdio.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <stdbool.h>
// # include <fcntl.h>
// # include <math.h>
// # include <mlx.h>
// # include <time.h>
// # include "structure.h"
// # include "../libft/inc/libft.h"

// int check_input(int argc, char **argv);

// void	check_face_normal(void *this, t_ray ray, t_vector outward_normal);
// bool	hit_hittable_list(void *this, t_hitarg arg);

// /* init */
// void		initialize(int argc, char **argv, t_mlx *mlx);

// /* color */
// void	color_each_pixel(t_img *img, int x, int y, int color);
// int		_get_color(t_vector vec);
// t_vector	__get_color_vec(t_ray *ray, t_hittable *world, int depth);
// t_ray	__get_color_ray(void *this, double u, double v);
// void	color_pixels(t_mlx *mlx);
// void	color_window(t_mlx *mlx);

// /* sphere */
// bool	hit_sphere(void *this, t_hitarg arg);

// /* plane */
// bool	hit_plane(void *this, t_hitarg arg);

// /* cylinder */
// bool	hit_cylinder(void *this, t_hitarg arg);

// /* random */
// double		drandom48(void);
// t_vector	random_in_hemisphere(t_vector normal);
// t_vector	random_unit_vecter(void);
// t_vector	random_in_unit_sphere(void);

// /* scatter */
// bool	scatter_lambertian(void *this, t_material_arg arg);
// bool	scatter_metal(void *this, struct s_material_arg arg);

// /* calculate */
// double		size_vec(t_vector vec);
// t_vector	new_vec(double x, double y, double z);
// t_ray		new_ray(t_vector org, t_vector dir);
// t_vector	unit_vec(t_vector vec);
// t_vector	cal_add_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_add3_vec(t_vector vec_1, t_vector vec_2, t_vector vec_3);
// t_vector	cal_subtract_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_inverse_vec(t_vector vec);
// t_vector	cal_multiply_vec(t_vector vec, double ratio);
// t_vector	cal_multi_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_divide_vec(t_vector vec, double ratio);
// t_vector	cal_arithmetic_vec(t_vector vec_1, t_vector vec_2, double ratio);
// t_vector	cal_ray(t_ray ray, double ratio);
// double		cal_inner_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_outer_vec(t_vector vec_1, t_vector vec_2);

// /* hooks */
// void		set_hooks(t_mlx *mlx);

// /* utils */
// void		exit_with_str(const char *str, int exit_code);

#endif

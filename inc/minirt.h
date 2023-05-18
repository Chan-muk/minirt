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

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "../libft/inc/libft.h"

# define EXIT_SUCCESS			0
# define EXIT_FAILURE			1
# define WIN_WIDTH				800
# define WIN_HEIGHT				400
# define DIVERGENCE_CONDITION	300
# define KEYPRESS				2
# define DESTROYNOTIFY			17
# define ESC					53
# define LEFT_CLICK				1
# define RIGHT_CLICK			2
# define MIDDLE_CLICK			3
# define SCROLL_UP				4
# define SCROLL_DOWN			5
# define UP						126
# define DOWN					125
# define LEFT					123
# define RIGHT					124
# define R_KEY					15

typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;	

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	img;
}	t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
	struct s_vector	org;
	struct s_vector	dir;
}	t_ray;

typedef struct s_hit_record
{
	double			t;
	struct s_vector	p;
	struct s_vector	normal;
}	t_hit_record;

typedef	struct s_hitarg
{
	t_ray			*ray;
	double			min;
	double			max;
	t_hit_record	*rec;
}	t_hitarg;

typedef struct s_sphere
{
	bool		(*hit)(void *this, struct s_hitarg arg);
	t_vector	center;
	double 		radius;
}	t_sphere;

typedef struct s_hitable
{
	bool		(*hit)(void *this, struct s_hitarg arg);
}	t_hitable;


typedef struct s_hitable_list
{
	bool				(*hit)(void *this, struct s_hitarg arg);
	struct s_hitable	**list;
	int					list_size;
}	t_hitable_list;

/* init */
void		initialize(int argc, char **argv, t_mlx *mlx);

/* calculate */
double		size_vec(t_vector vec);
t_vector	new_vec(double x, double y, double z);
t_ray		new_ray(t_vector org, t_vector dir);
t_vector	unit_vec(t_vector vec);
t_vector	cal_add_vec(t_vector vec_1, t_vector vec_2);
t_vector	cal_subtract_vec(t_vector vec_1, t_vector vec_2);
t_vector	cal_inverse_vec(t_vector vec);
t_vector	cal_multiply_vec(t_vector vec, double ratio);
t_vector	cal_divide_vec(t_vector vec, double ratio);
t_vector	cal_arithmetic_vec(t_vector vec_1, t_vector vec_2, double ratio);
t_vector	cal_ray(t_ray ray, double ratio);
double		cal_inner_vec(t_vector vec_1, t_vector vec_2);
t_vector	cal_outer_vec(t_vector vec_1, t_vector vec_2);

/* hooks */
void		set_hooks(t_mlx *mlx);

/* utils */
void		exit_with_str(const char *str, int exit_code);

#endif

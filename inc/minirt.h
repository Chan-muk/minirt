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
# include <fcntl.h>
# include <math.h>
# include <time.h>

# include "mlx.h"
# include "calculate.h"
# include "object.h"
# include "scene.h"
# include "parse.h"
# include "../libft/inc/libft.h"

# define OBJ_COUNT		1000
# define WIN_WIDTH		1200
# define WIN_HEIGHT		600
# define DELIMITER		" \t\v\f\r\n"
# define TRUE			1
# define FALSE			0
# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define INT_MAX		2147483647
# define EPSILON		1.0e-3
# define REC_TMIN		1.0e-8
# define REC_TMAX		INT_MAX
# define KEYPRESS		2
# define DESTROYNOTIFY	17
# define ESC			53

/* shininess value */
# define KSN			64

/* specular strength */
# define KS				0.5

/* standard luminous flux/light quantity */
# define LUMEN			3

/* init */
void	initialize(int argc, char **argv, t_data *data);
void	initialize_bonus(int argc, char **argv, t_data *data);

/* hooks */
void	set_hooks(t_mlx *mlx);

/* utils */
double	fract(double x);
int		check_object_height(t_hit_array *obj, t_ray *ray, double root);
void	data_backup(t_hit_record *rec_backup, t_hit_record *rec);
void	check_data(double root, int *flag, t_hit_record *rec, \
t_hit_record *rec_backup);
void	exit_with_str(const char *str, int exit_code);

/* free */
void	texture_free(t_hit_array array[]);

#endif

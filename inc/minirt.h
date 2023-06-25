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
# include <time.h>

# include "mlx.h"
# include "calculate.h"
# include "object.h"
# include "scene.h"
# include "parse.h"
# include "../libft/inc/libft.h"

# define WIN_WIDTH		2400
# define WIN_HEIGHT		1200
# define DELIMITER		" \t\v\f\r\n"
# define TRUE			1
# define FALSE			0
# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define CAMERA_NS		100
# define KEYPRESS		2
# define DESTROYNOTIFY	17
# define ESC			53
# define INT_MAX		2147483647

/* init */
void	initialize(int argc, char **argv, t_mlx *mlx, t_scene *scene);
void	initialize_bonus(int argc, char **argv, t_mlx *mlx, t_scene *scene);

/* hooks */
void	set_hooks(t_mlx *mlx);

/* utils */
double	fract(double x);
bool	check_object_height(t_hit_array *obj, t_ray *ray, double root);
void	data_backup(t_hit_record *rec_backup, t_hit_record *rec);
void	check_data(double root, bool *flag, t_hit_record *rec, \
t_hit_record *rec_backup);
void	exit_with_str(const char *str, int exit_code);

#endif

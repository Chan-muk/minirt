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
# include "../libft/inc/libft.h"

# define WIN_WIDTH		800
# define WIN_HEIGHT		400

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define CAMERA_NS		100
# define KEYPRESS		2
# define DESTROYNOTIFY	17
# define ESC			53
# define LEFT_CLICK		1
# define RIGHT_CLICK	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define UP				126
# define DOWN			125
# define LEFT			123
# define RIGHT			124
# define R_KEY			15

/* input */
void		set_objects(t_hit_array *array);

/* init */
void		initialize(int argc, char **argv, t_mlx *mlx);

/* hooks */
void		set_hooks(t_mlx *mlx);

/* utils */
void		exit_with_str(const char *str, int exit_code);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:47:38 by chajung           #+#    #+#             */
/*   Updated: 2023/05/01 09:47:39 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	shut_down(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(EXIT_SUCCESS);
}

int	key_event(int code, t_mlx *mlx)
{
	if (code == ESC)
		shut_down(mlx);
	// else if (code == UP)
	// 	mlx->num.offset_y += 0.1 * mlx->num.scale;
	// else if (code == DOWN)
	// 	mlx->num.offset_y -= 0.1 * mlx->num.scale;
	// else if (code == LEFT)
	// 	mlx->num.offset_x += 0.1 * mlx->num.scale;
	// else if (code == RIGHT)
	// 	mlx->num.offset_x -= 0.1 * mlx->num.scale;
	// else if (code == R_KEY)
	// 	initialize_fractal_data(mlx);
	// put_fractals_to_window(mlx);
	return (0);
}

void	mouse_middle_click(t_mlx *mlx)
{
	if (mlx->color.i == 0)
	{
		mlx->color.r *= 2;
		mlx->color.g /= 5;
		mlx->color.b /= 5;
	}
	else if (mlx->color.i == 1)
	{
		mlx->color.r /= 10;
		mlx->color.g *= 10;
	}
	else if (mlx->color.i == 2)
	{
		mlx->color.g /= 10;
		mlx->color.b *= 10;
	}
	else if (mlx->color.i == 3)
	{
		mlx->color.i = -1;
		mlx->color.r = 1;
		mlx->color.g = 1;
		mlx->color.b = 1;
	}
	mlx->color.i++;
}

void	mouse_click(int code, t_mlx *mlx)
{
	if (code == LEFT_CLICK)
		mlx->color.offset += 0.1;
	else if (code == RIGHT_CLICK)
		mlx->color.offset -= 0.1;
	else if (code == MIDDLE_CLICK)
		mouse_middle_click(mlx);
}

int	mouse_event(int code, int x, int y, t_mlx *mlx)
{
	if (code == SCROLL_UP)
	{
		mlx->num.offset_x -= \
			0.25 * mlx->num.scale * ((double)x / (double)WIN_WIDTH);
		mlx->num.offset_y -= \
			0.25 * mlx->num.scale * ((double)y / (double)WIN_HEIGHT);
		mlx->num.scale *= 0.75;
	}
	else if (code == SCROLL_DOWN)
	{
		mlx->num.offset_x += \
			0.25 * mlx->num.scale * ((double)x / (double)WIN_WIDTH);
		mlx->num.offset_y += \
			0.25 * mlx->num.scale * ((double)y / (double)WIN_HEIGHT);
		mlx->num.scale /= 0.75;
	}
	else if (code == LEFT_CLICK || code == RIGHT_CLICK || code == MIDDLE_CLICK)
		mouse_click(code, mlx);
	if (mlx->color.offset <= 0)
		mlx->color.offset = 5;
	// put_fractals_to_window(mlx);
	return (0);
}

void	set_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win_ptr, KEYPRESS, 0, key_event, mlx);
	mlx_hook(mlx->win_ptr, DESTROYNOTIFY, 0, shut_down, mlx);
	// mlx_mouse_hook(mlx->win_ptr, mouse_event, mlx);
}

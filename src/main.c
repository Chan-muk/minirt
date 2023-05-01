/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:04:41 by chajung           #+#    #+#             */
/*   Updated: 2023/04/23 12:04:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data_addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
	*(unsigned int *)dst = color;
}

int	setting_color(t_color *color, int i)
{
	double	r;
	double	g;
	double	b;
	int		result;

	r = color->r * i * color->offset;
	g = color->g * i * color->offset;
	b = color->b * i * color->offset;
	if ((int)r > 255)
		r = 1.0;
	if ((int)g > 255)
		g = 1.0;
	if ((int)b > 255)
		b = 1.0;
	if ((int)r < 0)
		r = 255.0;
	if ((int)g < 0)
		g = 255.0;
	if ((int)b < 0)
		b = 255.0;
	result = (((int)r << 16) + ((int)g << 8) + (int)b);
	result = result & 0x00FFFFFF;
	return (result);
}

// int	which_fractal(t_mlx *mlx, int width, int height)
// {
// 	if (mlx->fractal_number == JULIA_SET)
// 		return (julia_set(&mlx->num, width, height));
// 	else if (mlx->fractal_number == MANDELBROT_SET)
// 		return (mandelbrot_set(&mlx->num, width, height));
// 	else if (mlx->fractal_number == BURNING_SHIP)
// 		return (burning_ship(&mlx->num, width, height));
// 	else if (mlx->fractal_number == TRICORN)
// 		return (tricorn(&mlx->num, width, height));
// 	else
// 		exit_after_print("choose fail");
// 	return (0);
// }

void	put_color_in_pixel(t_mlx *mlx)
{
	// int	i;
	int	width;
	int	height;

	height = -1;
	while (++height < WIN_HEIGHT)
	{
		width = -1;
		while (++width < WIN_WIDTH)
		{
			// i = which_fractal(mlx, width, height);
			// if (i < DIVERGENCE_CONDITION)
			// 	my_mlx_pixel_put(&mlx->img, width, height, \
			// 		setting_color(&mlx->color, i));
			// else
			my_mlx_pixel_put(&mlx->img, width, height, 0x00FFFFFF);
		}
	}
}

void	put_fractals_to_window(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	put_color_in_pixel(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	// arguments_check(argc, argv, &mlx);
	initialize(argc, argv, &mlx);
	// put_fractals_to_window(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

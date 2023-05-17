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

void	color_each_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data_addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
	*(unsigned int *)dst = color;
}

// double hit_sphere(t_vector center, double radius, t_ray r)
// {
// 	t_vector	oc;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
	
// 	oc = cal_subtract_vec(&(r.org), &center);
// 	a = cal_inner_vec(&r.dir, &r.dir);
// 	b = 2.0 * cal_inner_vec(&oc, &r.dir);
// 	c = cal_inner_vec(&oc, &oc) - radius * radius;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (-1.0);
// 	else
// 		return (((-b -sqrt(discriminant)) / (2.0 * a)));
// }

double hit_sphere(t_vector center, double radius, t_ray ray)
{
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	
	r_center = cal_subtract_vec(&(ray.org), &center);
	a = cal_inner_vec(&ray.dir, &ray.dir);
	b = cal_inner_vec(&r_center, &ray.dir);
	c = cal_inner_vec(&r_center, &r_center) - radius * radius;
	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return (((-b -sqrt(discriminant)) / a));
}

t_vector	color(t_ray r)
{
	t_vector	unit_vector;
	t_vector	N;
	t_vector	tmp1;
	double		t;

	t = hit_sphere(new_vec(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		tmp1 = cal_ray(&r, t);
		N = new_vec(0.0, 0.0, -1);
		tmp1 = cal_subtract_vec(&tmp1, &N);
		N = unit_vec(&tmp1);
		tmp1 = new_vec(1.0, 1.0 ,1.0);
		N = cal_add_vec(&N, &tmp1);
		return (cal_multiply_vec(&N, 0.5));
	}
	unit_vector = unit_vec(&r.dir);
	t = 0.5 * ((unit_vector.y) + 1.0);
	unit_vector.x = (1.0 - t) * (1.0) + t * 0.5;
	unit_vector.y = (1.0 - t) * (1.0) + t * 0.7;
	unit_vector.z = (1.0 - t) * (1.0) + t * 1.0;
	return (unit_vector);
}

void	color_pixels(t_mlx *mlx)
{
	t_vector	vec;
	int			result;

	t_vector	lower_left_corner = {-2.0, -1.0, -1.0};
	t_vector	horizontal = {4.0, 0.0, 0.0};
	t_vector	vertical = {0.0, 2.0, 0.0};
	t_vector	origin = {0.0, 0.0, 0.0};
	for (int j = WIN_HEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < WIN_WIDTH; i++) {
			double u = (double)i / (double)WIN_WIDTH;
			double v = (double)j / (double)WIN_HEIGHT;
			t_ray r = \
			{{0.0, 0.0, 0.0}, {
				lower_left_corner.x + u * horizontal.x + v * vertical.x,
				lower_left_corner.y + u * horizontal.y + v * vertical.y,
				lower_left_corner.z + u * horizontal.z + v * vertical.z,
			}};
			vec = color(r);
			// vec = \
			// new_vec((double)i / (double)WIN_WIDTH, (double)j / (double)WIN_HEIGHT, 0.2);
			result = \
			(((int)(255.99 * vec.x) << 16) + ((int)(255.99 * vec.y) << 8) + (int)(255.99 * vec.z));
			color_each_pixel(&mlx->img, i, j, result);
		}
	}
}

void	color_window(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	color_pixels(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	// arguments_check(argc, argv, &mlx);
	initialize(argc, argv, &mlx);
	color_window(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

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

double hit_sphere(t_vector center, double radius, t_ray ray)
{
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	
	r_center = cal_subtract_vec(ray.org, center);
	a = cal_inner_vec(ray.dir, ray.dir);
	b = cal_inner_vec(r_center, ray.dir);
	c = cal_inner_vec(r_center, r_center) - (radius * radius);
	discriminant = (b * b) - (a * c);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / a);
}

// bool __hit_sphere(t_vector center, double radius, t_ray ray, double min, double max, t_hit_record *rec)
// bool	hit_sphere(void *this, t_hitarg h)
// {
// 	t_sphere	*t;
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	double		temp;
	
// 	t = (t_sphere *)this;
// 	r_center = cal_subtract_vec(h.ray->org, t->center);
// 	a = cal_inner_vec(h.ray->dir, h.ray->dir);
// 	b = cal_inner_vec(r_center, h.ray->dir);
// 	c = cal_inner_vec(r_center, r_center) - (t->r * t->r);
// 	discriminant = (b * b) - (a * c);
// 	if (discriminant > 0)
// 	{
// 		temp = (-b - sqrt(discriminant)) / a;
// 		if (temp < h.max && temp > h.min)
// 		{
// 			h.out->t = temp;
// 			h.out->p = cal_ray(h.ray, h.out->t);
// 			h.out->normal = cal_divide_vec(cal_subtract_vec(h.out->p, t->center), t->r);
// 			return (true);
// 		}
// 		temp = (-b + sqrt(discriminant)) / a;
// 		if (temp < h.max && temp > h.min)
// 		{
// 			h.out->t = temp;
// 			h.out->p = cal_ray(h.ray, h.out->t);
// 			h.out->normal = cal_divide_vec(cal_subtract_vec(h.out->p, t->center), t->r);
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

t_vector	color(t_ray ray)
{
	t_vector	unit_vector;
	double		t;

	t = hit_sphere(new_vec(0.0, 0.0, -1.0), 0.5, ray);
	if (t > 0.0)
	{
		unit_vector = cal_arithmetic_vec(\
		unit_vec(cal_subtract_vec(cal_ray(ray, t), new_vec(0.0, 0.0, -1.0))), \
		new_vec(1.0, 1.0, 1.0), 0.5);
	}
	else
	{
		unit_vector = unit_vec(ray.dir);
		t = 0.5 * ((unit_vector.y) + 1.0);
		unit_vector.x = ((1.0 - t) * 1.0) + (t * 0.5);
		unit_vector.y = ((1.0 - t) * 1.0) + (t * 0.7);
		unit_vector.z = ((1.0 - t) * 1.0) + (t * 1.0);
	}
	return (unit_vector);
}

t_ray	get_ray(double x, double y)
{
	t_ray		ray;
	t_vector	lower_left_corner;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	origin;

	double		u;
	double		v;

	u = x / (double)WIN_WIDTH;
	v = y / (double)WIN_HEIGHT;

	lower_left_corner = new_vec(-2.0, -1.0, -1.0);
	horizontal = new_vec(4.0, 0.0, 0.0);
	vertical = new_vec(0.0, 2.0, 0.0);
	origin = new_vec(0.0, 0.0, 0.0);

	ray = new_ray(new_vec(0.0, 0.0, 0.0), \
	new_vec(lower_left_corner.x + u * horizontal.x + v * vertical.x,
	lower_left_corner.y + u * horizontal.y + v * vertical.y,
	lower_left_corner.z + u * horizontal.z + v * vertical.z));
	return (ray);
}

void	color_pixels(t_mlx *mlx)
{
	int 		x;
	int		 	y;
	int			result;
	t_ray 		ray;
	t_vector	vec;

	y = WIN_HEIGHT;
	while (y >= 0)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = get_ray((double)x, (double)y);
			vec = color(ray);
			result = \
			(((int)(255.99 * vec.x) << 16) + ((int)(255.99 * vec.y) << 8) + (int)(255.99 * vec.z));
			color_each_pixel(&mlx->img, x, y, result);
			x++;
		}
		y--;
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


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

bool	hit_hitable_list(void *this, t_hitarg h)
{
	t_hitable_list	*t;
	t_hit_record	temp_out;
	bool			hit_anything;
	double			closest_so_far;

	t = (t_hitable_list *)this;
	hit_anything = false;
	closest_so_far = h.max;
	for (int i = 0; i < t->list_size; i++)
	{
		if (t->list[i]->hit(&t->list[i], (t_hitarg){h.ray, h.min, closest_so_far, &temp_out}))
		{
			hit_anything = true;
			closest_so_far = temp_out.t;
			*h.out = temp_out;
		}
	}
	return (hit_anything);
}


bool	hit_sphere(void *this, t_hitarg h)
{
	t_sphere	*t;
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	t = (t_sphere *)this;
	oc = cal_subtract_vec(&h.ray->org, &t->center);
	a = cal_inner_vec(&h.ray->dir, &h.ray->dir);
	b = 2.0 * cal_inner_vec(&oc, &h.ray->dir);
	c = cal_inner_vec(&oc, &oc) - t->r * t->r;
	discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		double temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < h.max && temp > h.min)
		{
			h.out->t = temp;
			h.out->p = cal_ray(h.ray, h.out->t);
			h.out->normal = cal_subtract_vec(&h.out->p, &t->center);
			h.out->normal = cal_multiply_vec(&h.out->normal, 1 / t->r);
			return (true);
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < h.max && temp > h.min)
		{
			h.out->t = temp;
			h.out->p = cal_ray(h.ray, h.out->t);
			h.out->normal = cal_subtract_vec(&h.out->p, &t->center);
			h.out->normal = cal_multiply_vec(&h.out->normal, 1 / t->r);
			return (true);
		}
	}
	return (false);
}

t_vector	color(t_ray r, t_hitable *world)
{
	t_hit_record	out;
	t_vector		unit_vector;
	t_vector		tmp;
	double			t;

	if (world->hit(world, (t_hitarg){&r, 0.0, MAXFLOAT, &out}))
	{
		tmp = new_vec(1.0, 1.0 ,1.0);
		out.normal = cal_add_vec(&out.normal, &tmp);
		return (cal_multiply_vec(&out.normal, 0.5));
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

	t_vector	lower_left_corner = {-2.0, -1.0, -1.0};
	t_vector	horizontal = {4.0, 0.0, 0.0};
	t_vector	vertical = {0.0, 2.0, 0.0};
	t_vector	origin = {0.0, 0.0, 0.0};
	t_hitable	*list[2];
	t_sphere	sphere1 = {{0, 0, -1}, 0.5, hit_sphere};
	t_sphere	sphere2 = {{0, -100.5, -1}, 100, hit_sphere};
	list[0] = &sphere1;
	list[1] = &sphere2;
	t_hitable	*world = (t_hitable_list *){list, 2};
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
			vec = color(r, world);
			// vec = \
			// new_vec((double)i / (double)WIN_WIDTH, (double)j / (double)WIN_HEIGHT, 0.2);
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

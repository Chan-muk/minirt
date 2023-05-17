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

void	color_pixels(t_mlx *mlx)
{
	t_vector	vec;
	int			result;

	for (int j = WIN_HEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < WIN_WIDTH; i++) {
			vec = \
			new_vec((double)i / (double)WIN_WIDTH, (double)j / (double)WIN_HEIGHT, 0.2);
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

vec3 color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = (int)(255.99 * col[0]);
			int ig = (int)(255.99 * col[1]);
			int ib = (int)(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}

// int	setting_color(t_color *color, int i)
// {
// 	double	r;
// 	double	g;
// 	double	b;
// 	int		result;

// 	r = color->r * i * color->offset;
// 	g = color->g * i * color->offset;
// 	b = color->b * i * color->offset;
// 	if ((int)r > 255)
// 		r = 1.0;
// 	if ((int)g > 255)
// 		g = 1.0;
// 	if ((int)b > 255)
// 		b = 1.0;
// 	if ((int)r < 0)
// 		r = 255.0;
// 	if ((int)g < 0)
// 		g = 255.0;
// 	if ((int)b < 0)
// 		b = 255.0;
// 	result = (((int)r << 16) + ((int)g << 8) + (int)b);
// 	result = result & 0x00FFFFFF;
// 	return (result);
// }

// void	put_color_in_pixel(t_mlx *mlx)
// {
// 	// int	i;
// 	int	width;
// 	int	height;

// 	height = 0;
// 	while (height < WIN_HEIGHT)
// 	{
// 		width = 0;
// 		while (width < WIN_WIDTH)
// 		{
// 			// i = which_fractal(mlx, width, height);
// 			// if (i < DIVERGENCE_CONDITION)
// 			// 	my_mlx_pixel_put(&mlx->img, width, height, \
// 			// 		setting_color(&mlx->color, i));
// 			// else
// 			// my_mlx_pixel_put(&mlx->img, width, height, 0x00000000);
// 			my_mlx_pixel_put(&mlx->img, width, height, 0x00FFFFFF);
// 			width++;
// 		}
// 		height++;
// 	}
// }

// int main() {
// 	int nx = 200; //Window width
// 	int ny = 100; //Window height
// 	// std::cout << "P3\n" << nx << " " << ny << "\n255\n";
// 	for (int j = ny - 1; j >= 0; j--) {
// 		for (int i = 0; i < nx; i++) {
// 			float r = (float)i / (float)nx;
// 			float g = (float)j / (float)ny;
// 			float b = 0.2;
// 			int ir = (int)(255.99 * r);
// 			int ig = (int)(255.99 * g);
// 			int ib = (int)(255.99 * b);

// 			int		result;
// 			result = \
// 			(((int)(255.99 * r) << 16) + ((int)(255.99 * g) << 8) + (int)(255.99 * b));
// 			// std::cout << ir << " " << ig << " " << ib << "\n";
// 		}
// 	}
// }

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

// int	ray_color(t_ray *ray)
// {
// 	t_vector	u_vector;
// 	double		ratio;
	
// 	u_vector = unit_vec(&ray->dir);
// 	ratio = 0.5 * (u_vector.y + 1.0);

// 	return ((1.0 - ratio) * color(1.0, 1.0, 1.0) + ratio * color(0.5, 0.7, 1.0));
// }

// void	test_code(t_mlx *mlx)
// {
// 	// Image
// 	double aspect_ratio = 16.0 / 9.0;
// 	int image_width = 400;
// 	int image_height = (int)((double)image_width / aspect_ratio);

// 	// Camera
// 	double viewport_height = 2.0;
// 	double viewport_width = aspect_ratio * viewport_height;
// 	double focal_length = 1.0;

// 	t_vector	origin = new_vec(0, 0, 0);
// 	t_vector	vertical = new_vec(viewport_height, 0, 0);
// 	t_vector	horizontal = new_vec(0, viewport_width, 0);

// 	t_vector	lower_left_corner = \
// 	new_vec(origin.x + (- horizontal.x / 2) + (-vertical.x / 2) + (0), \
// 	origin.y + (- horizontal.y / 2) + (-vertical.y / 2) + (0), \
// 	origin.z + (- horizontal.z / 2) + (-vertical.z / 2) + (-focal_length));

// 	double	u;
// 	double	v;
// 	int	i;
// 	int	j;

// 	t_ray r;
// 	t_vector test;
// 	double	t;
// 	// r.org = new_vec(0, 0, 0); // 3차원상의 정점 좌표
// 	// r.dir = \
// 	// new_vec(lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x, \
// 	// lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y, \
// 	// lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z);
	
// 	j = image_height - 1;
// 	while (j >= 0)
// 	{
// 		i = 0;
// 		while (i < image_width)
// 		{
// 			u = (double)i / (image_width - 1);
// 			v = (double)j / (image_height - 1);
// 			// ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			
// 			r.org = new_vec(0, 0, 0); // 3차원상의 정점 좌표
// 			r.dir = \
// 			new_vec(lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x, \
// 			lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y, \
// 			lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z);

// 			++i;
// 		}
// 		--j;
// 	}
// }
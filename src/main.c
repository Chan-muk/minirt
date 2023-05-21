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

/* Chapter 8: Metal*/
bool	scatter_lambertian(void *this, struct s_material_arg arg)
{
	t_vector		target;
	t_ray			ray;
	t_lambertian	*lambertian;

	lambertian = (t_lambertian *)this;
	ray = new_ray(arg.rec->p, cal_subtract_vec(target, arg.rec->p));
	arg.scattered = &ray;
	arg.attenuation = &lambertian->albedo;
	return (true);
}

t_vector	reflect(t_vector vec_v, t_vector vec_n)
{
	return (cal_subtract_vec(vec_v, cal_multiply_vec(vec_n, (2 * cal_inner_vec(vec_v, vec_n)))));
}

bool	scatter_metal(void *this, struct s_material_arg arg)
{
	t_metal		*metal;
	t_vector	reflected;
	t_ray		ray;
	
	metal = (t_metal *)this;
	reflected = reflect(unit_vec(arg.ray_in->dir), arg.rec->normal);
	ray = new_ray(arg.rec->p, reflected);
	arg.scattered = &ray;
	arg.attenuation = &metal->albedo;
	if (cal_inner_vec(arg.scattered->dir, arg.rec->normal) > 0)
		return (true);
	else
		return (false);
}
/* Chapter 8: Metal*/

bool	hit_sphere(void *this, t_hitarg arg)
{
	t_sphere	*sphere;
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		temp;

	sphere = (t_sphere *)this;
	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
	b = cal_inner_vec(r_center, arg.ray->dir);
	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
	discriminant = (b * b) - (a * c);
	if (discriminant > 0)
	{
		temp = (-b - sqrt(discriminant)) / a;
		if (temp < arg.max && temp > arg.min)
		{
			arg.rec->t = temp;
			arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
			arg.rec->normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
			return (true);
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < arg.max && temp > arg.min)
		{
			arg.rec->t = temp;
			arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
			arg.rec->normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
			return (true);
		}
	}
	return (false);
}

bool	hit_hitable_list(void *this, t_hitarg arg)
{
	t_hitable_list	*world;
	t_hit_record	temp_rec;
	bool			hit_anything;
	t_hitarg		temp_arg;

	world = (t_hitable_list *)this;
	hit_anything = false;
	temp_arg = arg;
	temp_arg.rec = &temp_rec;
	for (int i = 0; i < world->list_size; i++)
	{
		if (world->list[i]->hit(world->list[i], temp_arg))
		{
			hit_anything = true;
			temp_arg.max = temp_rec.t;
			*arg.rec = temp_rec;
		}
	}
	return (hit_anything);
}

t_vector	__get_color_vec(t_ray *ray, t_hitable *world)
{
	t_hit_record	rec;
	t_vector		unit_vector;
	double			t;
	t_hitarg 		arg;
	t_ray			__ray;

	arg.ray = ray;
	arg.min = 0.001;
	arg.max = MAXFLOAT;
	arg.rec = &rec;
	if (world->hit(world, arg))
	{
		__ray = new_ray(arg.rec->p, cal_subtract_vec(cal_add3_vec(arg.rec->p, arg.rec->normal, random_in_unit_sphere()), arg.rec->p));
		return (cal_multiply_vec(__get_color_vec(&__ray, world), 0.5));
	}
	unit_vector = unit_vec(ray->dir);
	t = 0.5 * ((unit_vector.y) + 1.0);
	unit_vector = new_vec(1.0 - 0.5 * t, 1.0 - 0.3 * t, 1.0);
	return (unit_vector);
}

t_ray	__get_color_ray(void *this, double u, double v)
{
	t_camera	camera;
	t_ray		ray;

	camera = *(t_camera *)this;
	camera.lower_left_corner = new_vec(-2.0, -1.0, -1.0);
	camera.horizontal = new_vec(4.0, 0.0, 0.0);
	camera.vertical = new_vec(0.0, 2.0, 0.0);
	camera.origin = new_vec(0.0, 0.0, 0.0);

	ray.org = camera.origin;
	ray.dir = cal_subtract_vec(cal_add_vec(cal_add_vec(camera.lower_left_corner, \
	cal_multiply_vec(camera.horizontal, u)), \
	cal_multiply_vec(camera.vertical, v)), camera.origin);
	return (ray);
}

void	color_pixels(t_mlx *mlx)
{
	int 		x;
	int		 	y;
	t_vector	color;
	t_ray		color_ray;

	t_camera	cam;
	cam._get_ray = __get_color_ray;
	srand(time(NULL));

	t_hitable	*list[2];
	t_hitable	*world = &(t_hitable_list){hit_hitable_list, list, 2};
	list[0] = &(t_sphere){hit_sphere, {0, 0, -1}, 0.5};
	list[1] = &(t_sphere){hit_sphere, {0, -100.5, -1}, 100};

	y = 0;
	while (y < (WIN_HEIGHT + 1))
	{
		x = 0;
		while (x < WIN_WIDTH + 1)
		{
			color = new_vec(0.0, 0.0, 0.0);
			for (int s = 0; s < CAMERA_NS; s++) {
				double u = ((double)x + drandom48()) / (double)WIN_WIDTH;
				double v = ((double)y + drandom48()) / (double)WIN_HEIGHT;

				t_ray	ray = cam._get_ray(&cam, u, v);
				t_vector p = cal_ray(ray, 2.0);
				color = cal_add_vec(color, __get_color_vec(&ray, world));
			}
			color = cal_divide_vec(color, (double)CAMERA_NS);
			color = new_vec(sqrt(color.x), sqrt(color.y), sqrt(color.z));
			// color_ray = __get_color_ray(x, y);
			// color = __get_color_vec(&color_ray);
			color_each_pixel(&mlx->img, x, y, _get_color(color));
			x++;
		}
		y++;
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


// t_vector	__get_color_vec(t_ray *ray)
// {
// 	t_vector	unit_vector;
// 	t_vector	center;
// 	t_vector	color;
// 	double		t;

// 	/* Adding Surface Normals and Multiple Obj */
// 	center = new_vec(0.0, 0.0, -1.0);
// 	t = __hit_sphere(center, 0.5, *ray);
// 	if (t > 0.0)
// 	{
// 		t_vector	temp;
// 		t_vector	N;
		
// 		temp = cal_ray(*ray, t);
// 		N = unit_vec(new_vec(temp.x - 0.0, temp.y - 0.0, temp.z - (-1.0)));
// 		color = cal_multiply_vec(new_vec(N.x + 1.0, N.y + 1.0, N.z + 1.0), 0.5);
// 		return (color);
// 	}
// 	/* Adding Sphere */
// 	// if (__hit_sphere(new_vec(0.0, 0.0, -1.0), 0.5, *ray))
// 	// 	return (new_vec(1.0, 0.0, 0.0));
// 	/* Adding Sphere */
// 	/* Adding Surface Normals and Multiple Obj */
// 	unit_vector = unit_vec(ray->dir);
// 	t = 0.5 * ((unit_vector.y) + 1.0);
// 	color = new_vec(1.0 - 0.5 * t, 1.0 - 0.3 * t, 1.0);
// 	return (color);
// }

// t_ray	__get_color_ray(double x, double y)
// {
// 	double		u;
// 	double		v;

// 	u = x / (double)WIN_WIDTH;
// 	v = y / (double)WIN_HEIGHT;

// 	t_vector	lower_left_corner;
// 	t_vector	horizontal;
// 	t_vector	vertical;
// 	t_vector	origin;

// 	lower_left_corner = new_vec(-2.0, -1.0, -1.0);
// 	horizontal = new_vec(4.0, 0.0, 0.0);
// 	vertical = new_vec(0.0, 2.0, 0.0);
// 	origin = new_vec(0.0, 0.0, 0.0);

// 	t_ray		ray;
// 	ray = new_ray(new_vec(0.0, 0.0, 0.0), \
// 	new_vec(lower_left_corner.x + u * horizontal.x + v * vertical.x,
// 	lower_left_corner.y + u * horizontal.y + v * vertical.y,
// 	lower_left_corner.z + u * horizontal.z + v * vertical.z));
// 	return (ray);
// }












// t_ray	_get_ray(void *this, double u, double v)
// {
// 	t_camera	camera;
// 	t_ray		ray;

// 	camera = *(t_camera *)this;
// 	camera.lower_left_corner = new_vec(-2.0, -1.0, -1.0);
// 	camera.horizontal = new_vec(2.0, 0.0, 0.0);
// 	camera.vertical = new_vec(0.0, 2.0, 0.0);
// 	camera.origin = new_vec(0.0, 0.0, 0.0);

// 	ray.org = camera.origin;
// 	ray.dir = cal_subtract_vec(cal_add_vec(cal_add_vec(camera.lower_left_corner, \
// 	cal_multiply_vec(camera.horizontal, u)), \
// 	cal_multiply_vec(camera.vertical, v)), camera.origin);
// 	return (ray);
// }

// double	__hit_sphere(t_vector center, double radius, t_ray ray)
// {
// 	t_vector 	center_vec;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;

// 	center_vec = \
// 	new_vec(ray.org.x - center.x ,ray.org.y - center.y ,ray.org.z - center.z);
// 	a = cal_inner_vec(ray.dir, ray.dir);
// 	b = cal_inner_vec(center_vec, ray.dir);
// 	c = cal_inner_vec(center_vec, center_vec) - (radius * radius);
// 	discriminant = (b * b) - (a * c);
// 	// /* Adding Surface Normals and Multiple Obj */
// 	if (discriminant < 0.0)
// 		return (-1.0);
// 	else
// 		return ((-b - sqrt(discriminant)) / a);
// 	// /* Adding Surface Normals and Multiple Obj */
// }

// void	color_pixels(t_mlx *mlx)
// {
// 	double		random;
// 	int 		x;
// 	int		 	y;
// 	t_ray 		ray;
// 	t_vector	vec;

// 	t_camera	cam;
// 	cam._get_ray = _get_ray;

// 	t_hitable	*list[4];
// 	t_hitable	*world = &(t_hitable_list){hit_hitable_list, list, 4};
// 	list[0] = &(t_sphere){hit_sphere, {0, 0, -1}, 0.5, &(t_lambertian){{scatter_lambertian, {0.8, 0.3, 0.3}}}};
// 	list[1] = &(t_sphere){hit_sphere, {0, -100.5, -1}, 100, &(t_lambertian){scatter_lambertian, {0.8, 0.8, 0.0}}};
// 	list[2] = &(t_sphere){hit_sphere, {1, 0, -1}, 0.5, &(t_metal){scatter_metal, {0.8, 0.6, 0.2}}};
// 	list[3] = &(t_sphere){hit_sphere, {-1, 0, -1}, 0.5, &(t_metal){scatter_metal, {0.8, 0.8, 0.8}}};
// 	y = WIN_HEIGHT;
// 	while (y >= 0)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			t_vector	col = new_vec(0.0, 0.0, 0.0);
// 			for (int s = 0; s < CAMERA_NS; s++) {
// 				double u = ((double)x + drandom48()) / (double)CAMERA_NS;
// 				double v = ((double)y + drandom48()) / (double)CAMERA_NS;

// 				t_ray	ray = cam._get_ray(&cam, u, v);
// 				t_vector p = cal_ray(ray, 2.0);
// 				col = cal_add_vec(col, color(&ray, world, 0));
// 			}
// 			col = cal_divide_vec(col, (double)CAMERA_NS);
// 			col = new_vec(sqrt(col.x), sqrt(col.y), sqrt(col.z));
// 			// ray = get_ray((double)x, (double)y);
// 			// vec = color(&ray, world);

// 			color_each_pixel(&mlx->img, x, y, _get_color(col));
// 			x++;
// 		}
// 		y--;
// 	}
// }

// bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
// {
//     vec3 oc = r.origin() - center;
//     auto a = r.direction().length_squared();
//     auto half_b = dot(oc, r.direction());
//     auto c = oc.length_squared() - radius*radius;

//     auto discriminant = half_b*half_b - a*c;
//     if (discriminant < 0) return false;
//     auto sqrtd = sqrt(discriminant);

//     // Find the nearest root that lies in the acceptable range.
//     auto root = (-half_b - sqrtd) / a;
//     if (root < t_min || t_max < root) {
//         root = (-half_b + sqrtd) / a;
//         if (root < t_min || t_max < root)
//             return false;
//     }

//     rec.t = root;
//     rec.p = r.at(rec.t);
//     rec.normal = (rec.p - center) / radius;

//     return true;
// }

// double	__hit_sphere(t_vector center, double radius, t_ray ray)
// bool	__hit_sphere(t_vector center, double radius, t_ray ray, double min, double max, )
// {
// 	t_vector 	center_vec;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;

// 	center_vec = \
// 	new_vec(ray.org.x - center.x ,ray.org.y - center.y ,ray.org.z - center.z);
// 	a = cal_inner_vec(ray.dir, ray.dir);
// 	b = cal_inner_vec(center_vec, ray.dir);
// 	c = cal_inner_vec(center_vec, center_vec) - (radius * radius);
// 	discriminant = (b * b) - (a * c);
// 	if (discriminant < 0.0)
// 		return (false);

// 	double		root;

// 	root = (-b - sqrt(discriminant)) / a;
// 	if (root < t_min || t_max < root)
// 	{
// 		root = (-half_b + sqrtd) / a;
// 		if (root < t_min || t_max < root)
// 			return (false);
// 	}

// 	// /* Adding Surface Normals and Multiple Obj */
// 	// if (discriminant < 0.0)
// 	// 	return (-1.0);
// 	// else
// 	// 	return ((-b - sqrt(discriminant)) / a);
// 	// /* Adding Surface Normals and Multiple Obj */
// }


// t_vector	color(t_ray *ray, t_hitable *world, int depth)
// {
// 	t_hit_record	rec;
// 	t_vector		unit_vector;
// 	double			t;
// 	t_hitarg 		hit_arg;

// 	hit_arg.ray = ray;
// 	hit_arg.min = 0.001;
// 	hit_arg.max = MAXFLOAT;
// 	hit_arg.rec = &rec;

// 	t_material_arg	mat_arg;
// 	t_ray			scatterd;
// 	t_vector		attenuation;
// 	mat_arg.ray_in = ray;
// 	mat_arg.rec = &rec;
// 	mat_arg.attenuation = &attenuation;
// 	mat_arg.scattered = &scatterd;

// 	if (world->hit(world, hit_arg))
// 	{
// 		if (depth < 50 && rec.mat_ptr->scatter(&rec.mat_ptr, mat_arg))
// 		{
// 			return (cal_multi_vec(attenuation, color(&scatterd, world, depth + 1)));
// 		}
// 		else
// 		{
// 			return (new_vec(0.0, 0.0, 0.0));
// 		}
// 	}
// 	else
// 	{
// 		unit_vector = unit_vec(ray->dir);
// 		t = 0.5 * ((unit_vector.y) + 1.0);
// 		unit_vector.x = ((1.0 - t) * 1.0) + (t * 0.5);
// 		unit_vector.y = ((1.0 - t) * 1.0) + (t * 0.7);
// 		unit_vector.z = ((1.0 - t) * 1.0) + (t * 1.0);
// 	}
// 	return (unit_vector);
// }

// t_vector	color(t_ray *ray, t_hitable *world)
// {
// 	t_hit_record	rec;
// 	t_vector		unit_vector;
// 	double			t;
// 	t_hitarg 		arg;

// 	arg.ray = ray;
// 	// arg.min = 0.0;
// 	arg.min = 0.001;
// 	arg.max = MAXFLOAT;
// 	arg.rec = &rec;
// 	if (world->hit(world, arg))
// 	{
// 		t_vector	target;
// 		t_ray		ray;

// 		target = cal_add3_vec(arg.rec->p, arg.rec->normal, random_in_unit_sphere());
// 		// unit_vector = cal_arithmetic_vec(rec.normal ,new_vec(1.0, 1.0, 1.0), 0.5);
// 		ray = new_ray(arg.rec->p, cal_subtract_vec(target, arg.rec->p));
// 		return (cal_multiply_vec(color(&ray, world), 0.5));
// 	}
// 	else
// 	{
// 		unit_vector = unit_vec(ray->dir);
// 		t = 0.5 * ((unit_vector.y) + 1.0);
// 		unit_vector.x = ((1.0 - t) * 1.0) + (t * 0.5);
// 		unit_vector.y = ((1.0 - t) * 1.0) + (t * 0.7);
// 		unit_vector.z = ((1.0 - t) * 1.0) + (t * 1.0);
// 	}
// 	return (unit_vector);
// }
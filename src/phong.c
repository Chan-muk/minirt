#include "minirt.h"

t_vector	reflect(t_vector v, t_vector n)
{
	return (vec_sub(v, vec_mul(n, vec_dot(v, n) * 2)));
}

bool	hit_objects(t_hit_array *array, t_ray *ray, t_hit_record *rec);

bool	hit_shadow(t_hit_array *array, t_ray *ray, t_hit_record *rec)
{
	bool	hit;

	hit = false;
	while (array->type)
	{
		if (hit_objects(array, ray, rec))
			hit = true;
		array++;
	}
	return (hit);
}

bool	in_shadow(t_hit_array *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit_shadow(objs, &light_ray, &rec))
		return (true);
	return (false);
}

t_color		phong_lighting(t_scene *scene)
{
	t_color		light_color;
	t_hit_array	*lights_array;

	light_color = new_color(0, 0, 0);
	lights_array = scene->light;
	while (lights_array->type) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
	{
		if(lights_array->type == _light)
			light_color = vec_add(light_color, point_light_get(scene, lights_array));
		lights_array++;
	}
	light_color = vec_add(light_color, scene->ambient);
	return (vec_cmp(vec_mul_(light_color, scene->rec.albedo), new_color(1, 1, 1)));	
}

// t_color		point_light_get(t_scene *scene, t_hit_array *light)
// {
// 	t_color		diffuse;
// 	t_vector	light_dir;
// 	double		kd;

// 	light_dir = unit_vec(vec_sub(light->center, scene->rec.p));
// 	kd = fmax(vec_dot(scene->rec.normal, light_dir), 0.0);
// 	diffuse = vec_mul(light->light_color, kd);
// 	return (diffuse);
// }

t_color		point_light_get(t_scene *scene, t_hit_array *light)
{
	t_color	diffuse;
	t_vector		light_dir;
	double		kd;
	t_color	specular;
	t_vector		view_dir;
	t_vector		reflect_dir;
	double		spec;
	double		ksn;
	double		ks;
	double		brightness;

	// 추가
	double		light_len;
	t_ray		light_ray;
	// 추가 끝

	light_dir = vec_sub(light->center, scene->rec.p);
	light_len = vec_len(light_dir);
	light_ray = ray(vec_add(scene->rec.p, vec_mul(scene->rec.normal, 0.000001)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (new_color(0,0,0));
	light_dir = unit_vec(light_dir);

	// light_dir = unit_vec(vec_sub(light->center, scene->rec.p));
	kd = fmax(vec_dot(scene->rec.normal, light_dir), 0.0);// diffuse strength;
	diffuse = vec_mul(light->light_color, kd);
	view_dir = unit_vec(vec_mul(scene->ray.dir, -1));
	reflect_dir = reflect(vec_mul(light_dir, -1), scene->rec.normal);
	ksn = 64; // shininess value
	ks = 0.5; // specular strength;
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), ksn);
	specular = vec_mul(vec_mul(light->light_color, ks), spec);
	brightness = light->bright_ratio * 3; // 기준 광속/광량을 정의한 매크로
	return (vec_mul(vec_add(vec_add(scene->ambient, diffuse), specular), brightness));
}

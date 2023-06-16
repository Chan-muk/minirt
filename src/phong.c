#include "minirt.h"

t_color		phong_lighting(t_scene *scene)
{
	t_color		light_color;
	t_hit_array	*lights_array;

	light_color = new_color(0, 0, 0);
	lights_array = scene->light;
	while (lights_array->type) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
	{
		if(lights_array->type == _light)
		{
			t_color	temp;

			temp = point_light_get(scene, lights_array);
			printf("%f, %f, %f\n", temp.x, temp.y, temp.z);
			light_color = vec_add(light_color, temp);
		}
		lights_array++;
	}
	light_color = vec_add(light_color, scene->ambient);
	return (vec_cmp(vec_mul_(light_color, scene->rec.albedo), new_color(1, 1, 1)));	
}

t_color		point_light_get(t_scene *scene, t_hit_array *light)
{
	t_color		diffuse;
	t_vector	light_dir;
	double		kd;

	light_dir = unit_vec(vec_sub(light->center, scene->rec.p));
	kd = fmax(vec_dot(scene->rec.normal, light_dir), 0.0);
	diffuse = vec_mul(light->light_color, kd);
	return (diffuse);
}

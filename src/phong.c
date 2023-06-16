#include "minirt.h"

t_color		phong_lighting(t_scene *scene)
{
	t_color		light_color;
	t_hit_array	*lights_array;

	light_color = new_color(0, 0, 0);
	lights_array = scene->light;
	// while (lights_array) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
	// {
	// 	if(lights_array->type == _light)
	// 		light_color = vec_add(light_color, point_light_get(scene, lights_array));
	// 	lights_array++;
	// }
	light_color = vec_add(light_color, scene->ambient);
	return (vec_sub(vec_mul_(light_color, scene->rec.albedo), new_color(1, 1, 1)));
}

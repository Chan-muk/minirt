/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:26:59 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 11:27:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

// A	0.2 										255,255,255
// C	-50,0,2			0 0,0,0 	70
// L	-40,0,30 					0.7 			255,255,255
// pl	0,0,0 			0,1.0,0 					255,0,225
// sp	0,0,20 						20 				255,0,0
// cy	50.0,0.0,20.6 	0,0,1.0 	14.2 	21.42 	10,0,255

double	get_ratio(char *str)
{
	double	ratio;

	ratio = ascii_to_double(str);
	if (ratio < 0.0 || ratio > 1.0)
		exit_with_str("Ratio is out of range.", EXIT_FAILURE);
	return (ratio);
}

double	get_fov(char *str)
{
	double	fov;

	fov = ascii_to_double(str);
	if (fov < 0.0 || fov > 180.0)
		exit_with_str("FOV is out of range.", EXIT_FAILURE);
	return (fov);
}

double	get_length(char *str)
{
	double	length;

	length = ascii_to_double(str);
	if (length <= 0.0)
		exit_with_str("Length must be greater than zero.", EXIT_FAILURE);
	return (length);
}

t_color	get_color(char *str)
{
	char	**array;
	t_color	color;

	array = _split(str, ",");
	if (array == NULL)
		exit_with_str("Memory problem in get color.", EXIT_FAILURE);
	color.x = ascii_to_double(array[0]);
	color.y = ascii_to_double(array[1]);
	color.z = ascii_to_double(array[2]);
	free_double_array(array);
	if (color.x < 0.0 || color.x > 255.0 || color.y < 0.0 \
	|| color.y > 255.0 || color.z < 0.0 || color.z > 255.0)
		exit_with_str("Color is out of range.", EXIT_FAILURE);	
	return (color);
}

t_point	get_point(char *str)
{
	char	**array;
	t_point	point;

	array = _split(str, ",");
	if (array == NULL)
		exit_with_str("Memory problem in get point.", EXIT_FAILURE);
	point.x = ascii_to_double(array[0]);
	point.y = ascii_to_double(array[1]);
	point.z = ascii_to_double(array[2]);
	free_double_array(array);
	return (point);
}

t_vector	get_normal_vector(char *str)
{
	char		**array;
	t_vector	vector;

	array = _split(str, ",");
	if (array == NULL)
		exit_with_str("Memory problem in get vector.", EXIT_FAILURE);
	vector.x = ascii_to_double(array[0]);
	vector.y = ascii_to_double(array[1]);
	vector.z = ascii_to_double(array[2]);
	free_double_array(array);
	if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0 \
	|| vector.y > 1.0 || vector.z < -1.0 || vector.z > 1.0)
		exit_with_str("Normal Vector is out of range.", EXIT_FAILURE);	
	return (unit_vec(vector));
}

void	parse_ambient_lightning(char *buffer,  t_scene *scene)
{
	char	**array;
	double	lighting_ratio;
	t_color	color;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse ambient light.", EXIT_FAILURE);
	if (size_double_array(array) != 3)
	{
		free_double_array(array);
		exit_with_str("The number of ambient light parameters is wrong.", EXIT_FAILURE);
	}
	scene->ambient_ratio = get_ratio(array[1]);
	scene->color = get_color(array[2]);
	free_double_array(array);
}

void	parse_camera(char *buffer, t_scene *scene)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse camera.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of camera parameters is wrong.", EXIT_FAILURE);
	}

	scene->cam_org = get_point(array[1]);
	scene->cam_dir = get_normal_vector(array[2]); // Need to check
	scene->cam_fov = get_fov(array[3]);

	// scene->cam.org = get_point(array[1]);
	// scene->cam.dir = get_normal_vector(array[2]); // Need to check
	// scene->cam.fov = get_fov(array[3]);

	// printf("pnt x: %f, y: %f, z: %f\n", (scene->cam.org).x, (scene->cam.org).y, (scene->cam.org).z);
	// printf("nor x: %f, y: %f, z: %f\n", (scene->cam.dir).x, (scene->cam.dir).y, (scene->cam.dir).z);
	// printf("fov %f\n", scene->cam.fov);
	free_double_array(array);
}

void	parse_light(char *buffer, t_hit_array **hit_array, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of light parameters is wrong.", EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _light;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].bright_ratio = get_ratio(array[2]);
	(*hit_array)[*index].color = get_color(array[3]);
	free_double_array(array);
	(*index)++;
}

void	parse_plane(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of plane parameters is wrong.", EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _plane;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].color = get_color(array[3]);
	free_double_array(array);
	(*index)++;
}

void	parse_sphere(char *buffer, t_hit_array **hit_array, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of sphere parameters is wrong.", EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _sphere;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].radius = (get_length(array[2]) * 0.5); // diameter > radius
	(*hit_array)[*index].color = get_color(array[3]);
	free_double_array(array);
	(*index)++;
}

void	parse_cylinder(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 6)
	{
		free_double_array(array);
		exit_with_str("The number of cylinder parameters is wrong.", EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _cylinder;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].radius = (get_length(array[3]) * 0.5); // diameter > radius
	(*hit_array)[*index].height = get_length(array[4]);
	(*hit_array)[*index].color = get_color(array[5]);
	free_double_array(array);
	(*index)++;
}

void	parse_cone(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 6)
	{
		free_double_array(array);
		exit_with_str("The number of cylinder parameters is wrong.", EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _cone;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].radius = (get_length(array[3]) * 0.5); // diameter > radius
	(*hit_array)[*index].height = get_length(array[4]);
	(*hit_array)[*index].color = get_color(array[5]);
	free_double_array(array);
	(*index)++;
}

void	check_parameter(char *buffer, t_hit_array **array, t_scene *scene, int *index)
{
	if (is_equal(buffer, "A"))
		parse_ambient_lightning(buffer, scene);
	else if (is_equal(buffer, "C"))
		parse_camera(buffer, scene);
	else if (is_equal(buffer, "L"))
		parse_light(buffer, array, index);
	else if (is_equal(buffer, "pl"))
		parse_plane(buffer, array, index);
	else if (is_equal(buffer, "sp"))
		parse_sphere(buffer, array, index);
	else if (is_equal(buffer, "cy"))
		parse_cylinder(buffer, array, index);
	else if (is_equal(buffer, "co"))
		parse_cone(buffer, array, index);
	else
		printf("Wrong Paramters: %s", buffer);
}

int	get_hit_array_size(char *file_name)
{
	int		fd;
	int		total_count;
	int		count;
	char	*buffer;

	fd = open(file_name, O_RDONLY);
	total_count = 0;
	count = 0;
	while (TRUE)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		if (is_equal(buffer, "A") || is_equal(buffer, "C"))
			;
		else if (is_equal(buffer, "L") || is_equal(buffer, "pl") \
		|| is_equal(buffer, "sp") || is_equal(buffer, "cy") \
		|| is_equal(buffer, "co"))
			count++;
		else
			exit_with_str("There is wrong Paramter.", EXIT_FAILURE);
		total_count++;
		free(buffer);
	}
	if (total_count == 0)
		exit_with_str("Check the RT file.", EXIT_FAILURE);
	close(fd);
	return (count);
}

void	test_print_hit_array(t_hit_array *array)
{
	int	i;

	i = 0;
	while (array[i].type != 0)
	{
		printf("type: %d\n", array[i].type);
		printf("center x: %f, y: %f, z: %f\n", array[i].center.x, array[i].center.y, array[i].center.z);
		printf("norm x: %f, y: %f, z: %f\n", array[i].norm.x, array[i].norm.y, array[i].norm.z);
		printf("color x: %f, y: %f, z: %f\n", array[i].color.x, array[i].color.y, array[i].color.z);
		printf("radius: %f\n", array[i].radius);
		printf("height: %f\n", array[i].height);
		i++;
	}
}

void	parse(char *file_name, t_hit_array **array, t_scene *scene)
{
	int		fd;
	int		size;
	int		index;
	char	*buffer;

	size = get_hit_array_size(file_name);
	fd = open(file_name, O_RDONLY);
	*array = ft_calloc(sizeof(t_hit_array), (size + 1));
	// scene = ft_calloc(sizeof(t_scene), 1);
	if (*array == NULL || scene == NULL)
		exit_with_str("Memory problem in parse.", EXIT_FAILURE);
	index = 0;
	while (TRUE)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		check_parameter(buffer, array, scene, &index);
		free(buffer);
	}
	close(fd);
	// printf("pnt x: %f, y: %f, z: %f\n", (scene->cam_org).x, (scene->cam_org).y, (scene->cam_org).z);
	// printf("nor x: %f, y: %f, z: %f\n", (scene->cam_dir).x, (scene->cam_dir).y, (scene->cam_dir).z);
	// printf("fov %f\n", scene->cam_fov);
}

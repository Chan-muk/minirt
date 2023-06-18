/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:37:20 by chajung           #+#    #+#             */
/*   Updated: 2023/06/10 10:37:22 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_lights(t_hit_array *light)
{
	light[0].type = _light;
	light[0].center = new_vec(0, 0, 0);
	light[0].light_color = new_color(1, 1, 1);
	light[0].bright_ratio = 0.08;

	light[1].type = _end;
}

void	set_objects(t_hit_array *array)
{
	// array[0].type = _cone;
	// array[0].center = new_vec(0, 0, -5);
	// array[0].norm = unit_vec(new_vec(1, 4, -1));
	// array[0].height = 6;
	// array[0].radius = 2;
	// array[0].albedo = new_color(0.5, 0.0, 0.0);
	// array[1].type = _end;
	
	// array[0].type = _cylinder;
	// array[0].center = new_vec(0, 8, 0);
	// array[0].norm = unit_vec(new_vec(0, 1, -1));
	// array[0].height = 2;
	// array[0].radius = 4;
	// array[0].albedo = new_color(0.5, 0.0, 0.0);
	// array[1].type = _end;
	
	array[0].type = _sphere;
	array[0].center = new_vec(0, 0, -4);
	array[0].radius = 2;
	array[0].texture_addr = get_bmp_addr("earthmap3.bmp", &array[0].texture_w, &array[0].texture_h);

	// array[1].type = _sphere;
	// array[1].center = new_vec(2, 0, -2);
	// array[1].radius = 2;

	// array[0].type = _cylinder;
	// array[0].center = new_vec(0, 0, 1);
	// array[0].norm = unit_vec(new_vec(0, 0, -1));
	// // array[0].norm = unit_vec(new_vec(1, 1, 1));
	// // array[0].norm = unit_vec(new_vec(0, 1, 0));
	// array[0].height = 10;
	// array[0].radius = 5;
	// array[0].albedo = new_color(0.5, 0.0, 0.0);
	
	array[1].type = _end;

	// array[0].type = _plane; 
	// array[0].center = new_vec(0, 0, -6);
	// array[0].norm = unit_vec(new_vec(0, 0, -1));
	// array[0].albedo = new_color(0.5, 0.0, 0.0);
	// array[0].texture_addr = get_bmp_addr("img.bmp", &array[0].texture_w, &array[0].texture_h);

	// array[0].type = _cone;
	// array[0].center = new_vec(0, 0, -5);
	// array[0].norm = unit_vec(new_vec(1, 1, 1));
	// array[0].height = 2;
	// array[0].radius = 2;

	// array[0].type = _sphere;
	// array[0].center = new_vec(-2, 0, -5);
	// array[0].radius = 2;
	// array[0].albedo = new_color(0.5, 0, 0);
	
	// array[1].type = _sphere;
	// array[1].center = new_vec(2, 0, -5);
	// array[1].radius = 2;
	// array[1].albedo = new_color(0, 0.5, 0);

	// array[2].type = _sphere;
	// array[2].center = new_vec(0, -1005, 0);
	// array[2].radius = 999;
	// array[2].albedo = new_color(0, 0, 0.5);

	// array[1].type = _end;
}

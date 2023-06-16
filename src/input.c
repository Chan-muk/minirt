/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>  ß     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:37:20 by chajung           #+#    #+#             */
/*   Updated: 2023/06/10 10:37:22 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_objects(t_hit_array *array)
{
	// array[0].type = _sphere;
	// array[0].center = new_vec(0, 0, -5);
	// array[0].radius = 2;

	// array[1].type = _sphere;
	// array[1].center = new_vec(2, 0, -2);
	// array[1].radius = 2;

	// array[0].type = _cylinder;
	// array[0].center = new_vec(0, 0, -5);
	// array[0].norm = unit_vec(new_vec(1, 1, 1));
	// array[0].height = 2;
	// array[0].radius = 2;
	// array[0].albedo = new_color(0.5, 0.0, 0.0);

	// array[1].type = _plane; 
	// array[1].center = new_vec(0, 0, -6);
	// array[1].norm = unit_vec(new_vec(1, 1, 1));
	// // array[1].height = 2;
	// // array[1].radius = 2;

	// array[0].type = _cone;
	// array[0].center = new_vec(0, 0, -5);
	// array[0].norm = unit_vec(new_vec(1, 1, 1));
	// array[0].height = 2;
	// array[0].radius = 2;

	array[0].type = _sphere;
	array[0].center = new_vec(-2, 0, -5);
	array[0].radius = 2;
	array[0].albedo = new_color(0.5, 0, 0);
	
	array[1].type = _sphere;
	array[1].center = new_vec(2, 0, -5);
	array[1].radius = 2;
	array[1].albedo = new_color(0, 0.5, 0);

	array[2].type = _sphere;
	array[2].center = new_vec(0, -1000, 0);
	array[2].radius = 999;
	array[2].albedo = new_color(0, 0, 0.5);

	array[3].type = _end;
}

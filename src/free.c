/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:36 by chajung           #+#    #+#             */
/*   Updated: 2023/06/27 17:13:37 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	texture_free(t_hit_array array[])
{
	int i;

	i = 0;
	while (array[i].type)
	{
		if (array[i].flag == _texture)
		{
			free(array[i].texture.addr);
			free(array[i].bump_map.addr);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaplien <ykaplien@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:33:48 by ykaplien          #+#    #+#             */
/*   Updated: 2019/02/27 17:33:49 by ykaplien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	find_pos(t_wolf *wolf)
{
	int		x;
	int		y;

	y = 0;
	while (y < wolf->max_y)
	{
		x = 0;
		while (x < wolf->max_x)
		{
			if (wolf->map[y][x] == 0)
			{
				wolf->pos_x = x + 0.2;
				wolf->pos_y = y + 0.2;
				return ;
			}
			x++;
		}
		y++;
	}
	if (wolf->pos_y == wolf->max_y && wolf->pos_y == wolf->max_y)
		invalid_map();
}

void	var_calc(t_wolf *wolf, int x)
{
	wolf->ray_hit = 0;
	wolf->side = 0;
	wolf->camera_x = 2 * x / (double)(WIN_X) - 1;
	wolf->ray_dir_x = wolf->dir_x + wolf->plane_x * wolf->camera_x;
	wolf->ray_dir_y = wolf->dir_y + wolf->plane_y * wolf->camera_x;
	wolf->map_x = (int)wolf->pos_x;
	wolf->map_y = (int)wolf->pos_y;
	wolf->distance_x = fabs(1 / wolf->ray_dir_x);
	wolf->distance_y = fabs(1 / wolf->ray_dir_y);
	var_calc_additionaly(wolf);
}

void	var_calc_additionaly(t_wolf *wolf)
{
	if (wolf->ray_dir_y < 0)
	{
		wolf->step_y = -1;
		wolf->side_distance_y = (wolf->pos_y - wolf->map_y) * wolf->distance_y;
	}
	else
	{
		wolf->step_y = 1;
		wolf->side_distance_y = (wolf->map_y + 1.0 - wolf->pos_y)
		* wolf->distance_y;
	}
	var_calc_additionalx(wolf);
}

void	var_calc_additionalx(t_wolf *wolf)
{
	if (wolf->ray_dir_x < 0)
	{
		wolf->step_x = -1;
		wolf->side_distance_x = (wolf->pos_x - wolf->map_x) * wolf->distance_x;
	}
	else
	{
		wolf->step_x = 1;
		wolf->side_distance_x = (wolf->map_x + 1.0 - wolf->pos_x)
		* wolf->distance_x;
	}
	dda(wolf);
}

void	sound(t_wolf *wolf)
{
	if (wolf->sound == 0)
	{
		wolf->sound = 1;
		system("afplay soundtrack.mp3&");
	}
	else
	{
		wolf->sound = 0;
		system("killall afplay");
	}
}

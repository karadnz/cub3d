/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:23:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/22 02:58:34 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//raycast main
void	raycast(t_game *game)
{
	double	angle;
	int		line_height;
	t_ray	ray;
	int		x;

	angle = game->player.dir - FOV / 2;
	x = -1;
	while (++x < WIDTH)
	{
		init_ray(game, &ray, angle);
		calculate_step_and_dist(game, &ray);
		calculate_perpetual(game, &ray);
		determine_texture(game, &ray);
		calculate_texture_x(game, &ray);
		ray.perp_wall_dist *= cos(game->player.dir - angle);
		line_height = safe_divide(HEIGHT, ray.perp_wall_dist);
		draw_textured_line(game, &ray, x, line_height);
		draw_floor_ceiling(game, x, line_height);
		angle += ANGLE_STEP;
	}
}

//take one step
void	ray_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
		ray->side = EAST_WEST;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
		ray->side = NORTH_SOUTH;
	}
}

int	safe_divide(int numerator, double denominator)
{
	if (denominator < 1e-5)
		denominator = 0.001;
	return ((int)(numerator / denominator));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:51:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/31 16:18:15 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_hook(int key, t_game *game)
{
	printf("KEY: %d\n", key);
	if (key == 53) // Escape key
		exit(0);
	double dir_x = cos(game->player.dir);
	double dir_y = sin(game->player.dir);
	double speed = 0.15;
	if (key == KEY_W)
	{
		game->player.x += dir_x * speed;
		game->player.y += dir_y * speed;
	}
	else if (key == KEY_S)
	{
		game->player.x -= dir_x * speed;
		game->player.y -= dir_y * speed;
	}
	else if (key == KEY_A) 
	{
		game->player.x += dir_y * speed;
		game->player.y -= dir_x * speed;
	}
	else if (key == KEY_D) 
	{
		game->player.x -= dir_y * speed;
		game->player.y += dir_x * speed;
	}
	else if (key == ARR_L)
	{
		game->player.dir -= 0.1;
		if (game->player.dir < 0) // Keep the angle between 0 and 2π
			game->player.dir += 2 * M_PI;
	}
	else if (key == ARR_R)
	{
		game->player.dir += 0.1;
		if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
			game->player.dir -= 2 * M_PI;
	}
	
	print_stats(game);
	routine(game);
	//print_textures(game);

	return (0);
}

int key_hook2(int key, t_game *game)
{
	printf("KEY: %d\n", key);
	if (key == 53) // Escape key
		exit(0);
	double dir_x = cos(game->player.dir);
	double dir_y = sin(game->player.dir);
	double speed = 0.15;
	double new_x, new_y;
	if (key == KEY_W) // W
	{
		new_x = game->player.x + dir_x * speed;
		new_y = game->player.y + dir_y * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == KEY_S) // S
	{
		new_x = game->player.x - dir_x * speed;
		new_y = game->player.y - dir_y * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == KEY_A) // A
	{
		new_x = game->player.x + dir_y * speed;
		new_y = game->player.y - dir_x * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == KEY_D) // D
	{
		new_x = game->player.x - dir_y * speed;
		new_y = game->player.y + dir_x * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == ARR_L) // Left arrow key
	{
		game->player.dir -= 0.1;
		if (game->player.dir < 0) // Keep the angle between 0 and 2π
			game->player.dir += 2 * M_PI;
	}
	else if (key == ARR_R) // Right arrow key
	{
		game->player.dir += 0.1;
		if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
			game->player.dir -= 2 * M_PI;
	}
	
	print_stats(game);
	routine(game);
	print_textures(game);

	return (0);
}

void	routine(t_game *game)
{
	//mlx_clear_window(game->mlx, game->win);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_minimap(game);
}

void	print_stats(t_game *game)
{
	printf("\n\n--OMG Stats--\n\n");
	printf("dir = %f\n", game->player.dir);
	printf("\n-----XYZ------\n");
	printf("dir_x = %f\n", cos(game->player.dir));
	printf("dir_y = %f\n", sin(game->player.dir));
	printf("\n-----PPlayer------\n");
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);
}

void	print_textures(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->textures[NORTH].img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[SOUTH].img, 64, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[EAST].img, 128, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[WEST].img, 192, 0);
}
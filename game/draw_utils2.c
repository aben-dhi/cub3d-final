/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:20:30 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/21 10:43:39 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	init_vars(t_game *game, t_ray *ray, float *lh, float *lw)
{
	float	out;
	float	ang_dist;

	ang_dist = game->chars[0]->pa - ray->ra;
	if (ang_dist < 0)
		ang_dist += 2 * (float)M_PI;
	else if (ang_dist >= 2 * (float)M_PI)
		ang_dist -= 2 * (float)M_PI;
	ray->dist *= cos(ang_dist);
	*lh = 32 * HEIGHT / ray->dist;
	game->textures->offset = game->textures->wall_size[1] / *lh;
	out = 0;
	if (*lh > HEIGHT + 1)
	{
		out = (*lh - HEIGHT - 1) / 2;
		*lh = HEIGHT - 1;
	}
	*lw = WIDTH / game->settings->fov;
	return (out);
}

void	draw_text_line(t_game *game, t_ray *ray, float pix_pos, long end_ray)
{
	int	tex_x;
	int	tex_y;
	int	start;

	start = ray->start[1];
	while (start <= ray->end[1])
	{
		tex_x = (int)pix_pos * (game->textures->wall_size[1]);
		tex_y = end_ray & (game->textures->wall_size[0] - 1);
		ray->color = game->textures->current[tex_x + tex_y];
		if (!(ray->start[0] < MINIMAP && start < MINIMAP))
		{
			if (ray->start[0] < 1920 && start < 1080)
				mlx_put_pixel(game->game_img, ray->start[0],
					start, ray->color);
		}
		start += 1;
		pix_pos += game->textures->offset;
	}
}

//I can change the texture/color of the floor if needed
void	draw_env(t_game *game, t_ray *ray)
{
	int	y;
	int	y_top;

	y = ray->end[1];
	while (y < HEIGHT)
	{
		get_color(game, ray, game->textures->floor, y - 540);
		if (!(ray->start[0] < MINIMAP && y < MINIMAP))
			mlx_put_pixel(game->game_img, ray->start[0], y, ray->color);
		if (!(ray->start[0] < MINIMAP && (HEIGHT - y) < MINIMAP))
		{
			y_top = HEIGHT - y - 1;
			mlx_put_pixel(game->game_img, ray->start[0], y_top,
				ft_pixel2(game->map->c));
		}
		y++;
	}
}

void	draw_text(t_game *game, t_ray *ray, int count, int *line)
{
	float	lh;
	float	lw;
	float	pix_pos;
	float	out;
	long	end_ray;

	out = init_vars(game, ray, &lh, &lw);
	end_ray = ray->end[1] / 32 * game->textures->wall_size[1];
	if (ray->dir == 'E')
		end_ray = ray->end[0] / 32 * game->textures->wall_size[0];
	while (count < lw)
	{
		ray->start[0] = *line;
		ray->start[1] = HEIGHT / 2 - lh / 2;
		ray->end[1] = ray->start[1] + lh;
		pix_pos = out * game->textures->offset;
		draw_text_line(game, ray, pix_pos, end_ray);
		draw_env(game, ray);
		*line += 1;
		count++;
	}
}

void	draw3d(t_game *game, t_ray *ray, int count, int *line)
{
	int	x;
	int	y;

	x = (int)ray->end[0] / 32;
	y = (int)ray->end[1] / 32;
	if (game->map->map[y][x] == '1')
		game->textures->current = game->textures->wall;
	draw_text(game, ray, count, line);
}

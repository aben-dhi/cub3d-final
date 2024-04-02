/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:01 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/03/31 20:50:45 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_image(t_game *game, mlx_image_t *img, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			game->ray_tiles[y][x] = false;
			mlx_put_pixel(img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

float	calc_ray(t_ray *ray, t_map *map, int x, int y)
{
	float	dist_h;
	float	dist_v;
	int		end[2];

	ray->start[0] = x;
	ray->start[1] = y;
	dist_h = calc_horizontal(ray, map, x, y);
	end[0] = ray->end[0];
	end[1] = ray->end[1];
	ray->dir = 'N';
	dist_v = calc_vertical(ray, map, x, y);
	if (dist_h < dist_v)
	{
		ray->end[0] = end[0];
		ray->end[1] = end[1];
		ray->dir = 'E';
		return (dist_h);
	}
	return (dist_v);
}

float	calc_horizontal(t_ray *ray, t_map *map, int x, int y)
{
	float	tan_v;
	float	ray_offset[2];

	tan_v = -1 / tan(ray->ra);
	if (ray->ra < (float)M_PI && ray->ra > 0)
	{
		ray->end[1] = y / 32 * 32 + 32;
		ray->end[0] = (y - ray->end[1]) * tan_v + x;
		ray_offset[1] = 32;
	}
	else if (ray->ra > (float)M_PI && ray->ra != (float)M_PI * 2)
	{
		ray->end[1] = y / 32 * 32 - 0.0001f;
		ray->end[0] = (y - ray->end[1]) * tan_v + x;
		ray_offset[1] = -32;
	}
	if (ray->ra == 0 || ray->ra == (float)M_PI)
	{
		ray->end[0] = x;
		ray->end[1] = y;
		return (MAXFLOAT);
	}
	ray_offset[0] = -ray_offset[1] * tan_v;
	until_wall(ray, map, ray_offset);
	return (sqrtf(powf(ray->end[0] - x, 2) + powf(ray->end[1] - y, 2)));
}

float	calc_vertical(t_ray *ray, t_map *map, int x, int y)
{
	float	tan_v;
	float	ray_offset[2];

	tan_v = -tan(ray->ra);
	if (ray->ra > (float)M_PI_2 && ray->ra < ((float)M_PI_2 * 3))
	{
		ray->end[0] = x / 32 * 32 - 0.0001f;
		ray_offset[0] = -32;
	}
	else if (ray->ra < (float)M_PI_2 || ray->ra > ((float)M_PI_2 * 3))
	{
		ray->end[0] = x / 32 * 32 + 32;
		ray_offset[0] = 32;
	}
	ray->end[1] = (x - ray->end[0]) * tan_v + y;
	if (ray->ra == (float)M_PI_2 || ray->ra == ((float)M_PI_2 * 3))
	{
		ray->end[0] = x;
		ray->end[1] = y;
		return (MAXFLOAT);
	}
	ray_offset[1] = -ray_offset[0] * tan_v;
	until_wall(ray, map, ray_offset);
	return (sqrtf(powf(ray->end[0] - x, 2) + powf(ray->end[1] - y, 2)));
}

void	iterate(t_game *game, t_ray *ray, int i, int coords[2])
{
	int		line;
	t_ray	*mini;

	line = 0;
	mini = malloc(sizeof(t_ray));
	if (!mini)
		ft_error("Error\nMalloc failed\n", 2);
	game->rays = malloc(sizeof(float) * 1920);
	if (!game->rays)
		ft_error("Error\nMalloc failed\n", 2);
	while (++i < game->settings->fov)
	{
		ray->ra += (float)M_PI / 180 / game->settings->graphics;
		if (ray->ra >= 2 * (float)M_PI)
			ray->ra -= 2 * (float)M_PI;
		ray->dist = calc_ray(ray, game->map, coords[0], coords[1]);
		mini->start[0] = ray->start[0] - (game->map->player[0] - 144);
		mini->start[1] = ray->start[1] - (game->map->player[1] - 144);
		mini->end[0] = ray->end[0] - (game->map->player[0] - 144);
		mini->end[1] = ray->end[1] - (game->map->player[1] - 144);
		draw_ray(game, mini, ray->img);
		draw3d(game, ray, 0, &line);
		game->rays[i] = ray->dist;
	}
	free(mini);
}

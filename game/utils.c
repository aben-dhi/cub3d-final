/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:45:43 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/22 11:48:44 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	max(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map->max = ft_strlen1(game->map->map[0]);
	while (i < game->map->rows)
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (ft_strlen1(game->map->map[i]) > game->map->max)
			{
				game->map->max = ft_strlen1(game->map->map[i]);
			}
			j++;
		}
		i++;
	}
}

u_int32_t	*ft_color(mlx_texture_t *texture)
{
	int				i;
	unsigned int	pos;
	uint8_t			rgb[4];
	u_int32_t		*color;

	i = 0;
	color = malloc(sizeof(u_int32_t) * (texture->width + 1)
			* (texture->height + 1));
	if (!color)
		return (ft_error("malloc failed\n", 2) ,NULL);
	pos = 0;
	while (pos < texture->width * texture->height * texture->bytes_per_pixel)
	{
		rgb[0] = texture->pixels[pos];
		rgb[1] = texture->pixels[pos + 1];
		rgb[2] = texture->pixels[pos + 2];
		rgb[3] = texture->pixels[pos + 3];
		color[i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pos += texture->bytes_per_pixel;
		i++;
	}
	return (color);
}

u_int32_t	ft_pixel2(char *str)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = ft_atoi(str);
	while (*str != ',')
		str++;
	str++;
	g = ft_atoi(str);
	while (*str != ',')
		str++;
	str++;
	b = ft_atoi(str);
	a = 200;
	return (r << 24 | g << 16 | b << 8 | a);
}

void	get_color(t_game *game, t_ray *ray, u_int32_t *col, float dy)
{
	float	angle;
	float	dyangle;
	int		tx;
	int		ty;

	angle = cos(game->chars[0]->pa - ray->ra);
	dyangle = 540 * 32 / dy / angle;
	tx = game->map->player[0] + cos(ray->ra) * dyangle;
	ty = game->map->player[1] + sin(ray->ra) * dyangle;
	ray->color = col[(ty & 31) * 32 + (tx & 31)];
}

void	until_wall(t_ray *ray, t_map *map, float ray_offset[2])
{
	int	x;
	int	y;

	while (true)
	{
		x = ray->end[0] / 32;
		y = ray->end[1] / 32;
		if (x < 0 || y < 0 || x >= map->max
			|| y >= map->rows || map->map[y][x] == '1')
			break ;
		ray->end[0] += ray_offset[0];
		ray->end[1] += ray_offset[1];
	}
}

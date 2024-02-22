/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:30:11 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/14 20:01:20 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	iterate_tiles(mlx_image_t *img, int addX, int addY)
{
	size_t	i;

	i = 0;
	while (i < img->count)
	{
		img->instances[i].x -= addX;
		img->instances[i].y -= addY;
		i++;
	}
}

void	move_map(t_game *game, int addX, int addY)
{
	int	tmp;

	iterate_tiles(game->map->floor, addX, addY);
	iterate_tiles(game->map->wall, addX, addY);
	iterate_tiles(game->map->out, addX, addY);
	tmp = 1;
	while (tmp < game->map->n_chars)
	{
		game->chars[tmp]->img->instances[0].x -= addX;
		game->chars[tmp]->img->instances[0].y -= addY;
		tmp++;
	}
}

void	change_position(t_game *game, int x, int y)
{
	int		pos_x;
	int		pos_y;
	int		circle_x;
	int		circle_y;
	float	angle;

	pos_x = game->map->player[0] + x;
	pos_y = game->map->player[1] + y;
	angle = 0;
	while (angle <= (float)M_PI * 2)
	{
		circle_x = (pos_x + 4 * cos(angle));
		circle_y = (pos_y + 4 * sin(angle));
		if (game->map->map[circle_y / 32][circle_x / 32] == '1')
			return ;
		angle += (float)M_PI / 18;
	}
	move_map(game, x, y);
	game->map->player[0] += x;
	game->map->player[1] += y;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:25:33 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/23 13:01:24 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->ps = 4;
	while (i < game->map->rows)
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S'
				|| game->map->map[i][j] == 'E' || game->map->map[i][j] == 'W')
			{
				game->map->player[0] = j * 32 + 16;
				game->map->player[1] = i * 32 + 16;
				game->map->n_chars = 1;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	init_dir(t_game *game, int n, float pi)
{
	if (n != 0)
		return ;
	game->chars[n]->ray = malloc(sizeof(t_ray));
	game->chars[n]->ray->img = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
	mlx_image_to_window(game->mlx, game->chars[n]->ray->img, 0, 0);
	game->chars[n]->pa = pi;
}

void	init_char(t_game *game, char direction, int n)
{
	if (direction == 'N')
		init_dir(game, n, (float)M_PI_2 + (float)M_PI);
	else if (direction == 'E')
		init_dir(game, n, (float)M_PI * 2);
	else if (direction == 'S')
		init_dir(game, n, (float)M_PI_2);
	else if (direction == 'W')
		init_dir(game, n, (float)M_PI);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:25:33 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/22 15:08:17 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// static void	init_dir(t_game *game, int i, int j)
// {
// 	if (game->map->map[i][j] == 'N')
// 	{
// 		game->chars[0]->pa = (float)M_PI_2 +(float)M_PI;
// 		game->chars[0]->ray->dir = 'N';
// 	}
// 	else if (game->map->map[i][j] == 'S')
// 	{
// 		game->chars[0]->pa = (float)M_PI;
// 		game->chars[0]->ray->dir = 'S';
// 	}
// 	else if (game->map->map[i][j] == 'E')
// 	{
// 		game->chars[0]->pa = (float)M_PI / 2;
// 		game->chars[0]->ray->dir = 'E';
// 	}
// 	else if (game->map->map[i][j] == 'W')
// 	{
// 		game->chars[0]->pa = (float)M_PI * 3 / 2;
// 		game->chars[0]->ray->dir = 'W';
// 	}
// }

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

// static void	char_al(t_game *game)
// {
// 	// game->chars[0]->pa = 0;
// 	game->ps = 4;
// 	game->chars[0]->x = 0;
// 	game->chars[0]->y = 0;
// 	game->chars[0]->w[0] = 0;
// 	game->chars[0]->w[1] = 0;
// 	game->chars[0]->a[0] = 1;
// 	game->chars[0]->a[1] = 1;
// 	game->chars[0]->s[0] = 0;
// 	game->chars[0]->s[1] = 0;
// 	game->chars[0]->d[0] = 0;
// 	game->chars[0]->d[1] = 0;
// }

// void	init_chars(t_game *game, int n, float pi)
// {
// 	int	i;

// 	i = 0;
// 	game->ps = 4;
// 	game->chars[0]->ray = malloc(sizeof(t_ray));
// 	game->chars[0]->ray->img = mlx_new_image(game->mlx, 32, 32);
// 	if (game->chars[0]->ray == NULL)
// 		ft_error("Error\nMalloc failed!\n", 2);
// 	game->chars[0]->ray->img = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
// 	mlx_image_to_window(game->mlx, game->chars[0]->ray->img, 0, 0);
// 	char_al(game);
// 	init_player(game);
// }

static void	init_dir(t_game *game, int n, float pi)
{
	if (n != 0)
		return ;
	game->chars[n]->ray = malloc(sizeof(t_ray));
	game->chars[n]->ray->img = mlx_new_image(game->mlx, MINIMAP, MINIMAP);
	mlx_image_to_window(game->mlx, game->chars[n]->ray->img, 0, 0);
	game->chars[n]->pa = pi;
	// char_al(game);
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

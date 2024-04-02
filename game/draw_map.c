/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:06:16 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/03/31 18:18:17 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_char(t_game *game, int x, int y)
{
	static int	chrs;

	chrs--;
	if (chrs == -1)
		chrs = game->map->n_chars - 1;
	mlx_image_to_window(game->mlx, game->map->floor, x, y);
	game->chars[chrs] = malloc(sizeof(t_char));
	if (game->chars[chrs] == NULL)
		ft_error("Error\nMalloc failed!\n", 2);
	game->chars[chrs]->x = x + 8;
	game->chars[chrs]->y = y + 8;
}

void	draw_tile(t_game *game, char **map, int *iterator, int *coords)
{
	if (iterator[0] < 0 || iterator[0] >= game->map->rows
		|| iterator[1] < 0 || iterator[1] >= game->map->max
		|| map[iterator[0]][iterator[1]] == ' ')
		mlx_image_to_window(game->mlx, game->map->out, coords[0], coords[1]);
	else if (map[iterator[0]][iterator[1]] == '0')
		mlx_image_to_window(game->mlx, game->map->floor, coords[0], coords[1]);
	else if (map[iterator[0]][iterator[1]] == '1')
		mlx_image_to_window(game->mlx, game->map->wall, coords[0], coords[1]);
	else if (check_player(map[iterator[0]][iterator[1]]) == true)
		create_char(game, coords[0], coords[1]);
}

void	draw_tiles(t_game *game, char **map)
{
	int	iterator[2];
	int	coords[2];

	game->chars = malloc(sizeof(t_char) * game->map->n_chars);
	if (game->chars == NULL)
		ft_error("Error\nMalloc failed!\n", 2);
	iterator[0] = -4;
	coords[1] = abs((int)game->map->player[1] / 32 * 32) * -1;
	while (iterator[0] < game->map->rows + 4)
	{
		iterator[1] = -4;
		coords[0] = abs((int)game->map->player[0] / 32 * 32) * -1;
		while (iterator[1] < game->map->max + 4)
		{
			draw_tile(game, map, iterator, coords);
			iterator[1]++;
			coords[0] += 32;
		}
		iterator[0]++;
		coords[1] += 32;
	}
}

void	draw_it(mlx_t *mlx, t_char *c)
{
	mlx_texture_t	*player;

	player = mlx_load_png("./textures/player.png");
	if (player == NULL)
		ft_error("Error\nInvalid texture!\n", 2);
	c->img = mlx_texture_to_image(mlx, player);
	if (c->img == NULL)
		ft_error("Error\nInvalid texture!\n", 2);
	mlx_delete_texture(player);
	mlx_image_to_window(mlx, c->img, c->x, c->y);
}

void	draw_char(t_game *game, char **map)
{
	int	i;
	int	j;
	int	chars;

	i = 0;
	chars = game->map->n_chars - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_player(map[i][j]))
			{
				draw_it(game->mlx, game->chars[chars]);
				init_char(game, map[i][j], chars);
				chars--;
			}
			j++; 
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:43:11 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/23 13:04:04 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_game(t_game *game, t_ray *ray)
{
	int	i;
	int	line;
	int	round[2];

	ray->ra = game->chars[0]->pa - 30 * ((float)M_PI / 180);
	if (ray->ra < 0)
		ray->ra += 2 * (float)M_PI;
	mlx_delete_image(game->mlx, game->game_img);
	game->game_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	i = 0;
	line = 0;
	round[0] = (int)game->map->player[0];
	round[1] = (int)game->map->player[1];
	reset_image(game, ray->img, MINIMAP, MINIMAP);
	iterate(game, ray, -1, round);
	mlx_image_to_window(game->mlx, game->game_img, 0, 0);
	game->game_img->instances[0].z = -100;
}

void	start(void *param)
{
	t_game	*game;

	game = param;
	keybinds(game);
	rotate(game, 0.0f, 0);
	game->game_img->enabled = true;
	draw_game(game, game->chars[0]->ray);
	free(game->rays);
}

void	init_game(t_game *game)
{
	game->settings = malloc(sizeof(t_settings));
	if (game->settings == NULL)
		ft_error("Error\nMalloc failed!\n", 2);
	game->settings->rs = 1;
	game->settings->graphics = 32;
	game->settings->fov = 1920;
	draw_map(game);
	mlx_loop_hook(game->mlx, &start, game);
}

t_game	*alloc_game(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_error("malloc error\n", 2) ,NULL);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (ft_error("malloc error\n", 2) ,NULL);
	game->map = map;
	game->game_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->game_img, 0, 0);
	return (game);
}

void	set_z(mlx_image_t *img, int z)
{
	int	i;

	i = 0;
	while (i < (int)img->count)
	{
		img->instances[i].z = z;
		i++;
	}
}

bool	check_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return(true);
	return(false);
}

static void create_char(t_game *game, int x, int y)
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
	mlx_texture_t *player;
	
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

void	draw_map(t_game *game)
{
	max(game);
	init_textures(game);
	get_textures(game);
	init_player(game);
	draw_tiles(game, game->map->map);
	draw_char(game, game->map->map);
	set_z(game->map->floor, -200);
	set_z(game->map->wall, -200);
	set_z(game->map->out, -200);
	game->chars[0]->img->instances[0].z = -150;
}

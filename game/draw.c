/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:43:11 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/03/31 20:00:47 by aben-dhi         ###   ########.fr       */
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
		return (ft_error("malloc error\n", 2), NULL);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (ft_error("malloc error\n", 2), NULL);
	game->map = map;
	game->game_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->game_img, 0, 0);
	return (game);
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

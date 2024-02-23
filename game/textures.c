/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:44:28 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/23 13:15:13 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_textures(t_game *game)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./textures/wall.png");
	game->map->wall = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/floor.png");
	game->map->floor = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/tile_water.png");
	game->map->out = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
}

void	init_textures(t_game *game)
{
	mlx_texture_t	*text;

	game->textures = malloc(sizeof(t_textures));
	text = mlx_load_png(game->map->no);
	game->textures->wall = ft_color(text);
	game->textures->wall_size[0] = text->width;
	game->textures->wall_size[1] = text->height;
	text = mlx_load_png(game->map->so);
	game->textures->floor = ft_color(text);
	mlx_delete_texture(text);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:52 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/22 11:41:20 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	keybinds(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		change_position(game, game->chars[0]->w[0], game->chars[0]->w[1]);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		change_position(game, game->chars[0]->s[0], game->chars[0]->s[1]);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		change_position(game, game->chars[0]->a[0], game->chars[0]->a[1]);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		change_position(game, game->chars[0]->d[0], game->chars[0]->d[1]);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->chars[0]->pa -= 0.03f * game->settings->rs;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->chars[0]->pa += 0.03f * game->settings->rs;
}

void	get_move(t_game *game, t_char *chars)
{
	chars->w[0] = roundf(cos(chars->pa) * game->ps);
	chars->w[1] = roundf(sin(chars->pa) * game->ps);
	chars->s[0] = chars->w[0] * -1;
	chars->s[1] = chars->w[1] * -1;
	chars->a[0] = chars->d[0] * -1;
	chars->a[1] = chars->d[1] * -1;
	chars->d[0] = roundf(cos(chars->pa + (float)M_PI / 2) * game->ps);
	chars->d[1] = roundf(sin(chars->pa + (float)M_PI / 2) * game->ps);
}

void	rotate(t_game *game, float angle, int i)
{
	float	px;
	float	py;

	px = game->map->player[0];
	py = game->map->player[1];
	game->chars[i]->pa += angle;
	if (game->chars[i]->pa < 0)
		game->chars[i]->pa += 2 * (float)M_PI;
	else if (game->chars[i]->pa >= 2 * (float)M_PI)
		game->chars[i]->pa -= 2 * (float)M_PI;
	get_move(game, game->chars[i]);
}

void	check_pos(t_game *game)
{
	int	x;
	int	y;

	x = game->map->player[0] / 32;
	y = game->map->player[1] / 32;
}

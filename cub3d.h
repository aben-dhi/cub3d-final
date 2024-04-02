/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:41:37 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/03/31 18:28:10 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP 288

typedef struct s_ray
{
	char		dir;
	int			color;
	int			start[2];
	float		end[2];
	float		ra;
	float		dist;
	mlx_image_t	*img;
}				t_ray;

typedef struct s_char
{
	t_ray		*ray;
	mlx_image_t	*img;
	float		w[2];
	float		a[2];
	float		s[2];
	float		d[2];
	float		pa;
	float		x;
	float		y;
}				t_char;

typedef struct s_map
{
	int			rows;
	int			*columns;
	char		**file;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	char		**map;
	char		**tmp;
	int			posx;
	int			posy;
	int			max;
	float		player[2];
	int			n_chars;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*out;
}				t_map;

typedef struct s_settings
{
	char		cross_type;
	int			fov;
	int			graphics;
	float		rs;
}				t_settings;

typedef struct s_textures
{
	u_int32_t	*floor;
	u_int32_t	*wall;
	u_int32_t	*out ;
	u_int32_t	*current;
	int			wall_size[2];
	float		offset;
}				t_textures;

typedef struct s_game
{
	t_char		**chars;
	t_map		*map;
	t_textures	*textures;
	mlx_t		*mlx;
	mlx_image_t	*game_img;
	bool		ray_tiles[MINIMAP][MINIMAP];
	int			ps;
	float		*rays;
	t_settings	*settings;
}				t_game;

//cub3d functions:
void		read_map(int fd, t_map *map);
int			check_extension(char *file);
int			check_map_content(t_map *map);
int			check_map_player(t_map *map);
int			check_map_frame0(t_map *map);
int			check_map_frame1(t_map *map);
int			check_map_frame2(t_map *map);
int			check_textures(t_map *map);
int			check_rgb(t_map *map);
void		display_map_errors1(t_map *map);
void		display_map_errors2(t_map *map);

//utility functions:
void		*ft_realloc(void *ptr, int size);
char		*ft_datacpy(char *src, int n);
char		*skip_spaces(char *str);
int			avoid_spaces(char *str);
int			reverse_avoid_spaces(char *str);
int			check_empty_spaces(char *str);
int			check_double_nl(char *lmap);
void		display_dnl_error(char *lmap);
int			ft_strlcmp(char *s1, char *s2, int n);
void		free_data(t_map *map);
void		free_tmp(char **str);

//mlx functions:
void		max(t_game *game);
void		get_textures(t_game *game);
u_int32_t	*ft_color(mlx_texture_t *texture);
void		init_textures(t_game *game);
void		draw_map(t_game *game);
t_game		*alloc_game(t_map *map);
void		iterate_tiles(mlx_image_t *img, int addX, int addY);
void		move_map(t_game *game, int addX, int addY);
void		change_position(t_game *game, int x, int y);
void		keybinds(t_game *game);
void		get_move(t_game *game, t_char *chars);
void		rotate(t_game *game, float angle, int i);
void		check_pos(t_game *game);
void		reset_image(t_game *game, mlx_image_t *img, int width, int height);
void		until_wall(t_ray *ray, t_map *map, float ray_offset[2]);
float		calc_horizontal(t_ray *ray, t_map *map, int x, int y);
float		calc_vertical(t_ray *ray, t_map *map, int x, int y);
float		calc_ray(t_ray *ray, t_map *map, int x, int y);
void		set_coords(t_ray *ray, float coords[2], float steps[2]);
void		draw_minimap(t_game *game, t_ray *ray, int dir, mlx_image_t *img);
void		draw_ray(t_game *game, t_ray *ray, mlx_image_t *img);
float		init_vars(t_game *game, t_ray *ray, float *lh, float *lw);
void		draw_text_line(t_game *game, t_ray *ray,
				float pix_pos, long end_ray);
void		get_color(t_game *game, t_ray *ray, u_int32_t *col, float dy);
void		draw_env(t_game *game, t_ray *ray);
void		draw_text(t_game *game, t_ray *ray, int count, int *line);
void		draw3d(t_game *game, t_ray *ray, int count, int *line);
void		iterate(t_game *game, t_ray *ray, int i, int coords[2]);
void		draw_game(t_game *game, t_ray *ray);
void		init_player(t_game *game);
void		init_char(t_game *game, char direction, int n);
void		start(void *param);
void		init_game(t_game *game);
int			ft_error(char *s, int fd);
u_int32_t	ft_pixel2(char *str);
void		free_arrs(t_game *game);
void		free_exit(t_game *game);
void		create_char(t_game *game, int x, int y);
void		draw_tile(t_game *game, char **map, int *iterator, int *coords);
void		draw_tiles(t_game *game, char **map);
void		draw_it(mlx_t *mlx, t_char *c);
void		draw_char(t_game *game, char **map);
void		set_z(mlx_image_t *img, int z);
bool		check_player(char c);

#endif
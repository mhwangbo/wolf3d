/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:57:35 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/11 21:48:09 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../lib/Libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# include <stddef.h>
# define POS e->pos
# define ROT 0.1
# define BUF 999999

typedef struct		s_tex
{
	void			*img;
	int				*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				width;
	int				height;
}					t_tex;

typedef struct		s_vec
{
	int				x;
	int				y;
	int				wall_type;
	int				color;
}					t_vec;

typedef struct		s_win
{
	int				intro;
	int				texture_switch;
}					t_win;

typedef struct		s_pos
{
	double			pos_x;
	double			pos_y;
	double			plane_pos;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_plane_x;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				d;
	int				tex_y;
	int				color;
	double			floor_x_wall;
	double			floor_y_wall;
	double			dist_wall;
	double			dist_player;
	double			current_dist;
	double			weight;
	double			current_floor_x;
	double			current_floor_y;
	int				door;
	int				floor_tex_x;
	int				floor_tex_y;
}					t_pos;

typedef struct		s_env
{
	double			win_x;
	double			win_y;
	double			block_w;
	double			block_h;
	double			speed;
	int				run;
	int				hand;
	int				fire;
	int				ammo;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				step;
	int				tex_change;
	int				bpp;
	int				size_line;
	int				endian;
	int				*data;
	int				y_max;
	int				x_max;
	int				x_max2;
	t_vec			**map;
	t_pos			pos;
	int				min;
	int				max;
	int				**texture;
	t_tex			tex[10];
	t_win			val;
	int				shot;
	int				b;
	int				i;
	int				l;
	int				ang;
	int				caption;
}					t_env;

/*
** util.c
*/

void				file_check(char *av);
int					animate(t_env *e);
int					wolf_exit(t_env *e);
void				billy_off(t_env *e);
void				message(void);

/*
** texture.c
*/

void				malloc_texture(t_env *e);
void				tex_into_texture(t_env *e, int i, int j);
void				tex_into_texture2(t_env *e, int i, int j);
void				load_texture(t_env *e);
void				load_texture2(t_env *e);

/*
** raycasting.c
*/

void				xpm_to_texture(t_env *e, int i, int j);
void				wolf_ray_cast(t_env *e);
void				wall_texture(t_env *e, int i, int j);
void				wolf_ray_cast_calc(t_env *e, int x);
void				wolf_ray_cast_dda(t_env *e);

/*
** positioning.c
*/

void				crack(t_env *e);
void				pos_hand(t_env *t, int i, int y);
void				pos_ammo(t_env *t);
void				position(t_env *e);
void				position2(t_env *e);

/*
** main.c
*/

void				intro_image(t_env *e);
void				wolf_win(t_env *e);
void				init_value(t_env *e);
void				error_exit(int i, int fd);
int					main(int ac, char **av);

/*
** key.c
*/

int					wolf_key(int key, t_env *e);
void				wolf_key2(int key, t_env *e);
void				wolf_key3(int key, t_env *e);
void				wolf_key4(int key, t_env *e);
void				wolf_key5(int key, t_env *e);

/*
** init.c
*/

void				wolf_win_start(t_env *e);
void				wolf_find_max(char *av, t_env *e);
int					*wolf_split(char *line, t_env *e);
int					**wolf_read(char *av, t_env *e);
void				wolf_put_struct(int **file, t_env *e);

/*
** draw.c
*/

void				pos_wall(t_env *e, int x, int y);
void				pos_wall2(t_env *e, int x, int y);
void				pos_floor(t_env *e);
void				pos_floor2(t_env *e, int x, int y);

#endif

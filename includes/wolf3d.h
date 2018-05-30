/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:57:35 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/30 01:12:39 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../lib/Libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# define POS e->pos
# define ROT 0.1

typedef struct		s_vec
{
	double			x;
	double			y;
	int				wall_type;
	int				color;
}					t_vec;

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
	int				color;
	double			floor_x_wall;
	double			floor_y_wall;
	double			dist_wall;
	double			dist_player;
	double			current_dist;
	double			weight;
	double			current_floor_x;
	double			current_floor_y;
}					t_pos;

typedef struct		s_env
{
	double			win_x;
	double			win_y;
	double			block_w;
	double			block_h;
	double			speed;

	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	int				*data;

	double			y_max;
	double			x_max;
	t_vec			**map;
	t_pos			pos;
	int				min;
	int				max;
}					t_env;

#endif

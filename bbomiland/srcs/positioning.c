/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positioning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:12:55 by jukim             #+#    #+#             */
/*   Updated: 2018/06/03 02:10:03 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	position(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < e->win_x)
	{
		wolf_ray_cast_calc(e, x);
		wolf_ray_cast_dda(e);
		POS.perp_wall_dist = (POS.side == 0 ? (POS.map_x - POS.pos_x +
		(1 - POS.step_x) / 2) / POS.ray_dir_x : (POS.map_y -
			POS.pos_y + (1 - POS.step_y) / 2) / POS.ray_dir_y);
		y = POS.draw_end;
		pos_wall(e, x, y);
		pos_floor(e);
		pos_floor2(e, x, y);
	}
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}

void	pos_wall(t_env *e, int x, int y)
{
	POS.line_height = (int)(e->win_y / POS.perp_wall_dist);
	POS.draw_start = -POS.line_height / 2 + e->win_y / 2;
	POS.draw_start < 0 ? POS.draw_start = 0 : 0;
	POS.draw_end = POS.line_height / 2 + e->win_y / 2;
	POS.draw_end >= e->win_y ? POS.draw_end = e->win_y - 1 : 0;
	POS.wall_x = (POS.side == 0 ? POS.pos_y + POS.perp_wall_dist *
		POS.ray_dir_y : POS.pos_x + POS.perp_wall_dist * POS.ray_dir_x);
	POS.wall_x -= floor(POS.wall_x);
	POS.tex_x = (int)(POS.wall_x * e->block_w);
	if (POS.side == 0 && POS.ray_dir_x > 0)
		POS.tex_x = e->block_w - POS.tex_x - 1;
	else if (POS.side == 1 && POS.ray_dir_x < 0)
		POS.tex_x = e->block_w - POS.tex_x - 1;
	y = POS.draw_start - 1;
	while (++y < POS.draw_end)
	{
		POS.d = y * 256 - e->win_y * 128 + POS.line_height * 128;
		POS.tex_y = ((POS.d * e->block_h) / POS.line_height) / 256;
		POS.color = e->texture[0][(int)(e->block_w * POS.tex_y + POS.tex_x)];
		POS.side == 1 ? POS.color /= 2 : 0;
		POS.door == 1 ? POS.color /= 3 : 0;
		ft_memcpy(e->data + 4 * (int)e->win_x * y + x * 4,
				&POS.color, sizeof(int));
		//e->data[(y * (int)e->win_x) + x] = POS.color;
	}
}

void	pos_floor(t_env *e)
{
	if (POS.side == 0 && POS.ray_dir_x > 0)
	{
		POS.floor_x_wall = POS.map_x;
		POS.floor_y_wall = POS.map_y + POS.wall_x;
	}
	else if (POS.side == 0 && POS.ray_dir_x < 0)
	{
		POS.floor_x_wall = POS.map_x + 1.0;
		POS.floor_y_wall = POS.map_y + POS.wall_x;
	}
	else if (POS.side == 1 && POS.ray_dir_x > 0)
	{
		POS.floor_x_wall = POS.map_x + POS.wall_x;
		POS.floor_y_wall = POS.map_y;
	}
	else
	{
		POS.floor_x_wall = POS.map_x + POS.wall_x;
		POS.floor_y_wall = POS.map_y + 1.0;
	}
	POS.dist_wall = POS.perp_wall_dist;
	POS.dist_player = 0.0;
	POS.draw_end < 0 ? POS.draw_end = e->win_y : 0;
}

void	pos_floor2(t_env *e, int x, int y)
{
	while (++y < e->win_y)
	{
		POS.current_dist = e->win_y / (2.0 * y - e->win_y);
		POS.weight = (POS.current_dist - POS.dist_player)
			/ (POS.dist_wall - POS.dist_player);
		POS.current_floor_x = POS.weight * POS.floor_x_wall +
			(1.0 - POS.weight) * POS.pos_x;
		POS.current_floor_y = POS.weight * POS.floor_y_wall +
			(1.0 - POS.weight) * POS.pos_y;
		POS.floor_tex_x = (int)(POS.current_floor_x *
			e->block_w) % (int)e->block_w;
		POS.floor_tex_y = (int)(POS.current_floor_y *
			e->block_h) % (int)e->block_h;
//		e->data[y * (int)e->win_x + x] = e->texture[1][(int)
//			(e->block_w * POS.floor_tex_y + POS.floor_tex_x)];
		ft_memcpy(e->data + 4 * (int)((e->win_y - y) * e->win_x) + x * 4,
					&e->tex[0].data[y % 64 * e->tex[0].sizeline +
					x % 64 * e->tex[0].bpp / 8], sizeof(int));
		ft_memcpy(e->data + 4 * (int)e->win_x * y + x * 4,
					&e->tex[1].data[y % 64 * e->tex[1].sizeline +
					x % 64 * e->tex[1].bpp / 8], sizeof(int));
//		e->data[(int)((e->win_y - y) * e->win_x) + x] = e->texture
//			[2][(int)(e->block_w * POS.floor_tex_y + POS.floor_tex_x)];
//		printf("block_w = %f	floor_tex_x = %d	floor_tex_y = %d\n", e->block_w, POS.floor_tex_x, POS.floor_tex_y);
	}
}

void	load_texture(t_env *e)
{
	int		a;
	int		b;

	a = 64;
	b = 64;
	e->tex[0].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/kkalkkal.xpm", &a, &b);
	e->tex[0].data = mlx_get_data_addr(e->tex[0].img, &e->tex[0].bpp,
			&e->tex[0].sizeline, &e->tex[0].endian);
	e->tex[1].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/bbm.xpm", &a, &b);
	e->tex[1].data = mlx_get_data_addr(e->tex[1].img, &e->tex[1].bpp,
			&e->tex[1].sizeline, &e->tex[1].endian);
}

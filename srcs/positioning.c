/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positioning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:12:55 by jukim             #+#    #+#             */
/*   Updated: 2018/06/07 16:44:40 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	pos_hand(t_env *t)
{
	t_env	e;
	int		i;
	int		x;
	int		y;

	e.img_ptr = mlx_new_image(t->mlx_ptr, t->tex[3].width, t->tex[3].height);
	e.data = (int*)mlx_get_data_addr(e.img_ptr, &t->bpp, &t->size_line,
			&t->endian);
	i = 0;
	y = -1;
	while (++y < t->tex[3].height)
	{
		x = -1;
		while (++x < t->tex[3].width)
		{
			if (t->texture[3][i] != 0)
				e.data[(y * (int)t->tex[3].width) + x] =
					t->texture[3][i++];
		}
	}
	mlx_put_image_to_window(t->mlx_ptr, t->win_ptr, e.img_ptr, 
			t->win_x / 2 - t->tex[3].width / 2, t->win_y - t->tex[3].height);
	ft_bzero(e.data, t->tex[3].width * t->tex[3].height * 4);
	if (t->fire == 1)
		t->fire = 0;
}

void	pos_ammo(t_env *t)
{
	t_env	e;
	int		i;
	int		bullet;
	int		x;
	int		y;

	e.img_ptr = mlx_new_image(t->mlx_ptr, t->tex[6].width, t->tex[6].height);
	e.data = (int*)mlx_get_data_addr(e.img_ptr, &t->bpp, &t->size_line,
			&t->endian);
	i = 0;
	y = -1;
	while (++y < t->tex[6].height)
	{
		x = -1;
		while (++x < t->tex[6].width)
		{
			e.data[(y * (int)t->tex[6].width) + x] = t->texture[4][i++];
		}
	}
	bullet = 0;
	while (++bullet <= t->ammo)
		mlx_put_image_to_window(t->mlx_ptr, t->win_ptr, e.img_ptr,
			t->win_x - (t->tex[6].width * bullet), t->tex[6].height);
	ft_bzero(e.data, t->tex[6].width * t->tex[6].height * 4);
}

void	position(t_env *e)
{
	int	x;
	int	y;
	int	i;

	x = -1;
	ft_bzero(e->data, e->win_x * e->win_y * 4);
	while (++x < e->win_x)
	{
		wolf_ray_cast_calc(e, x);
		wolf_ray_cast_dda(e);
		POS.perp_wall_dist = (POS.side < 2 ? (POS.map_x - POS.pos_x +
					(1 - POS.step_x) / 2) / POS.ray_dir_x : (POS.map_y -
						POS.pos_y + (1 - POS.step_y) / 2) / POS.ray_dir_y);
		y = POS.draw_end;
		pos_wall(e, x, y);
		pos_floor(e);
		pos_floor2(e, x, y);
	}
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
	if (e->hand == 1)
		pos_hand(e);
	if (e->val.texture_switch == 1)
		pos_ammo(e);
	i = -1;
	while (++i < 5)
		free(e->texture[i]);
	free(e->texture);
}

void	pos_wall(t_env *e, int x, int y)
{
	POS.line_height = (int)(e->win_y / POS.perp_wall_dist);
	POS.draw_start = -POS.line_height / 2 + e->win_y / 2;
	POS.draw_start < 0 ? POS.draw_start = 0 : 0;
	POS.draw_end = POS.line_height / 2 + e->win_y / 2;
	POS.draw_end >= e->win_y ? POS.draw_end = e->win_y - 1 : 0;
	POS.wall_x = (POS.side < 2 ? POS.pos_y + POS.perp_wall_dist *
			POS.ray_dir_y : POS.pos_x + POS.perp_wall_dist * POS.ray_dir_x);
	POS.wall_x -= floor(POS.wall_x);
	POS.tex_x = (int)(POS.wall_x * e->block_w);
	if (POS.side < 2 && POS.ray_dir_x > 0)
		POS.tex_x = e->block_w - POS.tex_x - 1;
	else if (POS.side > 1 && POS.ray_dir_y < 0)
		POS.tex_x = e->block_w - POS.tex_x - 1;
	y = POS.draw_start - 1;
	while (++y < POS.draw_end)
	{
		POS.d = y * 256 - e->win_y * 128 + POS.line_height * 128;
		POS.tex_y = ((POS.d * e->block_h) / POS.line_height) / 256;
		POS.color = e->texture[0][(int)(e->block_w * POS.tex_y + POS.tex_x)];
		if (e->val.texture_switch == 0)
		{
			POS.side == 1 ? POS.color /= 6 : 0;
			POS.side == 2 ? POS.color /= 3 : 0;
			POS.side == 3 ? POS.color /= 4 : 0;
			POS.door == 1 ? POS.color *= 1.2 : 0;
		}
		else
			POS.side > 1 ? POS.color /= 2 : 0;
		e->data[(y * (int)e->win_x) + x] = POS.color;
	}
}

void	pos_floor(t_env *e)
{
	if (POS.side < 2 && POS.ray_dir_x > 0)
	{
		POS.floor_x_wall = POS.map_x;
		POS.floor_y_wall = POS.map_y + POS.wall_x;
	}
	else if (POS.side < 2 && POS.ray_dir_x < 0)
	{
		POS.floor_x_wall = POS.map_x + 1.0;
		POS.floor_y_wall = POS.map_y + POS.wall_x;
	}
	else if (POS.side > 1 && POS.ray_dir_y > 0)
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
		e->data[y * (int)e->win_x + x] = e->texture[1][(int)
			(e->block_w * POS.floor_tex_y + POS.floor_tex_x)];
		e->data[(int)((e->win_y - y) * e->win_x) + x] = e->texture
			[2][(int)(e->block_w * POS.floor_tex_y + POS.floor_tex_x)];
	}
}

void	load_texture(t_env *e)
{
	e->tex[4].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/redbrick.xpm",
			&e->tex[4].width, &e->tex[4].height);
	e->tex[4].data = (int*)mlx_get_data_addr(e->tex[4].img, &e->tex[4].bpp,
			&e->tex[4].sizeline, &e->tex[4].endian);
	e->tex[1].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/greystone.xpm",
			&e->tex[1].width, &e->tex[1].height);
	e->tex[1].data = (int*)mlx_get_data_addr(e->tex[1].img, &e->tex[1].bpp,
			&e->tex[1].sizeline, &e->tex[1].endian);
	e->tex[2].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/wood.xpm",
			&e->tex[2].width, &e->tex[2].height);
	e->tex[2].data = (int*)mlx_get_data_addr(e->tex[2].img, &e->tex[2].bpp,
			&e->tex[2].sizeline, &e->tex[2].endian);
	e->tex[3].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/hand.xpm",
			&e->tex[3].width, &e->tex[3].height);
	e->tex[3].data = (int*)mlx_get_data_addr(e->tex[3].img, &e->tex[3].bpp,
			&e->tex[3].sizeline, &e->tex[3].endian);
	e->tex[5].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/fire.xpm",
			&e->tex[5].width, &e->tex[5].height);
	e->tex[5].data = (int*)mlx_get_data_addr(e->tex[5].img, &e->tex[5].bpp,
			&e->tex[5].sizeline, &e->tex[5].endian);
	e->tex[6].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/bullet.xpm",
			&e->tex[6].width, &e->tex[6].height);
	e->tex[6].data = (int*)mlx_get_data_addr(e->tex[6].img, &e->tex[6].bpp,
			&e->tex[6].sizeline, &e->tex[6].endian);
}

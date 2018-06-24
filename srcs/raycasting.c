/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 22:00:41 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 21:10:11 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	xpm_to_texture(t_env *e, int i, int j)
{
	while (++j < e->block_w)
	{
		e->texture[0][(i * (int)e->block_w) + j] =
			e->tex[(e->ang == 1 ? 8 : 4)].data[(i * (int)e->block_w) + j];
		e->texture[1][(i * (int)e->block_w) + j] =
			e->tex[1].data[(i * (int)e->block_w) + j];
		e->texture[2][(i * (int)e->block_w) + j] =
			e->tex[2].data[(i * (int)e->block_w) + j];
	}
}

void	wolf_ray_cast(t_env *e)
{
	malloc_texture(e);
	tex_into_texture(e, -1, -1);
	position(e);
	if (e->caption == 1)
		mlx_string_put(e->mlx_ptr, e->win_ptr, e->win_x / 2 - 20,
				e->win_y / 2 - 60, 255, "ARE YOU SURE?");
}

void	wall_texture(t_env *e, int i, int j)
{
	while (++j < e->block_w)
	{
		if (j % 16 == 0)
		{
			e->texture[0][(i * (int)e->block_w) + j] = 0x123123;
		}
		else if (i % 8 == 0)
			e->texture[0][(i * (int)e->block_w) + j] = 0x123123;
		else
			e->texture[0][(i * (int)e->block_w) + j] = 0xFFFFFF - i * 100;
	}
	j = -1;
	while (++j < e->block_w)
		e->texture[1][(i * (int)e->block_w) + j] = (j % 32 == 0 || i % 32 == 0 ?
				0x000000 : 0xFFFFFF);
	j = -1;
	while (++j < e->block_w)
		e->texture[2][(i * (int)e->block_w) + j] = (j % 3 == 0 || i % 5 == 0 ?
			0x000000 : 0x800000);
}

void	wolf_ray_cast_calc(t_env *e, int x)
{
	POS.camera_x = 2 * x / e->win_x - 1;
	POS.ray_dir_x = POS.dir_x + POS.plane_x * POS.camera_x;
	POS.ray_dir_y = POS.dir_y + POS.plane_y * POS.camera_x;
	POS.map_x = (int)POS.pos_x;
	POS.map_y = (int)POS.pos_y;
	POS.delta_dist_x = fabs(1 / POS.ray_dir_x);
	POS.delta_dist_y = fabs(1 / POS.ray_dir_y);
	POS.hit = 0;
	POS.door = 0;
	POS.step_x = (POS.ray_dir_x < 0 ? -1 : 1);
	POS.side_dist_x = (POS.ray_dir_x < 0 ?
			(POS.pos_x - POS.map_x) : (POS.map_x + 1.0 - POS.pos_x))
		* POS.delta_dist_x;
	POS.step_y = (POS.ray_dir_y < 0 ? -1 : 1);
	POS.side_dist_y = (POS.ray_dir_y < 0 ?
			(POS.pos_y - POS.map_y) : (POS.map_y + 1.0 - POS.pos_y))
		* POS.delta_dist_y;
}

void	wolf_ray_cast_dda(t_env *e)
{
	while (POS.hit == 0)
	{
		if (POS.side_dist_x < POS.side_dist_y)
		{
			POS.side_dist_x += POS.delta_dist_x;
			POS.map_x += POS.step_x;
			POS.side = (POS.ray_dir_x > 0 ? 0 : 1);
		}
		else
		{
			POS.side_dist_y += POS.delta_dist_y;
			POS.map_y += POS.step_y;
			POS.side = (POS.ray_dir_y > 0 ? 2 : 3);
		}
		if (e->map[POS.map_y][POS.map_x].wall_type > 0)
		{
			if (e->map[POS.map_y][POS.map_x].wall_type == 6)
				POS.door = 1;
			POS.hit = 1;
		}
	}
}

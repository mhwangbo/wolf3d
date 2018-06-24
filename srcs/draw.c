/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:42:10 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 21:10:28 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	pos_wall2(e, x, y);
}

void	pos_wall2(t_env *e, int x, int y)
{
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

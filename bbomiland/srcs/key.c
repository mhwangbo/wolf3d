/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:14:17 by jukim             #+#    #+#             */
/*   Updated: 2018/06/03 02:10:08 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		wolf_key(int key, t_env *e)
{
	if (key == 126)
	{
		e->map[(int)(POS.pos_y)][(int)(POS.pos_x + POS.dir_x * e->speed)]
			.wall_type == 0 ? POS.pos_x += POS.dir_x * e->speed : 0;
		e->map[(int)(POS.pos_y + POS.dir_y * e->speed)][(int)(POS.pos_x)]
			.wall_type == 0 ? POS.pos_y += POS.dir_y * e->speed : 0;
	}
	if (key == 125)
	{
		e->map[(int)(POS.pos_y)][(int)(POS.pos_x - POS.dir_x * e->speed)]
			.wall_type == 0 ? POS.pos_x -= POS.dir_x * e->speed : 0;
		e->map[(int)(POS.pos_y - POS.dir_y * e->speed)][(int)(POS.pos_x)]
			.wall_type == 0 ? POS.pos_y -= POS.dir_y * e->speed : 0;
	}
	if (key == 124)
	{
		POS.old_dir_x = POS.dir_x;
		POS.dir_x = POS.dir_x * cos(-ROT) - POS.dir_y * sin(-ROT);
		POS.dir_y = POS.old_dir_x * sin(-ROT) + POS.dir_y * cos(-ROT);
		POS.old_plane_x = POS.plane_x;
		POS.plane_x = POS.plane_x * cos(-ROT) - POS.plane_y * sin(-ROT);
		POS.plane_y = POS.old_plane_x * sin(-ROT) + POS.plane_y * cos(-ROT);
	}
	wolf_key2(key, e);
	return (0);
}

void	wolf_key2(int key, t_env *e)
{
	if (key == 123)
	{
		POS.old_dir_x = POS.dir_x;
		POS.dir_x = POS.dir_x * cos(ROT) - POS.dir_y * sin(ROT);
		POS.dir_y = POS.old_dir_x * sin(ROT) + POS.dir_y * cos(ROT);
		POS.old_plane_x = POS.plane_x;
		POS.plane_x = POS.plane_x * cos(ROT) - POS.plane_y * sin(ROT);
		POS.plane_y = POS.old_plane_x * sin(ROT) + POS.plane_y * cos(ROT);
	}
	if (key == 49)
	{
		(e->map[(int)POS.pos_y + 1][(int)POS.pos_x].wall_type == 6) ?
			e->map[(int)POS.pos_y + 1][(int)POS.pos_x].wall_type = 0 : 0;
		(e->map[(int)POS.pos_y - 1][(int)POS.pos_x].wall_type == 6) ?
			e->map[(int)POS.pos_y - 1][(int)POS.pos_x].wall_type = 0 : 0;
		(e->map[(int)POS.pos_y][(int)POS.pos_x + 1].wall_type == 6) ?
			e->map[(int)POS.pos_y][(int)POS.pos_x + 1].wall_type = 0 : 0;
		(e->map[(int)POS.pos_y][(int)POS.pos_x - 1].wall_type == 6) ?
			e->map[(int)POS.pos_y][(int)POS.pos_x - 1].wall_type = 0 : 0;
	}
	if (key == 53)
		exit(0);
	(key >= 123 && key <= 126) || key == 49 ? wolf_ray_cast(e) : 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:14:17 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 20:32:33 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		wolf_key(int key, t_env *e)
{
	if (key == 126 || key == 13)
	{
		e->map[(int)(POS.pos_y)][(int)(POS.pos_x + POS.dir_x * e->speed)]
			.wall_type == 0 ? POS.pos_x += POS.dir_x * e->speed : 0;
		e->map[(int)(POS.pos_y + POS.dir_y * e->speed)][(int)(POS.pos_x)]
			.wall_type == 0 ? POS.pos_y += POS.dir_y * e->speed : 0;
	}
	if (key == 125 || key == 1)
	{
		e->map[(int)(POS.pos_y)][(int)(POS.pos_x - POS.dir_x * e->speed)]
			.wall_type == 0 ? POS.pos_x -= POS.dir_x * e->speed : 0;
		e->map[(int)(POS.pos_y - POS.dir_y * e->speed)][(int)(POS.pos_x)]
			.wall_type == 0 ? POS.pos_y -= POS.dir_y * e->speed : 0;
	}
	if (key == 124 || key == 2)
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
	key == 11 && e->b < 1 && e->i == 0 && e->l == 0 ? e->b = 1 : 0;
	key == 34 && e->b == 1 && e->i < 1 && e->l == 0 ? e->i = 1 : 0;
	key == 37 && e->b == 1 && e->i == 1 && e->l < 2 ? e->l++ : 0;
	if (key == 36 && e->caption == 1)
	{
		e->ang = 1;
		e->caption = 0;
		wolf_win_start(e);
	}
	if (key == 51 && e->caption == 1)
	{
		billy_off(e);
		wolf_ray_cast(e);
	}
	if (key == 123 || key == 0)
	{
		POS.old_dir_x = POS.dir_x;
		POS.dir_x = POS.dir_x * cos(ROT) - POS.dir_y * sin(ROT);
		POS.dir_y = POS.old_dir_x * sin(ROT) + POS.dir_y * cos(ROT);
		POS.old_plane_x = POS.plane_x;
		POS.plane_x = POS.plane_x * cos(ROT) - POS.plane_y * sin(ROT);
		POS.plane_y = POS.old_plane_x * sin(ROT) + POS.plane_y * cos(ROT);
	}
	wolf_key3(key, e);
}

void	wolf_key3(int key, t_env *e)
{
	if (key == 49 && e->val.intro == 1 && e->val.texture_switch != 1)
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
	if (key == 22 && e->val.intro != 1)
	{
		e->val.intro = 1;
		e->val.texture_switch = 1;
		wolf_win_start(e);
	}
	key == 53 ? wolf_exit(e) : 0;
	if (key == 257)
	{
		e->speed = (e->run == 1 ? 0.1 : 0.3);
		e->run = (e->run == 1 ? 0 : 1);
	}
	wolf_key4(key, e);
}

void	wolf_key4(int key, t_env *e)
{
	if (key == 15 && e->val.texture_switch == 1)
	{
		e->hand = (e->hand == 1 ? 0 : 1);
		system("afplay -t 0.1 ./sound/pull_out.mp3 &");
	}
	if (key == 49 && e->val.texture_switch == 1 && e->hand == 1)
	{
		e->ammo > 0 ? e->fire = 1 : 0;
		if (e->ang == 1)
			e->ammo > 0 ? system("afplay ./sound/ang.mp3 &") :
				system("afplay -t 0.1 ./sound/22_magnum.wav");
		else
			e->ammo > 0 ? system("afplay -t 0.1 ./sound/gun_fire.wav &") :
				system("afplay -t 0.1 ./sound/22_magnum.wav");
		e->ammo > 0 ? e->ammo -= 1 : 0;
		e->ammo > 0 ? e->shot = 1 : 0;
		mlx_loop_hook(e->mlx_ptr, animate, e);
	}
	key == 7 ? billy_off(e) : 0;
	wolf_key5(key, e);
}

void	wolf_key5(int key, t_env *e)
{
	if (key == 12)
	{
		e->ammo = 5;
		system("afplay -t 0.1 ./sound/gun_reload_lock_or_click_sound.mp3 &");
	}
	if (key != 49 && key != 15 && e->val.texture_switch == 1)
		e->shot = 0;
	if (key == 16 && e->b == 1 && e->i == 1 && e->l == 2 && e->ang == 0
			&& e->val.texture_switch == 1)
	{
		e->caption = 1;
		wolf_ray_cast(e);
	}
	if (key == 49 && e->val.intro != 1)
		e->val.intro = 1;
	((key >= 123 && key <= 126) || (key >= 0 && key < 3) || key == 13
		|| key == 49 || key == 79 || key == 15 || key == 12) &&
		e->val.intro == 1 ? wolf_ray_cast(e) : 0;
}

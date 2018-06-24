/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positioning.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:12:55 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 20:43:52 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	crack(t_env *e)
{
	t_env	t;
	int		i;
	int		y;
	int		x;
	int		a;

	a = (e->ang == 1 ? 9 : 7);
	t.img_ptr = mlx_new_image(e->mlx_ptr, e->tex[a].width, e->tex[a].height);
	t.data = (int*)mlx_get_data_addr(t.img_ptr, &e->bpp, &e->size_line,
			&e->endian);
	i = 0;
	y = -1;
	while (++y < e->tex[a].height)
	{
		x = -1;
		while (++x < e->tex[a].width)
			t.data[(y * (int)e->tex[a].width) + x] = e->texture[5][i++];
	}
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, t.img_ptr, e->win_x / 2 -
			e->tex[a].width / 2 + 5, e->win_y / 2 - e->tex[a].height / 2 + 5);
	ft_bzero(t.data, e->tex[a].width * e->tex[a].height * 4);
}

void	pos_hand(t_env *t, int i, int y)
{
	t_env	e;
	int		x;

	e.img_ptr = mlx_new_image(t->mlx_ptr, t->tex[3].width, t->tex[3].height);
	e.data = (int*)mlx_get_data_addr(e.img_ptr, &t->bpp, &t->size_line,
			&t->endian);
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
	i = (t->fire == 0 ? 20 : 12);
	x = (t->fire == 0 ? 0 : 30);
	mlx_put_image_to_window(t->mlx_ptr, t->win_ptr, e.img_ptr,
			t->win_x / 2 - t->tex[3].width / 2 + i, t->win_y -
			t->tex[3].height - x);
	ft_bzero(e.data, t->tex[3].width * t->tex[3].height * 4);
	t->fire = (t->fire == 1 ? 0 : 0);
	mlx_string_put(t->mlx_ptr, t->win_ptr, t->win_x / 2, t->win_y / 2,
			(t->ang == 1 ? 0xFF6EB4 : 0x00FF00), "+");
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
	position2(e);
}

void	position2(t_env *e)
{
	int i;

	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
	if (e->val.texture_switch == 1)
		pos_ammo(e);
	if (e->shot == 1)
		crack(e);
	if (e->hand == 1)
		pos_hand(e, 0, -1);
	i = -1;
	while (++i < 6)
		free(e->texture[i]);
	free(e->texture);
}

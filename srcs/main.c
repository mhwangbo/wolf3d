/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:54:29 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/09 20:25:14 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	intro_image(t_env *e)
{
	mlx_hook(e->win_ptr, 2, 2, wolf_key, e);
	e->tex[0].data = mlx_xpm_file_to_image(e->mlx_ptr, "./img/background.xpm",
			&(e->tex[0].width), &(e->tex[0].height));
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->tex[0].data, 0, 0);
	mlx_string_put(e->mlx_ptr, e->win_ptr, e->win_x / 3.3, e->win_y /
			1.3, 0xFFFFFF, "Press [SPACE] to start");
	mlx_loop(e->mlx_ptr);
}

void	wolf_win(t_env *e)
{
	e->mlx_ptr = mlx_init();
	e->win_ptr = mlx_new_window(e->mlx_ptr, e->win_x, e->win_y, "wolf3d");
	system("afplay ./sound/Map.mp3 &");
	load_texture(e);
	e->img_ptr = mlx_new_image(e->mlx_ptr, e->win_x, e->win_y);
	e->data = (int*)mlx_get_data_addr(e->img_ptr, &e->bpp, &e->size_line,
			&e->endian);
	wolf_win_start(e);
}

void	init_value(t_env *e)
{
	e->win_x = 640;
	e->win_y = 480;
	e->block_w = 64;
	e->block_h = 64;
	e->pos.pos_x = 3;
	e->pos.pos_y = 3;
	e->pos.dir_x = -1.0;
	e->pos.dir_y = 0.0;
	e->pos.plane_x = 0.0;
	e->pos.plane_y = 0.66;
	e->speed = 0.1;
	e->ammo = 5;
	e->shot = 0;
	e->b = 0;
	e->i = 0;
	e->l = 0;
	e->ang = 0;
	e->caption = 0;
}

int		main(int ac, char **av)
{
	t_env	e;
	int		**file;

	if (ac != 2)
	{
		ft_putendl("usage: ./wolf3d <map_file>");
		return (0);
	}
	ft_bzero(&e, sizeof(t_env));
	wolf_find_max(av[1], &e);
	file = wolf_read(av[1], &e);
	e.map = (t_vec**)malloc(sizeof(t_vec*) * (e.y_max) + 1);
	ft_bzero(&e.pos, sizeof(t_pos));
	wolf_put_struct(file, &e);
	message();
	init_value(&e);
	wolf_win(&e);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:29:54 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 21:23:42 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		animate(t_env *e)
{
	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	wolf_ray_cast(e);
	return (0);
}

int		wolf_exit(t_env *e)
{
	if (e->img_ptr)
		mlx_destroy_image(e->mlx_ptr, e->img_ptr);
	if (e->win_ptr)
		mlx_destroy_window(e->mlx_ptr, e->win_ptr);
	system("pkill afplay");
	exit(0);
}

void	billy_off(t_env *e)
{
	e->caption = 0;
	e->b = 0;
	e->i = 0;
	e->l = 0;
	if (e->ang == 1)
	{
		system("pkill -9 afplay");
		system("afplay ./sound/Map.mp3 &");
	}
	e->ang = 0;
}

void	message(void)
{
	system("clear");
	ft_putendl("\n\n\t\tWOLF3D\n\nKEYS:");
	ft_putendl("\t[W,S]/[Arrow Key - Up,Down] - Move Forward/Backward");
	ft_putendl("\t[A,D]/[Arrow Key - Left,Right] - Rotate Left/Right");
	ft_putendl("\t[Shift] - Run/Walk\n\t[ESC] - Exit");
	ft_putendl("\t[Space] - Open Hidden Door");
	ft_putendl("\n\t\t-SECRET MODE-\n");
	ft_putendl("\t[R] - Pull In/Out Gun\n\t[Space] - Shoot");
	ft_putendl("\t[Q] - Reload");
}

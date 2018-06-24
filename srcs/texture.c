/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:41:29 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 20:54:22 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	malloc_texture(t_env *e)
{
	int i;

	e->texture = (int**)malloc(sizeof(int*) * 6);
	i = -1;
	while (++i < 3)
		e->texture[i] = (int*)malloc(sizeof(int) *
				(int)(e->block_w * e->block_h));
	e->texture[3] = (int*)malloc(sizeof(int) *
			(int)(e->tex[(e->fire == 1 ? 5 : 3)].height *
				e->tex[(e->fire == 1 ? 5 : 3)].width));
	e->texture[4] = (int*)malloc(sizeof(int) *
			(int)(e->tex[6].height * e->tex[6].width));
	e->texture[5] = (int*)malloc(sizeof(int) *
			(int)(e->tex[(e->ang == 1 ? 9 : 7)].height *
				e->tex[(e->ang == 1 ? 9 : 7)].width));
}

void	tex_into_texture(t_env *e, int i, int j)
{
	while (++i < e->block_h)
	{
		j = -1;
		(e->val.texture_switch == 1) ? xpm_to_texture(e, i, j) :
			wall_texture(e, i, j);
	}
	i = -1;
	while (++i < e->tex[3].height)
	{
		j = -1;
		while (++j < e->tex[3].width)
			e->texture[3][(i * e->tex[3].width) + j] =
				e->tex[(e->fire == 1 ? 5 : 3)].data[(i *
						e->tex[(e->fire == 1 ? 5 : 3)].width) + j];
	}
	tex_into_texture2(e, -1, -1);
}

void	tex_into_texture2(t_env *e, int i, int j)
{
	while (++i < e->tex[6].height)
	{
		j = -1;
		while (++j < e->tex[6].width)
			e->texture[4][(i * e->tex[6].width) + j] =
				e->tex[6].data[(i * e->tex[6].width) + j];
	}
	i = -1;
	while (++i < e->tex[(e->ang == 1 ? 9 : 7)].height)
	{
		j = -1;
		while (++j < e->tex[(e->ang == 1 ? 9 : 7)].width)
			e->texture[5][(i * e->tex[(e->ang == 1 ? 9 : 7)].width) + j] =
				e->tex[(e->ang == 1 ? 9 : 7)].data[(i * e->tex[(e->ang ==
							1 ? 9 : 7)].width) + j];
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
	load_texture2(e);
}

void	load_texture2(t_env *e)
{
	e->tex[6].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/bullet.xpm",
			&e->tex[6].width, &e->tex[6].height);
	e->tex[6].data = (int*)mlx_get_data_addr(e->tex[6].img, &e->tex[6].bpp,
			&e->tex[6].sizeline, &e->tex[6].endian);
	e->tex[7].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/crack.xpm",
			&e->tex[7].width, &e->tex[7].height);
	e->tex[7].data = (int*)mlx_get_data_addr(e->tex[7].img, &e->tex[7].bpp,
			&e->tex[7].sizeline, &e->tex[7].endian);
	e->tex[8].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/rainbow.xpm",
			&e->tex[8].width, &e->tex[8].height);
	e->tex[8].data = (int*)mlx_get_data_addr(e->tex[8].img, &e->tex[8].bpp,
			&e->tex[8].sizeline, &e->tex[8].endian);
	e->tex[9].img = mlx_xpm_file_to_image(e->mlx_ptr, "img/billy.xpm",
			&e->tex[9].width, &e->tex[9].height);
	e->tex[9].data = (int*)mlx_get_data_addr(e->tex[9].img, &e->tex[9].bpp,
			&e->tex[9].sizeline, &e->tex[9].endian);
}

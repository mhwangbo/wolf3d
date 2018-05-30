/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:54:29 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/30 01:12:48 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf_ray_cast(t_env *e)
{
	int		x;
	int		y;

	ft_bzero(e->data, e->win_x * e->win_y * 4);
	x = -1;
	while(++x < e->win_x)
	{
		POS.camera.x = 2 * x / e->win_x - 1;
		POS.ray_dir_x = POS.dir_x + POS.plane_x * POS.camera.x;
		POS.ray_dir_y = POS.dir_y + POS.plane_y * POS.camera.x;

		POS.map_x = (int)POS.pos_x;
		POS.map_y = (int)POS.pos_y;


		POS.delta_dist_x = fabs(1 / POS.ray_dir_x);
		POS.delta_dist_y = fabs(1 / POS.ray_dir_y);

		POS.hit = 0;
		//step and initial side distance
		if (POS.ray_dir_x < 0)
		{
			POS.step_x = -1;
			POS.side_dist_x = (POS.pos_x - POS.map_x) * POS.delta_dist_x;
		}
		else
		{
			POS.step_x = 1;
			POS.side_dist_x = (POS.map_x + 1.0 - POS.pos_x) * POS.delta_dist_x;
		}
		if (POS.ray_dir_y < 0)
		{
			POS.step_y = -1;
			POS.side_dist_y = (POS.pos_y - POS.map_y) * POS.delta_dist_y;
		}
		else
		{
			POS.step_y = 1;
			POS.side_dist_y = (POS.map_y + 1.0 - POS.pos_y) * POS.delta_dist_y;
		}
		//DDA
		while (POS.hit == 0)
		{
			if (POS.side_dist_x < POS.side_dist_y)
			{
				POS.side_dist_x += POS.delta_dist_x;
				POS.map_x += POS.step_x;
				side = 0;
			}
			else
			{
				POS.side_dist_y += POS.delta_dist_y;
				POS.map_y += POS.step_y;
				side = 1;
			}
			if (e->map[POS.map_y][POS.map_x].wall_type > 0)
				POS.hit = 1;
		}
		if (POS.side == 0)
			POS.perp_wall_dist = (POS.map_x - POS.pos_x + (1 - POS.step_x) / 2) / POS.ray_dir_x;
		else
			POS.perp_wall_dist = (POS.map_y - POS.pos_y + (1 - POS.step_y) / 2) / POS.ray_dir_y;
		int		line_height = (int)(e->win_y / POS.perp_wall_dist);
		int		draw_start = -line_height / 2 + e->win_y / 2;
		if (draw_start < 0)
			draw_start = 0;
		int		draw_end = line_height / 2 + e->win_y / 2;
		if (draw_end >= e->win_y)
			draw_end = e->win_y - 1;

		double	wall_x;
		if (POS.side == 0)
			wall_x = POS.pos_y + POS.perp_wall_dist * POS.ray_dir_y;
		else
			wall_x = POS.pos_x + POS.perp_wall_dist * POS.ray_dir_x;
		wall_x -= floor(wall_x);

		int		tex_x = (int)(wall_x * e->block_w);
		if (POS.side == 0 && POS.ray_dir_x > 0)
			tex_x = e->block_w - tex_x - 1;
		if (POS.side == 1 && POS.ray_dir_x < 0)
			tex_x = e->block_w - tex_x - 1;
		y = draw_start - 1;
		while (++y < draw_end)
		{
			int color = 0xFFFFFF;
			if (POS.side == 1)
				color = 0x800000;
			e->data[(y * (int)e->win_x) + x] = color;
		}
	}
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}

int		wolf_key(int key, t_env *e)
{
	if (key == 126)
	{
		if (e->map[(int)(POS.pos_y)][(int)(POS.pos_x + POS.dir_x * e->speed)].wall_type == 0)
			POS.pos_x += POS.dir_x * e->speed;
		if (e->map[(int)(POS.pos_y + POS.dir_y * e->speed)][(int)(POS.pos_x)].wall_type == 0)
		   POS.pos_y += POS.dir_y * e->speed;
	}
	if (key == 125)
	{
		if (e->map[(int)(POS.pos_y)][(int)(POS.pos_x - POS.dir_x * e->speed)].wall_type == 0)
			POS.pos_x -= POS.dir_x * e->speed;
		if (e->map[(int)(POS.pos_y - POS.dir_y * e->speed)][(int)(POS.pos_x)].wall_type == 0)
		   POS.pos_y -= POS.dir_y * e->speed;
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
	if (key == 123)
	{
		POS.old_dir_x = POS.dir_x;
		POS.dir_x = POS.dir_x * cos(ROT) - POS.dir_y * sin(ROT);
		POS.dir_y = POS.old_dir_x * sin(ROT) + POS.dir_y * cos(ROT);
		POS.old_plane_x = POS.plane_x;
		POS.plane_x = POS.plane_x * cos(ROT) - POS.plane_y * sin(ROT);
		POS.plane_y = POS.old_plane_x * sin(ROT) + POS.plane_y * cos(ROT);
	}
	wolf_ray_cast(e);
	return (0);
}

void	wolf_win(t_env *e)
{
	e->mlx_ptr = mlx_init();
	e->win_ptr = mlx_new_window(e->mlx_ptr, e->win_x, e->win_y, "wolf3d");
	e->img_ptr = mlx_new_image(e->mlx_ptr, e->win_x, e->win_y);
	e->data = (int*)mlx_get_data_addr(e->img_ptr, &e->bpp, &e->size_line,
			&e->endian);
	wolf_ray_cast(e);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
	mlx_hook(e->win_ptr, 2, 2, wolf_key, e);
	mlx_loop(e->mlx_ptr);
}

void 	wolf_find_max(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		i;
	int		tmp_max;

	fd = open(av, O_RDONLY);
	if (fd < 1)
		exit (0);
	i = -1;
	while (get_next_line(fd, &line) == 1)
	{
		e->y_max += 1;
		if (e->y_max == 1)
			while (line[++i])
				(line[i] != ' ' && (i - 1 == -1 || line[i - 1] == ' ')) ?
					e->x_max += 1 : 0;
		i = -1;
		tmp_max = 0;
		while (e->y_max != 1 && line[++i])
			(line[i] != ' ' && (i - 1 == -1 || line[i - 1] == ' ')) ?
				tmp_max += 1 : 0;
		free(line);
	}
	close(fd);
}

int		*wolf_split(char *line, t_env *e)
{
	int		*line_i;
	char	**tmp;
	int		x;

	line_i = ft_memalloc(sizeof(int) * e->x_max + 1);
	tmp = ft_strsplit(line, ' ');
	x = -1;
	while (++x < e->x_max)
	{
		line_i[x] = ft_atoi(tmp[x]);
		free(tmp[x]);
	}
	free(tmp);
	return (line_i);
}

int		**wolf_read(char *av, t_env *e)
{
	int		**file;
	char	*line;
	int		fd;
	int		y;
	int		i;

	fd = open(av, O_RDONLY);
	y = -1;
	i = 0;
	file = (int**)malloc(sizeof(int*) * (e->y_max + 1));
	while (get_next_line(fd, &line) > 0 && ++y < e->y_max)
	{
		file[y] = wolf_split(line, e);
		free(line);
	}
	if (get_next_line(fd, &line) == 0 && ++y < e->y_max)
		file[y] = wolf_split(line, e);
	file[y] = NULL;
	close(fd);
	return (file);
}

void	wolf_put_struct(int **file, t_env *e)
{
	int		y;
	int		x;

	y = -1;
	while (++y < e->y_max)
	{
		x = -1;
		e->map[y] = ft_memalloc(sizeof(t_vec) * (e->x_max) + 1);
		while (++x < e->x_max)
		{
			e->map[y][x].x = x;
			e->map[y][x].y = y;
			e->map[y][x].wall_type = file[y][x];
			(e->map[y][x].wall_type == 1) ? e->map[y][x].color = 0x800000 : 0;
		}
	}
}

int		main(int ac, char **av)
{
	t_env	e;
	int		**file;

	if (ac != 2)
		return (0);
	ft_bzero(&e, sizeof(t_env));
	wolf_find_max(av[1], &e);
	file = wolf_read(av[1], &e);
	e.map = (t_vec**)malloc(sizeof(t_vec*) * (e.y_max) + 1);
	ft_bzero(&e.pos, sizeof(t_pos));
	wolf_put_struct(file, &e);
	e.win_x = 640;
	e.win_y = 480;
	e.block_w = 64;
	e.block_h = 64;
	e.pos.pos_x = 22;
	e.pos.pos_y = 11.5;
	e.pos.dir_x = -1.0;
	e.pos.dir_y = 0.0;
	e.pos.plane_x = 0.0;
	e.pos.plane_y = 0.66;
	e.speed = 0.1;
	wolf_win(&e);
	return (0);
}
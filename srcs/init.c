/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:16:24 by jukim             #+#    #+#             */
/*   Updated: 2018/06/09 20:25:02 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf_win_start(t_env *e)
{
	ft_bzero(e->data, e->win_x * e->win_y * 4);
	if (e->ang == 1)
	{
		system("pkill -9 afplay");
		system("afplay ./sound/heman.mp3 &");
	}
	(e->val.intro != 1) ? intro_image(e) : wolf_ray_cast(e);
	mlx_hook(e->win_ptr, 2, 2, wolf_key, e);
	mlx_hook(e->win_ptr, 17, 0, wolf_exit, e);
	mlx_loop(e->mlx_ptr);
}

void	wolf_find_max(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		i;
	int		tmp_max;

	fd = open(av, O_RDONLY);
	if (fd < 1)
		exit(0);
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
		}
	}
}

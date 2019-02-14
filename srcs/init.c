/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 23:16:24 by jukim             #+#    #+#             */
/*   Updated: 2018/06/17 20:35:42 by jukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf_win_start(t_env *e)
{
	ft_bzero(e->data, e->win_x * e->win_y * 4);
	mlx_hook(e->win_ptr, 2, 2, wolf_key, e);
	mlx_hook(e->win_ptr, 17, 0, wolf_exit, e);
	if (e->ang == 1)
	{
		system("pkill -9 afplay");
		system("afplay ./sound/heman.mp3 &");
	}
	(e->val.intro != 1) ? intro_image(e) : wolf_ray_cast(e);
	mlx_loop(e->mlx_ptr);
}

void	wolf_find_max(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		i;

	file_check(av);
	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line) == 1 && (i = -1))
	{
		e->x_max = 0;
		while (line[++i] != '\0')
		{
			ft_isdigit(line[i]) == 1 && (line[i + 1] == ' ' || line[i + 1]
					== '\0') ? e->x_max++ : 0;
			!ft_isdigit(line[i]) && line[i] != ' ' ? error_exit(2, fd) : 0;
			if (line[i + 1] == '\0')
			{
				e->y_max > 0 && e->x_max != e->x_max2 ? error_exit(2, fd) : 0;
				e->x_max2 = e->x_max;
			}
		}
		free(line);
		e->y_max += 1;
	}
	close(fd);
}

int		*wolf_split(char *line, t_env *e)
{
	int		*line_i;
	char	**tmp;
	int		x;

	line_i = ft_memalloc(sizeof(int) * e->x_max);
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

	fd = open(av, O_RDONLY);
	y = -1;
	file = (int**)malloc(sizeof(int*) * e->y_max);
	while (get_next_line(fd, &line) > 0 && ++y < e->y_max)
	{
		file[y] = wolf_split(line, e);
		free(line);
	}
	close(fd);
	return (file);
}

void	wolf_put_struct(int **file, t_env *e)
{
	int		y;
	int		x;
	int		c;

	c = 0;
	y = -1;
	e->x_max < 3 || e->y_max < 3 ? error_exit(3, 0) : 0;
	while (++y < e->y_max)
	{
		x = -1;
		e->map[y] = ft_memalloc(sizeof(t_vec) * (e->x_max) + 1);
		while (++x < e->x_max)
		{
			if (y == 0 || x == 0 || x == e->x_max - 1 || y == e->y_max - 1)
				file[y][x] != 1 ? error_exit(3, 0) : 0;
			if (y == 1 && x == 1)
				file[y][x] != 0 ? error_exit(3, 0) : 0;
			file[y][x] != 1 ? c++ : 0;
			e->map[y][x].x = x;
			e->map[y][x].y = y;
			e->map[y][x].wall_type = file[y][x];
		}
	}
	c == 0 ? error_exit(3, 0) : 0;
}

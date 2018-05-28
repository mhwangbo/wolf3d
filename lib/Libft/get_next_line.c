/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 00:00:23 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/11 17:03:29 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_line(const int fd, char **data, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data[fd][i] != '\n' && data[fd][i] != '\0')
		i++;
	if (data[fd][i] == '\n')
	{
		*line = ft_strsub(data[fd], 0, i);
		tmp = ft_strdup(data[fd] + i + 1);
		ft_strdel(&data[fd]);
		data[fd] = tmp;
		if (data[fd][0] == '\0')
			ft_strdel(&data[fd]);
	}
	else if (data[fd][i] == '\0')
	{
		*line = ft_strdup(data[fd]);
		ft_strdel(&data[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*data[256 * 256];
	int			rd;
	char		*tmp;
	char		buff[BUFF_SIZE + 1];

	if (BUFF_SIZE < 1 || fd < 0 || line == NULL)
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if (data[fd] == NULL)
			data[fd] = ft_strnew(1);
		tmp = ft_strjoin(data[fd], buff);
		ft_strdel(&data[fd]);
		data[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (rd < 0)
		return (-1);
	if (rd == 0 && data[fd] == '\0')
		return (0);
	return (get_line(fd, data, line));
}

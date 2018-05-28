/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 23:09:41 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/05 03:08:04 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char*)&haystack[i]);
	while (haystack[i] != '\0')
	{
		h = 0;
		while (needle[j + h] == haystack[i + h])
		{
			h++;
			if (needle[j + h] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

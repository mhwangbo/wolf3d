/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 23:08:37 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/04/03 23:41:28 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	h;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char*)&haystack[i]);
	while ((i < len) && (haystack[i] != '\0'))
	{
		h = 0;
		while (needle[j + h] == haystack[i + h])
		{
			if (i + h == len)
				return (NULL);
			h++;
			if (needle[j + h] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

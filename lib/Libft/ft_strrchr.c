/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:11:24 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/06 00:20:20 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	tmp;

	len = ft_strlen(s);
	tmp = c;
	while (s[len] != tmp)
	{
		if ((len == 0) && (s[len] != tmp))
			return (NULL);
		len--;
	}
	return ((char*)&s[len]);
}

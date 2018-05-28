/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:08:59 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/05 00:36:10 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c,
		size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(((unsigned char*)dst)[i]) = (((unsigned char*)src)[i]);
		if (((unsigned char*)src)[i] == (unsigned char)c)
			return (&((unsigned char*)dst)[i + 1]);
		i++;
	}
	return (NULL);
}

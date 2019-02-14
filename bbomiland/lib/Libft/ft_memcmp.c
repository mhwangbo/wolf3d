/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:39:59 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/05 01:53:48 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	r;

	r = 0;
	while (r < n)
	{
		if (((unsigned char*)s1)[r] != ((unsigned char*)s2)[r])
			return (((unsigned char*)s1)[r] - ((unsigned char*)s2)[r]);
		r++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:56:27 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/05 01:52:05 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;
	size_t			i;

	i = 0;
	tmp_src = (unsigned char*)src;
	tmp_dst = (unsigned char*)dst;
	if (tmp_src < tmp_dst)
		while (len)
		{
			tmp_dst[len - 1] = tmp_src[len - 1];
			len--;
		}
	else
		while (i < len)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	return (dst);
}

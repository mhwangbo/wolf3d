/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:31:29 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/04 22:33:19 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	void	*temp;

	i = 0;
	temp = s;
	if (n == 0)
		return ;
	else
	{
		while (i < n)
		{
			*(unsigned char*)temp = 0;
			temp++;
			i++;
		}
	}
}

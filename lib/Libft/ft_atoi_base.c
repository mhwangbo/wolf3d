/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:16:04 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/15 17:28:28 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi_base(const char *s)
{
	int					i;
	unsigned long long	j;
	int					sign;

	i = 0;
	j = 0;
	sign = 1;
	while (*s && ft_iswhite(s[i]) == 1)
		i++;
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
		i += 2;
	while (*s && ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')
				|| (s[i] >= 'A' && s[i] <= 'Z')))
	{
		if (s[i] >= '0' && s[i] <= '9')
			j = ((j * 16) + (s[i++] - '0'));
		else if (s[i] >= 'a' && s[i] <= 'f')
			j = (j * 16) + (s[i++] - 87);
		else if (s[i] >= 'A' && s[i] <= 'F')
			j = (j * 16) + (s[i++] - 55);
	}
	return (j * sign);
}

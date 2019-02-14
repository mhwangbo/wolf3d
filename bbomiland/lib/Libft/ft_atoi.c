/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:16:04 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/10 13:29:06 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int					i;
	unsigned long long	j;
	int					sign;

	i = 0;
	j = 0;
	sign = 1;
	while (*s && ft_iswhite(s[i]) == 1)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (*s && s[i] >= '0' && s[i] <= '9')
	{
		j = ((j * 10) + (s[i++] - '0'));
		if (i > 19 || j >= 9223372036854775808ULL)
			return (sign == 1 ? -1 : 0);
	}
	return (j * sign);
}

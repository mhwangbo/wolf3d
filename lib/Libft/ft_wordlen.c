/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 23:42:51 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/15 17:31:03 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordlen(char const *s, char c)
{
	int		j;

	j = 0;
	while (s[j] != c && s[j] != '\0')
		j++;
	return (j);
}

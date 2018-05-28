/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:38:41 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/03/24 20:12:53 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		h;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = (char**)malloc(sizeof(char*) * (ft_wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	while (s[i] != '\0')
		if (s[i] != c)
		{
			h = 0;
			split[j] = (char*)malloc(sizeof(char) * ft_wordlen(&s[i], c) + 1);
			while (s[i] != c && s[i] != '\0')
				split[j][h++] = s[i++];
			split[j++][h] = '\0';
		}
		else
			i++;
	split[j] = NULL;
	return (split);
}

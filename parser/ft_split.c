/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:07:22 by atouati           #+#    #+#             */
/*   Updated: 2022/11/09 17:23:44 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	get_strings(char const *s, char c)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (s[i] != c && s[i - 1] == c && s[i]))
			n++;
		i++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**result;
	int		i;
	int		o;
	int		nb_strings;

	i = 0;
	if (!s)
		return (NULL);
	nb_strings = get_strings (s, c);
	result = malloc((nb_strings + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	while (index < nb_strings)
	{
		while (s[i] == c && s[i])
			i++;
		o = i;
		while (s[i] != c && s[i])
			i++;
		result[index++] = ft_substr(s, o, i - o);
	}
	result[index] = NULL;
	//free((char *)s);
	return (result);
}

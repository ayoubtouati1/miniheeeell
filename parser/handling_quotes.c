/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:25:03 by atouati           #+#    #+#             */
/*   Updated: 2022/11/09 16:13:27 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_sep(char **dst, char *str, int i, t_token *ptr)
{
	char	*dest;
	char	sep;

	dest = *dst;
	dest[i] = str[i];
	i++;
	if (!ptr->quotes)
		sep = '"';
	else
		sep = '\'';
	while (str[i] && str[i] != sep)
	{
		if (str[i] == ptr->a)
			dest[i] = ptr->b;
		else
			dest[i] = str[i];
		i++;
	}
	if (str[i] != sep)
		return (0);
	else
	{
		dest[i] = str[i];
		i++;
	}
	return (i);
}

char	*handling_quotes(char	*str, char a, char b)
{
	int		i;
	char	*dest;
	t_token	ptr;

	ptr.a = a;
	ptr.b = b;
	dest = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			ptr.quotes = 0;
			i = replace_sep(&dest, str, i, &ptr);
		}
		else if (str[i] == '\'')
		{
			ptr.quotes = 1;
			i = replace_sep(&dest, str, i, &ptr);
		}
		else
		{
			dest[i] = str[i];
			i++;
		}
		if (i == 0)
			return (NULL);
	}
	dest[i] = '\0';
	free(str);
	return (dest);
}

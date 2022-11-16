/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 02:55:18 by atouati           #+#    #+#             */
/*   Updated: 2022/11/13 20:33:14 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_free(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

char	*count_space_and_alloc(char *str, char *dest, int i)
{
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str) + 1;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if ((str[i] == '<' || str[i] == '>'
					|| str[i] == '|')
				&& (str[i + 1] == '\0'))
				j++;
			else if ((str[i] == '<' && str[i + 1] != '<')
				|| (str[i] == '>' && str[i + 1] != '>')
				|| str[i] == '|')
				j += 2;
		}
		i++;
	}
	dest = malloc(sizeof(char) * (len + j));
	if (!dest)
		return (NULL);
	return (dest);
}

int	skeep_opirations(char **str, char **dest, int *i, int *j)
{
	int	len;

	len = 0;
	while (((*str)[*i] == '<'
		|| (*str)[*i] == '>'
		|| (*str)[*i] == '|') && (*str)[*i])
	{
		(*dest)[*j] = (*str)[*i];
		(*j)++;
		(*i)++;
		len++;
	}
	if (*i == 0)
		return (len);
	if (((*str)[*i - 1] == '<'
		|| (*str)[*i - 1] == '>'
		|| (*str)[*i - 1] == '|') && !(*str)[*i])
			len = -4;
	return (len);
}

int	add_after_opirations(char **str, char	**dest, int *i, int *j)
{
	int	len;

	len = skeep_opirations(str, dest, i, j);
	if (len != 0 && len != -4)
	{
		(*dest)[*j] = ' ';
		len = 0;
		(*j)++;
	}
	if (!(*str)[*i])
		return (0);
	return (1);
}

int	add_inside_quot(char **str, char **dest, int *i, int *j)
{
	if ((*str)[*i] == '"')
	{
		(*dest)[*j] = (*str)[*i];
			(*i)++;
			(*j)++;
		while ((*str)[*i] != '"' && (*str)[*i] != '\0')
		{
			(*dest)[*j] = (*str)[*i];
			(*i)++;
			(*j)++;
		}
		if ((*str)[*i] == '\0')
			return (0);
	}
	return (1);
}
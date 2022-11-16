/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 01:40:30 by atouati           #+#    #+#             */
/*   Updated: 2022/11/13 21:22:49 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(t_token *ptr, char *str)
{
	if (ptr->d_quot == 1 && str[ptr->n] == '"')
	{
		ptr->d_quot = 0;
	}
	else if (str[ptr->n] == '"')
	{
		ptr->d_quot = 1;
	}
	if (str[ptr->n] == '\'' && ptr->s_quot == 1)
	{
		ptr->s_quot = 0;
	}
	else if (str[ptr->n] == '\'' && quot_cont(str, ptr->n, '"') == 1 && !quot_cont(str, ptr->i, '\''))
		ptr->s_quot = 1;
}

char	*copy_no_dollar(char *str, char *tmp, t_token *ptr)
{
	char *dest;

	ptr->n = ptr->i;
	ptr->j = ptr->i;
	ptr->i = cont_dollar(str, ptr->i);
	ptr->j = ptr->i - ptr->j;
	dest = malloc(sizeof(char) * ptr->j + 1);
	ptr->j = 0;
	while (str[ptr->n] && str[ptr->n] != '$')
	{
		check_quotes(ptr, str);
		dest[ptr->j] = str[ptr->n];
		ptr->j++;
		ptr->n++;
	}
	dest[ptr->j] = '\0';
	tmp = ft_strrjoin(tmp, dest);
	return (tmp);
}

void	count_for_alloc(char *str, t_token *ptr)
{
	while (str[ptr->i] && str[ptr->i] != '"'  && str[ptr->i] != '\'')
	{
		ptr->j++;
		ptr->i++;
	}
}

char	*copy_no_expand(char *str, char *tmp, t_token *ptr)
{
	char	*dest;

	if (ptr->s_quot == 1 || (((str[ptr->i] == '$' && str[ptr->i + 1] == '\0')
				|| (str[ptr->i] == '$' && str[ptr->i + 1] == ' '))
			|| (ptr->d_quot == 1 && str[ptr->i] == '$'
				&& (str[ptr->i + 1] == '"' || str[ptr->i + 1] == '\''))))
	{
		ptr->j = 0;
		count_for_alloc(str, ptr);
		dest = malloc(sizeof(char) * ptr->j + 1);
		ptr->j = 0;
		while (str[ptr->n] != '\0' && str[ptr->n] != '"' && str[ptr->n] != '\'')
		{
			dest[ptr->j] = str[ptr->n];
			ptr->j++;
			ptr->n++;
		}
		dest[ptr->j] = '\0';
		tmp = ft_strrjoin(tmp, dest);
	}
	return (tmp);
}

char	*digit_expand(char *str, char *tmp, t_token *ptr, char **env)
{
	ptr->i = ptr->n;
	if (str[ptr->i] == '$' && ft_isdigit(str[ptr->i + 1]) == 1)
	{
		ptr->i++;
		tmp = ft_strrjoin(tmp, expand(str, ptr->i, env));
		ptr->i = cont_dollar(str, ptr->n + 1);
		tmp = ft_strrjoin(tmp, ft_substr(str, ptr->n + 2, ptr->i - ptr->n - 2));
	}
	return (tmp);
}
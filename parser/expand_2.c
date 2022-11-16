/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 02:27:46 by atouati           #+#    #+#             */
/*   Updated: 2022/11/14 21:51:37 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *dollar_expand(char *str, char *tmp, t_token *ptr, char **env)
{
	if (((str[ptr->i] == '$' && str[ptr->i + 1] == '"')
			|| (str[ptr->i] == '$' && str[ptr->i + 1] == '\''))
		&& (ptr->d_quot == 0))
	{
		ptr->i++;
	}
	else
	{
		if (quot_cont(str, ptr->i, '\'') == 1 && ptr->s_quot == 1)
		{
			ptr->s_quot = 0;
		}
		else
		{
			if (str[ptr->i] == '$' && str[ptr->i + 1] != ' ' && str[ptr->i + 1] != '\0' && str[ptr->i + 1] != '\'' && str[ptr->i + 1] != '"')
			{
				ptr->i++;
				tmp = ft_strrjoin(tmp, expand(str, ptr->i, env));
			}
			while (str[ptr->i] && (str[ptr->i] != '"' && str[ptr->i] != '\'' && str[ptr->i] != '$' && str[ptr->i] != '.' && str[ptr->i] != ',' && str[ptr->i] != ' '))
				ptr->i++;
		}
	}
	return (tmp);
}

char	**alloc_des(char **env)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (0);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		dst[i] = ft_substr(env[i], 0, j);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

char	*expand(char *str, int i, char **env)
{
	int		j;
	char	*dest;

	j = i;
	while (str[j] && (str[j] != '"' && str[j] != '\'' && str[j] != '$' && str[j] != '.' && str[j] != ',' && str[j] != ' '))
		j++;
	if (ft_isdigit(str[i]))
		j = i + 1;
	dest = ft_substr(str, i, j - i);
	dest = comper_to_env(dest, env);
	return (dest);
}

char	*comper_to_env(char *dest, char **env)
{
	int		i;
	char	**dst;

	i = 0;
	dst = alloc_des(env);
	while (dst[i])
	{
		if (!ft_memcmp(dest, dst[i]))
		{
			free(dest);
			dest = ft_substr(env[i], ft_strlen(dst[i]) + 1,
					ft_strlen(env[i]) - ft_strlen(dst[i]));
			ft_free(dst);
			return (dest);
		}
		i++;
	}
	ft_free(dst);
	free(dest);
	return (NULL);
}
char	*check_expand(char *str, char **env, int type)
{
	char	*dest;
	char	*tmp;
	t_token	ptr;

	ptr.i = 0;
	ptr.n = 0;
	ptr.s_quot = 0;
	ptr.d_quot = 0;
	tmp = malloc(sizeof(char));
	tmp[0] = '\0';
	while (str[ptr.i])
	{
		//sleep(1);
		tmp = copy_no_dollar(str,tmp, &ptr);
		if (type == HEREDOC)
		{
			ptr.s_quot = 1;
			tmp = copy_no_expand(str,tmp, &ptr);
			continue ;
		}
		tmp = copy_no_expand(str,tmp, &ptr);
		tmp = digit_expand(str,tmp, &ptr, env);
		tmp = dollar_expand(str,tmp, &ptr, env);
		//sleep(2);
	}
	free(str);
	return (tmp);
}

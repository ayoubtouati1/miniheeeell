/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 22:01:38 by atouati           #+#    #+#             */
/*   Updated: 2022/11/13 21:21:32 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	*ft_sstrcpy(char *str, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (i < len_s1)
	{
		str[i] = (char)s1[i];
		i++;
	}
	while (j < len_s2)
		str[i++] = (char)s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strrjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(((len_s1 + len_s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	str = ft_sstrcpy(str, (char *)s1, (char *)s2);
	free((char *)s1);
	free((char *)s2);
	return (str);
}

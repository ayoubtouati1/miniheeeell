/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 06:05:10 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/14 06:09:08 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	*ms_getprompt()
{
	char	*prompt;
	char	*name;
	char	*dir;

	name = getenv("LOGNAME");
	dir = getenv("PWD");
	prompt = ft_calloc(ft_strlen(name) + ft_strlen(dir) + 16, sizeof(char));
	ft_strlcat(prompt, name, ft_strlen(name) + 1);
	ft_strlcat(prompt, ":\033[1;34m", ft_strlen(prompt) + 9);
	ft_strlcat(prompt, dir, ft_strlen(prompt) + ft_strlen(dir) + 1);
	ft_strlcat(prompt, "\x1b[0m$ ", ft_strlen(prompt) + 8);
	return (prompt);
}
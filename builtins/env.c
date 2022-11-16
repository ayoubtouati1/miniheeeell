/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:36:35 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/11 04:24:45 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"
#include <stdio.h>
#include "../libft/libft.h"

int    run_env(t_list_env *env)
{
    while (env && env->next != NULL)
	{
	    ft_putendl_fd(env->value, STDOUT);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, STDOUT);
	return (0);
}

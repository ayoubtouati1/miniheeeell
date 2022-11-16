/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:26:34 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/04 16:53:46 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"
t_list_env *new_env_malloc(char *name, char *value)
{
	t_list_env *new_env;

	new_env = (t_list_env *)malloc(sizeof(t_list_env));
	if (!new_env)
		return NULL;
	new_env->name = name;
	new_env->value = value;
	new_env->next = NULL;
	return new_env;
}

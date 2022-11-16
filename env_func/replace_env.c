/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:29:37 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/11 00:04:10 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"
#include "../libft/libft.h"
void	replace_env(t_list_env **list, char *name, char *value)
{
	t_list_env *tmp;
	if ((list) && (*list))
	{
		tmp = *list;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name , name) == 0)
			{
				free(tmp->value);
				tmp->value = value;
			}
			tmp = tmp->next;
		}
		 
	}	
}

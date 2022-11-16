/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:44:37 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/11 04:15:41 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell2.h"
void    del_at_env(t_list_env **lst, char *str)
{
    t_list_env  *tmp;
    t_list_env  *prev;
    
    if (!lst || (*lst))
        return ;
    tmp = *lst;
    prev = NULL;
    while (ft_strncmp(tmp->name, str) != 0 && tmp->name != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (ft_strncmp(tmp->value, str) == 0)
    {
        free(tmp->value);
        free(tmp);
    }
}
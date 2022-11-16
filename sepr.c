/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:49:36 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/13 02:55:23 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell2.h"

t_minishell *next_sep(t_minishell *token, int skip)
{
    if (token && skip)
        token = token->next;
    while (token && token->type < INPUT_FILE)
       token = token->next;
    return (token);
}

t_minishell *prev_sep(t_minishell *token, int skip)
{
    if (token && skip)
        token = token->next;
    while (token && token->type < INPUT_FILE)
        token = token->next;
    return (token);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:36:22 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/11 19:54:02 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

int     run_builtins(char **argv, t_shell *mini)
{
    int	result;
	
	result = 0;
	if (ft_strcmp(argv[0], "echo") == 0)
		result = ft_echo(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		result = ft_cd(argv, mini->env);
	if (ft_strcmp(argv[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(argv[0], "env") == 0)
		result = run_env(mini->env);
	if (ft_strcmp(argv[0], "export") == 0)
		result = run_export(argv, mini->env, mini->export_env);
	if (ft_strcmp(argv[0], "unset") == 0)
		result  = run_unset(argv, mini);
	return (result);
}

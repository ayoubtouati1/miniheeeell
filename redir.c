/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:58:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/15 23:41:28 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

void    redir(t_shell *mini, t_minishell *token, int type)
{
    ft_close(mini->fdout);
    if (type == OUTPUT_FILE)
        mini->fdout = open(token->data, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    else
        mini->fdout = open(token->data, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (mini->fdout == -1)
    {
        ft_putstr_fd("minishell: ",STDERR);
        ft_putstr_fd(token->data, STDERR);
        ft_putstr_fd(": No such file or directory\n", STDERR);
        mini->ret = 1;
        mini->no_exec = 1;
        return ;
    }
    dup2(mini->fdout, STDOUT);
}

void    input(t_shell *mini, t_minishell *token)
{
    ft_close(mini->fdin);
    mini->fdin = open(token->data, O_RDONLY, S_IRWXU);
    if (mini->fdin == -1)
    {
        ft_putstr_fd("minishell: ",STDERR);
        ft_putstr_fd(token->data, STDERR);
        ft_putstr_fd(": No such file or directory\n", STDERR);
        mini->ret = 1;
        mini->no_exec = 1;
        return ;
    }
    dup2(mini->fdin, STDIN);
}

int minipipe(t_shell *mini)
{
    pid_t pid;
    int    i;
    int pipefd[2];
    char    str[100000];
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
	{
		close(pipefd[0]);
       // printf("%d\n", pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
		//mini->pipin = pipefd[0];
        read(pipefd[0], str, 1000);
        printf("======%s ==========\n", str);
		mini->pid = -1;
		mini->parent = 0;
		mini->no_exec = 0;
		return (pid);
	}
    else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
		//mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (pid);
	}
}

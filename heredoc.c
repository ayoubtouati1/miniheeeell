/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:54:17 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/14 22:05:37 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static
int	create_temporary_file(void)
{
	return (open("../.tmp_hdocu", O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

void	restores_stdin_and_closes(void)
{
	int		tmp_fd;

	tmp_fd = open("../.tmp_hdocu", O_RDONLY);
	unlink(".tmp_hdocu");
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}

void	interrupt_here_document(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(errno);
}

static void	get_and_write_input(t_shell *head, t_minishell *token, int tmp_fd)
{
	char	*input;

	signal(SIGINT, interrupt_here_document);
	while (head)
	{
		input = readline("> ");
		if (!input)
			exit(errno);
		if (ft_strncmp(input, token->data, ft_strlen(input) + 1))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

void	heredoc_func(t_shell *head, t_minishell *token)
{
	int		tmp_fd;
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	head->here_in = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		get_and_write_input(head, token ,tmp_fd);
		close(tmp_fd);
	}
	waitpid(pid, &status, 0);
	restores_stdin_and_closes();
	close(tmp_fd);
}

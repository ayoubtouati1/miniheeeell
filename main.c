/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:11:31 by atouati           #+#    #+#             */
/*   Updated: 2022/11/16 14:56:24 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

int	init_env(t_shell *mini, char **env_array)
{
	t_list_env	*env;
	t_list_env	*new;
	int		i;

	if (!(env = malloc(sizeof(t_list_env))))
		return (1);
		
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_list_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int	init_export_env(t_shell *mini, char **env_array)
{
	t_list_env	*env;
	t_list_env	*new;
	int		i;

	if (!(env = malloc(sizeof(t_list_env))))
		return (1);
		
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->export_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_list_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

t_minishell	*fill_token(t_token *ptr, char **env)
{
	t_minishell	*head;
	t_minishell	*tokens;
	int			i;

	tokens = sep_split(ptr->parse_line, ' ', env);
	i = 0;
	head = tokens;
	while (tokens != NULL)
	{
		//tokens[i]->data = handling_quotes(tokens[i]->data, -1, ' ');
		tokens->quotes = check_quot(tokens->data);
		//tokens[i]->data = check_expand(tokens[i]->data, env, tokens[i]);
		tokens->data = remove_quotes(tokens->data);
		tokens = tokens->next;
	}
	tokens = head;
	while (tokens)
		{
			if (tokens->type == INPUT_FILE)
				printf("[INPUT_FILE] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == PIPE)
				printf("[PIPE] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == CMD_T_P)
				printf("[CMD_T_P] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == OUTPUT_FILE)
				printf("[OUTPUT_FILE] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == HEREDOC)
				printf("[HERDOC] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == CMD)
				printf("[CMD] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == APPEND)
				printf("[APPEND] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == INPUT_OP)
				printf("[INPUT_OP] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == OUTPUT_OP)
				printf("[OUTPUT_OP] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == ARG)
				printf("[ARG] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == APPEND_OP)
				printf("[APPEND_OP] %s [%d]\n", tokens->data, tokens->quotes);
			else if (tokens->type == HEREDOC_OP)
				printf("[HEREDOC_OP] %s [%d]\n", tokens->data, tokens->quotes);
			tokens = tokens->next;
		}
		tokens = head;
	return (tokens);
}

int	skeep_space(char *parse_line)
{
	int	i;

	i = 0;
	while (parse_line[i] && parse_line[i] == ' ')
		i++;
	return (i);
}

int	check_error_op(char *parse_line)
{
	int	i;

	i = 0;
	while (parse_line[i])
	{
		if (parse_line[i] == '|' && parse_line[i + skeep_space(parse_line + i + 1) + 1] == '\0')
			return (0);
		if (parse_line[i] == '|' && parse_line[i + skeep_space(parse_line + i + 1) + 1] == '|')
		{
			printf("********** %c *********\n", parse_line[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	signals(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

t_minishell	*parser(t_token *ptr, char **env)
{
	t_minishell	*tokens;
	int			i;

	i = 0;
	ptr->parse_line = handling_spaces(ptr->parse_line);
	if (!ptr->parse_line)
	{
		printf("quot error\n");
		ptr->if_true = 1;
		return (0);
	}
	i = skeep_space(ptr->parse_line);
	if (ptr->parse_line[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		ptr->if_true = 1;
		return (0);
	}
	if (!check_error_op(ptr->parse_line))
	{
		printf("......minishell: syntax error near unexpected token `|'\n");
		ptr->if_true = 1;
		return (0);
	}
	ptr->parse_line = handling_quotes(ptr->parse_line, ' ', -1);
	tokens = fill_token(ptr, env);
	return (tokens);
}

int	main(int ac, char **av, char **env)
{
	t_token     ptr;
    t_shell t_mini;
	char *prt;
    t_mini.in = dup(STDIN);
	t_mini.out = dup(STDOUT);
    t_mini.ret = 0;
    t_mini.no_exec = 0;
    t_mini.exit = 0;
	reset_fds(&t_mini);
    init_env(&t_mini,env);
    init_export_env(&t_mini ,env);
    (void)ac;
    (void)av;
	while (1)
	{
		prt = ms_getprompt();
		ptr.if_true = 0;
		init_sig();
       	signals();
		ptr.parse_line = readline(prt);
		if (!ptr.parse_line)
			exit (0);
		if (!ft_memcmp(ptr.parse_line, "\n"))
		{
			free(ptr.parse_line);
			continue ;
		}
		add_history(ptr.parse_line);
		t_mini.start = parser(&ptr, env);
		if (ptr.if_true == 1)
			continue ;
		t_minishell *head;
		while (t_mini.start)
		{
			head = t_mini.start->next;
			free(t_mini.start->data);
			free(t_mini.start);
			t_mini.start = head;
		}
		free(t_mini.start);
		free(prt);
		system("leaks minishell");
	}
}

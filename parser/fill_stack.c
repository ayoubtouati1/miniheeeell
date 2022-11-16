/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:46:24 by atouati           #+#    #+#             */
/*   Updated: 2022/11/16 14:47:59 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_num(t_minishell **top, t_minishell *tmp)
{
	t_minishell	*temp;

	if (*top == NULL)
		*top = tmp;
	else
	{
		temp = *top;
		while (temp->next)
			temp = temp->next;
		temp->next = tmp;
	}
}

int	get_type(int i, char **str)
{
	if (i == 0)
		return (ARG);
	else if (str[i][0] == '|' && str[i][1] == '\0')
		return (PIPE);
	else if (str[i - 1][0] == '<' && str[i - 1][1] == '\0')
		return (INPUT_FILE);
	else if (str[i - 1][0] == '>' && str[i - 1][1] == '\0')
		return (OUTPUT_FILE);
	else if (str[i - 1][0] == '>' && str[i - 1][1] == '>')
		return (APPEND);
	else if (str[i - 1][0] == '<' && str[i - 1][1] == '<')
		return (HEREDOC);
	else
		return (ARG);
}

int	check_error(char	**str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if ((str[i][0] == '<' || str[i][0] == '>')
			&& (str[i + 1][0] == '<' || str[i + 1][0] == '>'))
				return (0);
		if (str[i][0] == '<' && str[i][1] == '>')
			return (0);
		if (str[i][0] == '>' && str[i][1] == '<')
			return (0);
		i++;
	}
	if (str[i + 1] == NULL && (str[i][0] == '<' || str[i][0] == '>'))
			return (0);
	return (1);
	
}

int	check_error_2(char *str)
{
	if (str[0] == '<' && str[1] == '<')
	{
		if (!ft_memcmp(str, "<<"))
			return (0);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		if (!ft_memcmp(str, ">>"))
			return (0);
	}
	else if (str[0] == '<' && str[1] == '\0')
	{
		return (0);
	}
	else if (str[0] == '>' && str[1] == '\0')
	{
		return (0);
	}
	else
		return (0);
	return (1);
	
}

t_minishell	*fill_stack(t_minishell *stack_a, char **str, char **env)
{
		t_minishell	*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	if (!check_error(str))
	{
		printf("..........minishell: syntax error near unexpected token\n");
		return (NULL);
	}
	while (str[i])
	{
		if (check_error_2(str[i]))
		{
			printf("minishell: syntax error near unexpected token\n");
			return (NULL);
		}
		if (str[i][0] != '<' && str[i][0] != '>')
		{
			tmp = malloc(sizeof(t_minishell));
			//printf("------ %s\n", str[i]);
			str[i] = handling_quotes(str[i], -1, ' ');
			str[i] = check_expand(str[i], env, get_type(i, str));
			tmp->data = ft_strdup(str[i]);
			tmp->type = get_type(i, str);
			tmp->next = NULL;
			add_num(&stack_a, tmp);
		}
		//else
		//	free(str[i]);
		i++;
	}
	return (stack_a);
}

void	open_and_define(t_minishell **tokens)
{
	int			i;
	t_minishell	*head;

	i = 0;
	while (tokens[i] != NULL)
	{
		head = tokens[i];
		while (tokens[i] != NULL)
		{
			tokens[i]->file.fd = -4;
			if (tokens[i]->type == OUTPUT_FILE)
			{
				tokens[i]->file.type = OUTPUT_FILE;
				tokens[i]->file.fd = open(tokens[i]->data, O_CREAT | O_TRUNC, 0600);
			}
			else if (tokens[i]->type == INPUT_FILE)
			{
				tokens[i]->file.type = INPUT_FILE;
				tokens[i]->file.fd = open(tokens[i]->data, O_RDONLY);
			}
			else if (tokens[i]->type == APPEND)
			{
				tokens[i]->file.type = APPEND;
				tokens[i]->file.fd = open(tokens[i]->data, O_CREAT | O_APPEND, 0600);
			}
			if (tokens[i]->file.fd < 0 && tokens[i]->file.fd != -4)
			{
				printf("minishell: %s: No such file or directory\n", tokens[i]->data);
				exit (0);
			}
			tokens[i] = tokens[i]->next;
		}
		tokens[i] = head;
		i++;
	}
	
}

int	check_pip(t_minishell *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->data, "|"))
			return (0);
		tokens = tokens->next;
	}
	return (1);
	
}

t_minishell	*skip_tokens(t_minishell *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->data, "|"))
			return (tokens->next);
		tokens = tokens->next;
	}
	return (NULL);
	
}


void	define_cmd(t_minishell *tokens)
{
	int			i;
	t_minishell	*head;

	i = 0;
	while (tokens)
	{		
		if (tokens->type == ARG && !check_pip(tokens))
		{
			tokens->type = CMD_T_P;
			break ;
		}
		else if (tokens->type == ARG)
		{
			tokens->type = CMD;
			break ;
		}
		tokens = tokens->next;
	}
	if (!check_pip(tokens))
		define_cmd(skip_tokens(tokens));
}

t_minishell	*sep_split(char *str, char sep, char **env)
{
	t_minishell	*tokens;
	t_minishell	*head;
	int			i;
	char		**chr;

	//tokens = malloc(sizeof(t_minishell));
	tokens = NULL;
	chr = ft_split(str, ' ');
	tokens = fill_stack(tokens, chr, env);
	ft_free(chr);
	define_cmd(tokens);
	//open_and_define(tokens);
	free(str);
	return (tokens);
}
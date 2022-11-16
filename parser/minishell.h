/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:30:51 by atouati           #+#    #+#             */
/*   Updated: 2022/11/16 02:00:48 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

////////////for the execution/////////

enum e_type
{
	CMD,
	ARG,
	INPUT_FILE,
	OUTPUT_FILE,
	HEREDOC,
	HEREDOC_OP,
	APPEND,
	INPUT_OP,
	OUTPUT_OP,
	APPEND_OP,
	D_QUOTES,
	S_QUOTES,
	NO_QUOTES,
	PIPE,
	CMD_T_P
};

typedef struct s_file
{
	int		fd;
	int		type;
} t_file;

typedef struct s_minishell
{
	char				*data;
	int					type;
	t_file				file;
	int					quotes;
	struct s_minishell	*next;
}	t_minishell;

////////////end of the execution/////////


////////////for the parsing/////////////

typedef struct s_token
{
	char			*parse_line;
	char			**pip_split;
	int				quotes;
	char			a;
	char			b;
	int				i;
	int				j;
	int				n;
	int				s_quot;
	int				d_quot;
	int				if_true;
}	t_token;

char		*handling_quotes(char	*str, char a, char b);
char		*ft_strcpy(char *dst, const char *str);
//int			ft_strchr(const char *s, int c);
int			ft_strnstr(const char *haystack, const char *needle);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
int			ft_memcmp(const void *s1, const void *s2);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isdigit(int c);
char		*copy_no_dollar(char *str,char *tmp, t_token *ptr);
int			quot_cont(char *str, int n, char sep);
int			check_dollar(char *str, int i);
int			cont_dollar(char *str, int i);
char		*copy_no_expand(char *str, char *tmp, t_token *ptr);
char		*digit_expand(char *str, char *tmp, t_token *ptr, char **env);
char		*dollar_expand(char *str, char *tmp, t_token *ptr, char ** env);
char		*expand(char *str, int i, char **env);
char		**alloc_des(char **env);
void		ft_free(char **dst);
char		*count_space_and_alloc(char *str, char *dest, int i);
int			add_after_opirations(char **str, char	**dest, int *i, int *j);
int			add_inside_quot(char **str, char **dest, int *i, int *j);
void		add_befor_opirations(char **str, char **dest, int *i, int *j);
char		*handling_spaces(char *str);
t_minishell	*fill_stack(t_minishell *stack_a, char **str, char **env);
char		*remove_quotes(char *str);
int			check_quot(char *str);
int			cont_quot(char *str);
char		*comper_to_env(char *dest, char **env);
char		*check_expand(char *str, char **env, int type);
char		**replace_in_quotes(char **str, char a, char b);
void		define_cmd(t_minishell *tokens);
t_minishell	*sep_split(char *str, char sep, char **env);
char		*get_next_line(int fd);
char		*ft_strrjoin(char const *s1, char const *s2);
int			ft_strcmp(char *s1, char *s2);

////////////for the parsing//////////////

#endif
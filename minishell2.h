#if !defined(MINISHELL2_H)
#define MINISHELL2_H
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <curses.h>
#include <signal.h>
#include "parser/minishell.h"
#include "dirent.h"
#include <limits.h>
#include "libft/libft.h"
#include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFF_SIZE 4000

typedef struct		s_list
{
	void			*content;
	long			content_size;
	struct s_list	*next;
}					t_list;

typedef struct s_sig
{
	int	sigint;
	int sigquit;
	pid_t pid;
	int exit_status;
}t_sig;

typedef struct s_list_env
{
    char *value;
    struct s_list_env *next;

}t_list_env;

typedef struct s_shell
{
	t_list_env		*export_env;
    t_list_env		*env;
	t_minishell		*start;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				here_in;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
	int				if_true;
}t_shell;

void		replace_env(t_list_env **list, char *name, char *value);
char		*find_env(t_shell **list, char *name);
void		add_env(t_list_env **lst, t_list_env *new);
t_list_env 	*new_env_malloc(char *name, char *value);
void		ft_list_sort_env(t_list_env **lst);
void    	del_at_env(t_list_env **lst, char *str);
int			ft_cd(char **args, t_list_env *env);
int    		ft_echo(char **argv);
int			run_env(t_list_env *env);
void    	run_exit(char **av, t_shell *t_mini);
int  		run_export(char **args, t_list_env *env, t_list_env *export_env);
int			ft_pwd(void);
int			run_unset(char **a, t_shell *mini);
void 		free_tab(char **tabs);
void		sig_handler(int sig);
void		print_prompt(int clear);
int			run_builtins(char **argv, t_shell *mini);
void 		free_tab(char **tabs);
void 		init_sig(void);
t_minishell *next_sep(t_minishell *token, int skip);
t_minishell *prev_sep(t_minishell *token, int skip);
t_minishell *next(t_minishell *token, int skip);
void		print_sorted_env(t_list_env *env);
int			is_valid_env(char *env);
void		exec_cmd(t_shell *mini, t_minishell *token);
int			run_bin(char **av, t_list_env *env, t_shell *mini);
char		*env_to_str(t_list_env *lst);
void		redir(t_shell *mini, t_minishell *token, int type);
void		input(t_shell *mini, t_minishell *token);
int			minipipe(t_shell *mini);
void		input(t_shell *mini, t_minishell *token);
int			is_in_env(t_list_env *env, char *args);
int			env_add(const char *value, t_list_env *env);
void 		execution(t_shell *ptr);
void		reset_std(t_shell *mini);
void		close_fds(t_shell *mini);
void		reset_fds(t_shell *mini);
void		ft_close(int fd);
char		*ms_getprompt();
void		heredoc_func(t_shell *head, t_minishell *token);
#endif  

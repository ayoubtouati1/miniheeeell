/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 04:30:44 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/15 23:44:27 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

int	error_print(char *path)
{
	DIR *folder;
	int	fd;
	int ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell :" ,2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putstr_fd(": command not found\n", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory\n", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory\n", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	close(fd);
	return 126;		
}

int execute_cmd(char *path, char **av, t_list_env *env, t_shell *mini)
{
	int	ret;
	t_sig sig;
	char *ptr;
	char **env_arr;
	ret = 0;
	//if (mini->if_true == 1)
	//{
	//	sig.pid = minipipe(mini);
	//	if (sig.pid == 0)
	//	{
	//		ptr = env_to_str(env);
	//		env_arr = ft_split(ptr, '\n');
	//		free(ptr);
	//		if (ft_strchr(path, '/') != NULL)
	//			execve(path, av, env_arr);
	//		ret = error_print(path);
	//		free_tab(env_arr);
	//		// free_token(mini->start);
	//		exit(ret);	
	//	}	
	//}
	//else
	//{
		sig.pid = fork();
		if (sig.pid == 0)
		{
			ptr = env_to_str(env);
			env_arr = ft_split(ptr, '\n');
			free(ptr);
			if (ft_strchr(path, '/') != NULL)
				execve(path, av, env_arr);
			ret = error_print(path);
			free_tab(env_arr);
			// free_token(mini->start);
			exit(ret);	
		}
		else
			waitpid(sig.pid, &ret, 0);
	//}
	return(ret);	
}

char	*join_path(char *s1, char *s2)
{
	char *tmp;
	char *path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path); 
}

char	*check_dir(char *bin, char *command)
{
	DIR *folder;
	struct dirent *entry;
	char *path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((entry = readdir(folder)))
	{
		if (ft_strcmp(entry->d_name, command) == 0)
			path = join_path(bin, entry->d_name);
	}
	closedir(folder);
	return (path);
}

int     run_bin(char **av, t_list_env *env, t_shell *mini)
{
	int i;
	char **bin;
	char *path;
	int ret;

	ret = 127;
	i = 0;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (execute_cmd(av[0], av, env, mini));
	bin = ft_split(env->value, ':');
	if (!av[0] && !bin[0])
		return (1);
	i = 1;
	path = check_dir(bin[0] + 5, av[0]);
	while (av[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], av[0]);
	if (path != NULL)
		ret = execute_cmd(path, av, env, mini);
	else
		ret = execute_cmd(av[0], av, env, mini);
	free_tab(bin);
	free(path);
	return (ret);	
}
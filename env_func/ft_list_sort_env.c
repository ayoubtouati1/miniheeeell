/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 06:25:01 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/11 19:58:35 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell2.h"
#include "../libft/libft.h"

int			str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void		sort_env(char **tabs, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tabs && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tabs[i], tabs[i + 1]) > 0)
			{
				tmp = tabs[i];
				tabs[i] = tabs[i + 1];
				tabs[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void		print_sorted_env(t_list_env *env)
{
	int		i;
	char	**tabs;
	char	*str_env;

	str_env = env_to_str(env);
	tabs = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tabs, str_env_len(tabs));
	i = 0;
	while (tabs[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(tabs[i], STDOUT);
		i++;
	}
	free_tab(tabs);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 02:55:29 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/14 21:34:50 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "libft/libft.h"

void sig_handler(int sig)
{
    sig++;
	write(1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void init_sig(void)
{
    t_sig sig_m;
    sig_m.sigint = 0;
    sig_m.pid = 0;
    sig_m.exit_status = 0;
    sig_m.sigquit = 0;
}
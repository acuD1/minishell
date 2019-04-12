/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:28 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 10:42:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <time.h>


void	logger(t_list *env, char **environ)
{
	int			ttyfd;
	time_t		rawtime;
	struct tm	*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if ((ttyfd = open(LOG_TTY, O_WRONLY)) == -1)
		ft_mprintf(1, "open /dev/tty");
	ft_mprintf(ttyfd, "\n>\n%sLOGGING...%s\n", C_B, C_X);
	print_env(environ, ttyfd);
	print_env_db(env, ttyfd);
	ft_mprintf(ttyfd, "LOGGER FOR MINISHELL : %s", asctime(timeinfo));
}

void	print_env(char **environ, int ttyfd)
{
	int		i;

	i = 0;
	ft_putendl_fd("DEBUF FOR ENV ->", ttyfd);
	if (!(environ[i]))
		ft_mprintf(ttyfd, "%sEMPTY%s\n", C_R, C_X);
	while (environ[i])
	{
		ft_mprintf(ttyfd ,"%sENV[%s%d%s]%s%s\n",
			C_Y, C_G, i, C_Y, C_X, environ[i]);
		i++;
	}
}

void	print_env_db(t_list *env, int ttyfd)
{
	int		i;

	i = 0;
	ft_putendl_fd("DEBUF FOR ENV_DB ->", ttyfd);
	if (!(env))
		ft_mprintf(ttyfd, "%sEMPTY%s\n", C_R, C_X);
	while (env)
	{
		ft_mprintf(ttyfd, "%sENV_DB[%s%d%s]\n%sS = |%s|\n%sV = |%s|%s\n",
			C_Y, C_G, i, C_Y, C_M, ENV_DB->symbol, C_C, ENV_DB->value, C_X);
		env = env->next;
		i++;
	}
}

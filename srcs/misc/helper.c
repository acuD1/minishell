/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:28 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/04 14:45:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <time.h>

static void	print_env_db(t_list *env, int fd)
{
	int		i;

	i = 0;
	ft_putendl_fd("DEBUG FOR ENV_DB ->", fd);
	if (!(env))
		ft_mprintf(fd, "%sEMPTY%s\n", C_R, C_X);
	while (env)
	{
		ft_mprintf(fd, "%sENV_DB[%s%d%s]\n%sS = |%s|\n%sV = |%s|%s\n",
			C_Y, C_G, i, C_Y, C_M, ENV_DB->symbol, C_C, ENV_DB->value, C_X);
		env = env->next;
		i++;
	}
}

int			open_logger(t_core *shell)
{
	int		fd;

	if ((fd = open(shell->logger,
		O_WRONLY | O_APPEND | O_CREAT | O_NOFOLLOW, 0600)) == -1)
	{
		shell->flag.stop = 1;
		ft_mprintf(STDERR_FILENO, "%sFailed open %s for debug !%s\n",
			C_R, shell->logger, C_X);
		return (0);
	}
	return (fd);
}

void		helper(t_core *shell, char *line, char **tokens)
{
	struct tm	*timeinfo;
	time_t		rawtime;
	int			fd;
	int			i;

	if (!shell->opt.d || !(fd = open_logger(shell)))
		return ;
	i = 0;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	ft_mprintf(fd, "\n\n>\n%sLOGGING...%s\n", C_B, C_X);
	print_env_db(shell->env, fd);
	ft_mprintf(fd, "\nline = |%s|\n\n", line);
	while (tokens && tokens[i])
	{
		ft_mprintf(fd, "token[%d] = |%s|\n", i, tokens[i]);
		i++;
	}
	ft_mprintf(fd, "\nCHILD PID = %d\n\nLOGGER FOR MINISHELL (%d) V.%d_%d : %s",
		shell->child_pid, shell->minishell_pid,
		shell->build.version, shell->build.patch, asctime(timeinfo));
}

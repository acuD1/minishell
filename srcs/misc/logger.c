/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:28 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 15:34:31 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

static void	print_env_db(t_core *shell)
{
	t_list	*env;
	size_t	i;

	i = 0;
	env = shell->env;
	ft_putendl_fd("DEBUG FOR ENV_DB ->", shell->logger_fd);
	if (!(env))
		ft_mprintf(shell->logger_fd, "%sEMPTY%s\n", C_R, C_X);
	while (env)
	{
		ft_mprintf(shell->logger_fd,
			"%sENV_DB[%s%d%s]\n%sS = |%s|\n%sV = |%s|%s\n",
			C_Y, C_G, i, C_Y, C_M, ((t_db*)(env->content))->symbol, C_C,
			((t_db*)(env->content))->value, C_X);
		env = env->next;
		i++;
	}
}

static void	print_var_db(t_core *shell)
{
	t_list	*var;
	size_t	i;

	i = 0;
	var = shell->var;
	ft_putendl_fd("DEBUG FOR VAR_DB ->", shell->logger_fd);
	if (!(var))
		ft_mprintf(shell->logger_fd, "%sEMPTY%s\n", C_R, C_X);
	while (var)
	{
		ft_mprintf(shell->logger_fd,
			"%sVAR_DB[%s%d%s]\n%sS = |%s|\n%sV = |%s|%s\n",
			C_Y, C_G, i, C_Y, C_M, ((t_db*)(var->content))->symbol, C_C,
			((t_db*)(var->content))->value, C_X);
		var = var->next;
		i++;
	}
}

void		open_logger_fd(t_core *shell, char *av)
{
	char	*tmp_fd;

	if (av == NULL)
		tmp_fd = LOGGER_TTY;
	else
		tmp_fd = av;
	if ((shell->logger_fd = open(tmp_fd,
		O_WRONLY | O_APPEND | O_CREAT | O_NOFOLLOW, 0600)) == -1)
	{
		ft_mprintf(STDERR_FILENO, "%sFailed open %s for debug !%s\n",
			C_R, LOGGER_TTY, C_X);
		return ;
	}
}

void		logger(t_core *shell, char *line, char **tokens)
{
	struct tm	*timeinfo;
	time_t		rawtime;
	size_t		i;

	if (shell->opt ^ OPT_DEBG || shell->logger_fd == -1)
		return ;
	i = 0;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	ft_mprintf(shell->logger_fd, "\n\n>\n%sLOGGING...%s\n", C_B, C_X);
	print_env_db(shell);
	ft_mprintf(shell->logger_fd, "\nline = |%s|\n\n", line);
	while (tokens && tokens[i])
	{
		ft_mprintf(shell->logger_fd, "token[%d] = |%s|\n", i, tokens[i]);
		i++;
	}
	print_var_db(shell);
	ft_mprintf(shell->logger_fd,
		"\nCHILD PID = %d\n\nLOGGER FOR MINISHELL (%d) V.%d_%d : %s",
		shell->child_pid, shell->minishell_pid,
		shell->build.version, shell->build.patch, asctime(timeinfo));
}

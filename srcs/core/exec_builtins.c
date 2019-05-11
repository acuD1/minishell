/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 18:28:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

static void	get_env_home(t_list *env)
{
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
			chdir(((t_db*)(env->content))->value);
		env = env->next;
	}
}

static void	cd_builtin(t_core *shell, char **tokens)
{
	DIR	*content;

	content = NULL;
	if (tokens[1] == NULL)
		get_env_home(shell->env);
	else
	{
		if (access(tokens[1], F_OK) == -1)
		{
			ft_mprintf(STDERR_FILENO,
				"minishell: cd: %s: No such file or directory\n", tokens[1]);
			return ;
		}
		if (!(content = opendir(tokens[1])))
		{
			ft_mprintf(STDERR_FILENO, "minishell: cd: %s: Permission denied\n",
				tokens[1]);
			return ;
		}
		chdir(tokens[1]);
		closedir(content);
	}
}

static void	echo_builtin(char **tokens)
{
	size_t	i;
	uint8_t	no_newline;

	i = 1;
	no_newline = 0;
	if (ft_strequ(tokens[i], "-n"))
	{
		i = 2;
		no_newline = TRUE;
	}
	while (tokens[i])
	{
		ft_mprintf(STDOUT_FILENO, "%s", tokens[i]);
		i++;
		if (tokens[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (no_newline == FALSE)
		write(STDOUT_FILENO, "\n", 1);
}

int8_t		exec_builtins(t_core *shell, char **tokens)
{
	logger(shell, NULL, tokens);
	if (ft_strequ(tokens[0], "exit") == TRUE)
	{
		shell->exit = TRUE;
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "cd") == TRUE)
	{
		cd_builtin(shell, tokens);
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "echo") == TRUE)
	{
		echo_builtin(tokens);
		return (SUCCESS);
	}
	return (FAILURE);
}

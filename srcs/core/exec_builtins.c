/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/12 16:01:38 by arsciand         ###   ########.fr       */
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

void		set_tmp_env(t_core *shell, char *tokens)
{
	t_db	tmp_env_db;

	tmp_env_db = shell->db;
	ft_lstpushback(&shell->tmp_env,
		ft_lstnew(fetch_db(&tmp_env_db, tokens), sizeof(t_db)));
}

void	get_tmp_env(t_core *shell, char **tokens, size_t i)
{
	(void)shell;
	if (tokens[i + 1] == NULL || ft_strchr(tokens[i], '=') == FALSE)
		return ;
}
size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	env_builtin(t_core *shell, char **tokens)
{
	t_list	*env;
	char	**tmp;
	size_t	i;

	env = shell->env;
	tmp = NULL;
	i = ft_tablen(tokens);
	if (tokens[1] && tokens[1][0] == '-' && ft_strequ(tokens[1], "-i") == FALSE)
	{
		ft_mprintf(STDERR_FILENO, "env: illegal option -- %c\n", tokens[1][1]);
		ft_putendl_fd("usage: env [-i] [name=value ...] [utility [argument ...]]",
			STDERR_FILENO);
		return ;
	}
	if (ft_strequ(tokens[1], "-i") == TRUE && tokens[2] == NULL)
		return ;
	if (ft_strequ(tokens[1], "-i") == TRUE && tokens[2])
	{
		logger(shell, NULL, tokens);
		/*while (tokens[i])
		{
			if (ft_strchr(tokens[i], '='))
			{
				if (tokens[i + 1] == NULL)
				{
					ft_mprintf(STDOUT_FILENO, "%s\n", tokens[i]);
					return ;
				}
				tmp = ft_strdup(tokens[i + 1]);
				printf("tmp = %s\n", tmp);
				set_tmp_env(shell, tokens[i]);
				ft_strdel(&tokens[i]);
				tokens[i] = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
			i++;
		}*/
		logger(shell, NULL, tokens);
		shell->default_env = 1;
		exec_process(shell, tokens);
		return ;
	}
	//////////////
	if (tokens[1])
	{
		if (!(tmp = ft_memalloc(sizeof(tmp) * 2)))
			return ;
		tmp[0] = ft_strdup(tokens[i - 1]);
		tmp[1] = NULL;
		exec_process(shell, tmp);
		ft_free_tab(&tmp);
		return ;
	}
	//////////////
	while (env)
	{
		ft_mprintf(STDOUT_FILENO, "%s=%s\n",
			((t_db*)(env->content))->symbol, ((t_db*)(env->content))->value);
		env = env->next;
	}
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
	if (ft_strequ(tokens[0], "env") == TRUE)
	{
		shell->env_mode = 1;
		env_builtin(shell, tokens);
		//logger(shell, NULL, tokens);
		return (SUCCESS);
	}
	return (FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:52:12 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/30 13:25:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <dirent.h>
#include <unistd.h>

static void cd_handler(char **tokens, uint8_t handler)
{
	if (handler & CD_ARG_ERROR)
		ft_mprintf(STDERR_FILENO, "minishell: cd: Too many arguments\n");
	if (handler & CD_DIR_ERROR)
		ft_mprintf(STDERR_FILENO,
			"minishell: cd: %s: No such file or directory\n", tokens[1]);
	if (handler & CD_PERM_ERROR)
		ft_mprintf(STDERR_FILENO, "minishell: cd: %s: Permission denied\n",
			tokens[1]);
}

static void	update_old_pwd(t_list *env)
{
	char	oldpwd[PATH_MAX];

	getcwd(oldpwd, sizeof(oldpwd));
	while(env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "OLDPWD") == TRUE)
		{
			ft_strdel(&((t_db*)(env->content))->value);
			((t_db*)(env->content))->value = ft_strdup(oldpwd);
		}
		env = env->next;
	}
}

static void	get_env_home(t_list *env)
{
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
		{
			update_old_pwd(env);
			chdir(((t_db*)(env->content))->value);
		}
		env = env->next;
	}
}

void		cd_builtin(t_core *shell, char **tokens)
{
	DIR	*content;

	content = NULL;
	if (tokens[2] != NULL)
		return (cd_handler(tokens, CD_ARG_ERROR));
	if (tokens[1] == NULL)
		get_env_home(shell->env);
	else
	{
		if (access(tokens[1], F_OK) == -1)
			return (cd_handler(tokens, CD_DIR_ERROR));
		if (!(content = opendir(tokens[1])))
			return (cd_handler(tokens, CD_PERM_ERROR));
		update_old_pwd(shell->env);
		chdir(tokens[1]);
		closedir(content);
	}
}

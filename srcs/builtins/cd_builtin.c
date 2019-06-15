/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:52:12 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/15 14:40:08 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <dirent.h>
#include <unistd.h>

static void	init_pwd(t_pwd *pwd, t_list *env)
{
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "PWD") == TRUE)
			ft_strcpy(pwd->current, ((t_db*)(env->content))->value);
		if (ft_strequ(((t_db*)(env->content))->symbol, "OLDPWD") == TRUE)
			ft_strcpy(pwd->old, ((t_db*)(env->content))->value);
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
			ft_strcpy(pwd->home, ((t_db*)(env->content))->value);
		env = env->next;
	}
}

static void	update_env_pwd(t_core *shell, t_pwd *pwd)
{
	t_list		*env;

	env = shell->env;
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "PWD") == TRUE)
		{
			ft_strdel(&((t_db*)(env->content))->value);
			((t_db*)(env->content))->value = ft_strdup(pwd->current);
		}
		if (ft_strequ(((t_db*)(env->content))->symbol, "OLDPWD") == TRUE)
		{
			ft_strdel(&((t_db*)(env->content))->value);
			((t_db*)(env->content))->value = ft_strdup(pwd->old);
			pwd->env_oldpwd = TRUE;
		}
		env = env->next;
	}
	if (pwd->env_oldpwd == FALSE)
	{
		shell->db.symbol = ft_strdup("OLDPWD");
		shell->db.value = ft_strdup(pwd->old);
		ft_lstpushback(&shell->env, ft_lstnew(&shell->db, sizeof(t_db)));
	}
}

static void	do_home_cd(t_core *shell, t_pwd *pwd)
{
	if (ft_strlen(pwd->home) < 1)
		return (cd_handler(NULL, CD_HOME_NULL));
	chdir(pwd->home);
	ft_strcpy(pwd->old, pwd->current);
	ft_strcpy(pwd->current, pwd->home);
	update_env_pwd(shell, pwd);
}

static void	do_hyphen_cd(t_core *shell, t_pwd *pwd)
{
	char	tmp[PATH_MAX];

	if (ft_strlen(pwd->old) < 1)
		return (cd_handler(NULL, CD_OLDPWD_NULL));
	chdir(pwd->old);
	ft_strcpy(tmp, pwd->current);
	ft_strcpy(pwd->current, pwd->old);
	ft_strcpy(pwd->old, tmp);
	ft_mprintf(STDOUT_FILENO, "%s\n", pwd->current);
	update_env_pwd(shell, pwd);
}

void		cd_builtin(t_core *shell, char **tokens)
{
	DIR		*content;
	t_pwd	pwd;
	char	tmp[PATH_MAX];

	content = NULL;
	pwd = shell->pwd;
	init_pwd(&pwd, shell->env);
	if (tokens[1] == NULL)
		return (do_home_cd(shell, &pwd));
	if (tokens[2] != NULL)
		return (cd_handler(tokens, CD_ARG_ERROR));
	if (ft_strequ(tokens[1], "-"))
		return (do_hyphen_cd(shell, &pwd));
	if (ft_strchr(tokens[1], '-') && tokens[1][1])
		return (cd_handler(tokens, CD_USAGE));
	if (access(tokens[1], F_OK) == -1)
		return (cd_handler(tokens, CD_DIR_ERROR));
	if (!(content = opendir(tokens[1])))
		return (cd_handler(tokens, CD_PERM_ERROR));
	chdir(tokens[1]);
	closedir(content);
	ft_strcpy(pwd.old, pwd.current);
	ft_strcpy(tmp, tokens[1]);
	ft_strcpy(pwd.current, getcwd(tmp, sizeof(tmp)));
	update_env_pwd(shell, &pwd);
}

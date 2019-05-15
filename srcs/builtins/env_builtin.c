/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:55:44 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/15 17:58:57 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	set_tmp_env(t_core *shell, char **tokens)
{
	t_db	tmp_env_db;
	size_t	i;

	i = 1;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '='))
		{
			ft_lstpushback(&shell->tmp_env,
				ft_lstnew(fetch_db(&tmp_env_db, tokens[i]), sizeof(t_db)));
		}
		i++;
	}
}

char	**set_tmp_tokens(char **tokens)
{
	char	**tmp_tokens;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(tmp_tokens = ft_memalloc(sizeof(tmp_tokens) * (ft_tablen(tokens) + 1))))
		return (NULL);
	while (tokens && tokens[i])
	{
		if (ft_strequ(tokens[i], "env"))
			i++;
		if (ft_strequ(tokens[i], "-i") == TRUE)
			i++;
		if (ft_strchr(tokens[i], '='))
			i++;
		tmp_tokens[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	tmp_tokens[j] = NULL;
	return (tmp_tokens);
}

void	env_builtin(t_core *shell, char **tokens)
{
	t_list	*env;
	char	**tmp_tokens;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	tmp_tokens = NULL;
	env = shell->env;
	if (tokens[1] && tokens[1][0] == '-' && ft_strequ(tokens[1], "-i") == FALSE)
	{
		ft_mprintf(STDERR_FILENO, "env: illegal option -- %c\n", tokens[1][1]);
		ft_putendl_fd("usage: env [-i] [name=value ...] [utility [argument ...]]",
			STDERR_FILENO);
		return ;
	}
	if (ft_strequ(tokens[1], "-i") == TRUE && tokens[2] == NULL)
		return ;
	if (tokens[1] == NULL)
	{
		while (env)
		{
			ft_mprintf(STDOUT_FILENO, "%s=%s\n",
				((t_db*)(env->content))->symbol, ((t_db*)(env->content))->value);
			env = env->next;
		}
		return ;
	}
	if (ft_strequ(tokens[1], "-i"))
		set_env(shell, NULL);
	else
		set_env(shell, shell->environ);
	set_tmp_env(shell, tokens);
	logger(shell, NULL, tokens);
	if ((tmp_tokens = set_tmp_tokens(tokens)) == NULL)
	{
		printf("Ops\n");
		ft_free_tab(&tmp_tokens);
		return ;
	}
	exec_process(shell, shell->tmp_env, tmp_tokens);
	ft_free_tab(&tmp_tokens);
}

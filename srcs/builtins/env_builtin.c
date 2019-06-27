/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:55:44 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 17:16:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	set_tmp_env(t_core *shell, char **tokens)
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

static void	get_tmp_tokens(char **tokens, char **tmp_tokens, size_t i)
{
	size_t	j;

	j = 0;
	while (tokens && tokens[i])
	{
		tmp_tokens[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	tmp_tokens[j] = NULL;
}

static char	**set_tmp_tokens(char **tokens)
{
	char	**tmp_tokens;
	size_t	i;

	i = 0;
	if (!(tmp_tokens = ft_memalloc(sizeof(tmp_tokens)
			* (ft_tablen(tokens) + 1))))
		return (NULL);
	while (tokens && tokens[i])
	{
		if (tokens_parser_checker(tokens[i]) == TRUE)
			i++;
		else
			break ;
	}
	if (!(tokens[i]))
	{
		free(tmp_tokens);
		return (NULL);
	}
	get_tmp_tokens(tokens, tmp_tokens, i);
	return (tmp_tokens);
}

void		env_builtin(t_core *shell, char **tokens)
{
	char	**tmp_tokens;

	tmp_tokens = NULL;
	if (tokens[1] && tokens[1][0] == '-' && ft_strequ(tokens[1], "-i") == FALSE)
		return (env_builtin_usage(tokens));
	if (ft_strequ(tokens[1], "-i") == TRUE && tokens[2] == NULL)
		return ;
	if (tokens[1] == NULL)
		return (env_builtin_printer(shell, tokens));
	if (ft_strequ(tokens[1], "-i"))
		set_env(shell, NULL);
	else
		set_env(shell, shell->environ);
	set_tmp_env(shell, tokens);
	tmp_tokens = set_tmp_tokens(tokens);
	if (tmp_tokens == NULL)
	{
		ft_free_tab(&tmp_tokens);
		return (env_builtin_printer(shell, tokens));
	}
	exec_process(shell, shell->tmp_env, tmp_tokens);
	ft_free_tab(&tmp_tokens);
}

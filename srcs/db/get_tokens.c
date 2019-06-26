/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 09:46:42 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/26 17:24:08 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

static void		tilde_converter(t_core *shell, char **tokens)
{
	t_list	*env;
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	env = shell->env;
	while (tokens[i])
	{
		if (ft_strequ(tokens[0], "~") == FALSE && tokens[i][0] == '~')
		{
			path = ft_strsub(tokens[i], 1, ft_strlen(tokens[i]));
			ft_strdel(&tokens[i]);
			while (env)
			{
				if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
					tokens[i] = ft_strjoinf(((t_db*)(env->content))->value,
									path, FREE_2);
				env = env->next;
			}
		}
		i++;
	}
}

int8_t	shift_exp_tokens(t_list *env, t_list *var, char *tokens, char *tmp)
{
	while (var)
	{
		if (ft_strequ(((t_db*)(var->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tmp);
			ft_strdel(&tokens);
			tokens = ft_strdup(((t_db*)(var->content))->value);
			return (SUCCESS);
		}
		var = var->next;
	}
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tmp);
			ft_strdel(&tokens);
			tokens = ft_strdup(((t_db*)(env->content))->value);
			return (SUCCESS);
		}
		env = env->next;
	}
	ft_strdel(&tmp);
	return (FAILURE);

}

static int8_t	exp_shifter(t_core *shell, char *tokens)
{
	t_list	*env;
	t_list	*var;
	char	*tmp;

	env = shell->env;
	var = shell->var;
	tmp = ft_strsub(tokens, 1, ft_strlen(tokens));
	return (shift_exp_tokens(env, var, tokens, tmp));
}

static void		exp_converter(t_core *shell, char **tokens)
{
	size_t	i;

	i = 1;
	while (tokens[i])
	{
		if (tokens[i][0] == '$' && exp_shifter(shell, tokens[i]) != SUCCESS)
			ft_bzero(tokens[i], ft_strlen(tokens[i]));
		i++;
	}
}

static char		**cleanup_tokens(char **tokens)
{
	char 	**tmp;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	tmp = NULL;
	while (tokens[i])
	{
		if (ft_strlen(tokens[i++]) != 0)
			n++;
	}
	if (!(tmp = ft_memalloc(sizeof(tmp) * (n + 1))))
		return (NULL);
	i = 0;
	n = 0;
	while (tokens[i])
	{
		if (ft_strlen(tokens[i]) != 0)
			tmp[n++] = ft_strdup(tokens[i]);
		i++;
	}
	tmp[n] = NULL;
	ft_free_tab(&tokens);
	return (tmp);
}

int8_t			get_tokens(t_core *shell, char *line, char ***tokens)
{
	*tokens = ft_strsplit(line, " \t");
	if (**tokens == NULL)
		return (FAILURE);
	exp_converter(shell, *tokens);
	tilde_converter(shell, *tokens);
	*tokens = cleanup_tokens(*tokens);
	return (SUCCESS);
}

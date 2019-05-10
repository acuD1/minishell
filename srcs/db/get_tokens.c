/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 09:46:42 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/10 17:36:05 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void	tilde_converter(t_core *shell, char **tokens)
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

/*
static size_t	count_words(const char *s, char *charset)
{
	size_t	n_words;

	n_words = 0;
	while (*s)
	{
		if (ft_strstr(s, charset))
			s++;
		else
		{
			while (!(ft_strstr(s, charset)) && *s)
				s++;
			n_words++;
		}
	}
	return (n_words);
}

char			**ft_strsplit_charset(const char *s, char *charset)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	**tab;

	i = 0;
	j = 0;
	len = 0;
	if (!charset || !s)
		return (NULL);
	if (!(tab = ft_memalloc(sizeof(tab) * (count_words(s, charset) + 1))))
		return (NULL);
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i + len] && !(ft_strstr(s, charset)))
			len++;
		if (len)
			tab[j++] = ft_strsub(s, i, len);
		i += len ? len : 1;
		len = 0;
	}
	tab[j] = NULL;
	return (tab);
}
*/

int8_t		get_tokens(t_core *shell, char *line, char ***tokens)
{
	(void)shell;
	if (ft_strlen(line) == 0 || (ft_strlen(line) == 1 && ft_strchr(" \t", line[0])))
		return (FAILURE);
	int i = 0;
//	while (line)
	*tokens = ft_strsplit_charset(line, " \t");
	tilde_converter(shell, *tokens);
	return (SUCCESS);
}

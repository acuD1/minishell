/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:08:04 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/11 14:26:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *env)
{
	t_list *tmp;

	while (env)
	{
		free(ENV_DB->symbol);
		free(ENV_DB->value);
		free(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/28 10:15:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "define.h"
# include "struct.h"

# include <stdio.h>

/*
**	Core
*/

void				signal_handler(void);
void				exec_prompt(t_core *shell);
void				exec_process(t_core *shell, t_list *env, char **tokens);
int8_t				exec_builtins(t_core *shell, char **tokens);
int8_t				exit_handler(t_core *shell, int status);
void				free_list(t_list *env);
void				free_prompt(t_core *shell, char ***tokens, char *line);
void				builtins_parser(t_core *shell, char *tokens);
int8_t				shift_exp_tokens(t_list *env,
					t_list *var, char **tokens, char *tmp);
int8_t				exp_shifter(t_core *shell, char **tokens);
/*
**	Builtins
*/

void				cd_builtin(t_core *shell, char **tokens);
void				cd_handler(char *tokens, uint8_t handler);
void				echo_builtin(char **tokens);
void				env_builtin(t_core *shell, char **tokens);
void				env_builtin_usage(char **tokens);
uint8_t				tokens_parser_checker(char *tokens);
void				env_builtin_printer(t_core *shell, char **tokens);
int8_t				unsetenv_builtin(t_list **env, char **tokens);
int8_t				setenv_builtin(t_core *shell, t_list **env, char **tokens);
void				pwd_builtin(void);
void				exit_builtin(t_core *shell, char **tokens);
void				exec_handler(t_core *shell, char **tokens, uint8_t handler);

/*
** DB
*/

void				init_shell(t_core *shell, char **environ);
t_db				*fetch_db(t_db *db, const char *s);
int8_t				set_default_env(t_core *shell, t_list *env);
int8_t				get_tokens(t_core *shell, char *line, char ***tokens);
int8_t				set_env(t_core *shell, char **environ);
int8_t				get_opt(int ac, char **av, t_core *shell);
char				**get_envp(t_core *shell, t_list *env);
char				*get_bin(t_core *shell, t_list *env, const char *filename);
void				conv_home(t_core *shell, char **tokens, char *path, size_t i);
void				conv_pwd(t_core *shell, char **tokens, char *path, size_t i);

/*
**	Misc
*/

void				logger(t_core *shell, char *line, char **tokens);
void				open_logger_fd(t_core *shell, char *av);
void				credit(t_core *shell);
void				init_prompt(void);
void				print_opt(t_core *shell);

#endif

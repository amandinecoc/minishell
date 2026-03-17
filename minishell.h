/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:10:56 by amandine          #+#    #+#             */
/*   Updated: 2026/03/17 16:21:33 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*INCLUDES*/
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************************************************** */
/*TYPEDEF*/
// typedef enum e_status
// {
// 	Success,
// 	malloc_failure,
// 	command_not_found,
// }			t_status;

// typedef struct s_pipex
// {
// 	char	*file1;
// 	char	*cmd1;
// 	char	*file2;
// 	char	*cmd2;
// 	char	**tab_cmd1;
// 	char	**tab_cmd2;
// 	char	**tab_path;
// }			t_pipex;

/* ************************************************************************** */
/*PARSING*/
int parsing_minishell(char *line);
int goto_char(char to_find, char *str, int pos);

/* ************************************************************************** */
/*MINISHELL*/

#endif
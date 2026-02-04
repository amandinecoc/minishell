/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:10:56 by amandine          #+#    #+#             */
/*   Updated: 2026/02/04 18:12:39 by amandine         ###   ########.fr       */
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
// int			fill_struct_pipex(t_pipex *pipex, char **argv, char **envp);
// void		create_path(t_pipex *pipex, char **envp);
// void		access_cmd(t_pipex *data, int num);
// char		*create_cmd(t_pipex *data, char *cmd);
// void		print_error(int status);
// int			pipex(t_pipex *data, char **envp);
// void		free_pipex(t_pipex *data);
// void		first_process(t_pipex *data, char **envp, int *pipefd);
// void		second_process(t_pipex *data, char **envp, int *pipefd);

/* ************************************************************************** */
/*MINISHELL*/

#endif
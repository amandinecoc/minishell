/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:43:20 by amandine          #+#    #+#             */
/*   Updated: 2026/04/03 19:02:39 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	fill_struct_parsing(char *line, t_parsing *data_parsing, char **envp)
{
    data_parsing->start_line = ft_strdup(line);
	if (!data_parsing->start_line)
		return (Malloc_failure);
	return (Success);
}

int parsing_minishell(char *line, char **envp)
{
    int status;
    t_parsing data_parsing;
    
    if (fill_struct_parsing(line, &data_parsing, envp))
    status = check_line(line);
    if (status != Success)
        return (status);
    return(Success);
}

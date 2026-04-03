/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:47:57 by amandine          #+#    #+#             */
/*   Updated: 2026/04/03 21:47:59 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void fill_clone_envp(t_minishell *ms_data, char **envp)
{
    int i;
    int j;
    
    i = 0;
    while (envp[i] != NULL)
    {
        j = 0;
        while (envp[i][j] != NULL)
        {
            ms_data->envp[i][j] = envp[i][j];
            j++;
        }
        ms_data->envp[i][j] = '/0';
        i++;
    }
    ms_data->envp[i][j] = NULL;
}

int clone_envp(t_minishell *ms_data, char **envp)
{
    int i;
    
    i = 0;
    while (envp[i] != NULL)
        i++;
    ms_data->envp =malloc(sizeof(char *) * (i + 1));
	if (!ms_data->envp)
		return (Malloc_failure);
    i = 0;
    while (envp[i] != NULL)
    {
        ms_data->envp[i] = ft_strdup(envp[i]);
        if (ms_data->envp[i] == NULL)
            return (Malloc_failure);
        i++;
    }
    ms_data->envp[i] = NULL;
    fill_clone_envp(&ms_data, envp);
    return (Success);
}

int fill_struct_minishell(t_minishell *ms_data, char **envp)
{
    int status;
    
	if (clone_envp(&ms_data, envp) != Success)
		return (status);
	return (Success);
}

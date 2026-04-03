/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:25 by amandine          #+#    #+#             */
/*   Updated: 2026/04/03 18:58:09 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int argc, char **envp)
{
    char *line;
    int status;
    
    if (argc < 1)
        return (EXIT_FAILURE);
    while (1) //ctrl-D fonctionne avec cette boucle : while ((line = readline("minishell> ")) != NULL)
    {
        line = readline("minishell>");
        if (line != NULL)
            add_history(line);
        if (ft_strncmp(line, "clear", 6) == 0)
        {
            rl_clear_history();
            printf("Historique effacé.\n");
        }
        status = parsing_minishell(line, envp);
        if (status != Success)
        {
            printf("error_parsing\n"); //printf status error autre fonction
            free(line);
            break;
        }
        printf("Vous avez tapé: %s\n", line);
        free(line);
    }
    printf("Fin\n");
    return 0;
}
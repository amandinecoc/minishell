/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:25 by amandine          #+#    #+#             */
/*   Updated: 2026/04/02 21:38:49 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main()
{
    char *line;
    int status;
    
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
        status = parsing_minishell(line);
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
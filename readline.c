/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:25 by amandine          #+#    #+#             */
/*   Updated: 2026/02/04 19:14:23 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main()
{
    char *line;
    
    line = readline("minishell> ");
    while (1)
    {
        if (line != NULL)
            add_history(line);
        if (ft_strncmp(line, "clear", 6) == 0)
        {
            rl_clear_history();
            printf("Historique effacé.\n");
        }
        printf("Vous avez tapé: %s\n", line);
        free(line);
        line = readline("minishell> ");
    }
    printf("Fin\n");
    return 0;
}
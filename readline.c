/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:25 by amandine          #+#    #+#             */
/*   Updated: 2026/02/10 12:03:52 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main()
{
    char *line;
    
    while (1)
    {
        line = readline("minishell>");
        if (line != NULL)
            add_history(line);
        if (ft_strncmp(line, "clear", 6) == 0)
        {
            rl_clear_history();
            printf("Historique effacé.\n");
        }
        printf("Vous avez tapé: %s\n", line);
        free(line);
    }
    printf("Fin\n");
    return 0;
}
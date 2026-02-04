/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:25 by amandine          #+#    #+#             */
/*   Updated: 2026/02/04 19:22:38 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main()
{
    char *line;
    
    while (1)
    {
        line = readline("minishell>");  //gestion line
        if (line != NULL)
            add_history(line);
        if (ft_strncmp(line, "clear", 6) == 0)  //parsing
        {
            rl_clear_history();
            printf("Historique effacé.\n");
        }
        printf("Vous avez tapé: %s\n", line);  //executable
        free(line);
        line = readline("minishell> ");
    }
    printf("Fin\n");  //clear et free tout en cas de ctrl d
    return 0;
}
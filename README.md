# Les grandes étapes
----------
## Etape 1

Comprendre la fonction readline.
Readline est une fonction clé de minishell. Cette fonction servira à ouvrir le prompt de minishell.
On peut l'utiliser dans une boucle infinie.

**Exemple :**
```c
int handling_readline(char *line)
{}

int parsing_line(char *line)
{}

int execute_line(char *line)
{}

int clear_and_free_line(char *line)
{}

int main()
{
    char *line;
    
    while (1)
    {
        handling_readline(line);
        parsing_line(line);
        execute_line(line);
        free(line);
    }
    clear_and_free_line(line);
    return 0;
}
```
----------

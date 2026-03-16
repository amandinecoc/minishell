# Minishell
----------
## Etape 1

Comprendre la fonction readline.
Readline est une fonction clé de minishell. Cette fonction servira à ouvrir le prompt de minishell.
On peut l'utiliser dans une boucle infinie.

**Exemple :**
```c
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
    clear_and_free(line);
    return 0;
}
```
----------
## Etape 2

Commencer le parsing. Verifier si la ligne de commande reçu ne possede pas de caracteres non admis ou des côtes non fermés.

**Exemple :**
```c
{
str[i]

int goto_char(char to_find, char *str, int pos)
}
```
----------
## Etape 3

Tokeniser la ligne de commande. Faire en sorte de savoir ce que chaque éléments est (commande, redirection, pipe, mot, arguments...)

**Exemple :**
```c
{
struct 

int *word_type commande commmade file redirection
char **line_world 
int redir
char *redir
}
```
----------

<!-- line[0] = elements[0]
struc
cat echo file

typedef enum e_status
{
	command,
	redirection,
	command_not_found,
}			t_status;

 str[0]
file > cat
file 
>
cat -->


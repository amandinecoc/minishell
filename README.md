# Subject to Minishell
----------
* **Program name** : minishell
* **Turn in files** : Makefile, *.h, *.c
* **Makefile** :  NAME, all, clean, fclean, re
* **Libft authorized** : Yes
* **Description** : Write a shell
* **Include** : #include <readline/readline.h>, <readline/history.h>, <stdio.h>, <string.h>, <stdlib.h>, <errno.h>, <unistd.h>, <sys/types.h>, <fcntl.h>, <sys/stat.h>, <sys/wait.h>, <signal.h>, <dirent.h>, <sys/ioctl.h>, <termios.h>, <termcap.h>, <curses.h>/<ncurses.h>, <stdlib.h> 
* **External functs** : readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
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

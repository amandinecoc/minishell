# Subject to Minishell
----------
* **Program name** : minishell
* **Turn in files** : Makefile, *.h, *.c
* **Makefile** :  NAME, all, clean, fclean, re
* **Libft authorized** : Yes
* **Description** : Write a shell
* **Include** : #include <readline/readline.h>, <readline/history.h>, <stdio.h>, <string.h>, <stdlib.h>, <errno.h>, <unistd.h>, <sys/types.h>, <fcntl.h>, <sys/stat.h>, <sys/wait.h>, <signal.h>, <dirent.h>, <sys/ioctl.h>, <termios.h>, <termcap.h>, <curses.h>/<ncurses.h>, <stdlib.h> 
* **External functs** : readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

### Your shell should:
* Display a prompt when waiting for a new command.
* Have a working history.
* Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
* Use at most one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.
* Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
* Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
* Implement the following redirections:
    * '<' should redirect input.
    * '>' should redirect output.
    * '<<' should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
    * '>>' should redirect output in append mode.
* Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
* Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
* Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
* In interactive mode:
    * ctrl-C displays a new prompt on a new line.
    * ctrl-D exits the shell.
    * ctrl-\ does nothing.
* Your shell must implement the following built-in commands:
    * echo with option-n
    * cd with only a relative or absolute path
    * pwd with no options
    * export with no options
    * unset with no options
    * env with no options or arguments
    * exit with no options
  The readline() function may cause memory leaks, but you are not required to fix them. However, this does not mean your own code, yes the code you wrote, can have memory leaks.
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

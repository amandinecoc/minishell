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
* Afficher un prompt lors de l'attente d'une nouvelle commande.
* Conserver un historique des commandes.
* Rechercher et exécuter le fichier exécutable approprié (en fonction de la variable PATH ou à l'aide d'un chemin relatif ou absolu).
* Utiliser au maximum une variable globale pour indiquer la réception d'un signal. Attention : cette approche garantit que le gestionnaire de signaux n'accédera pas aux structures de données principales.
* Ne pas interpréter les guillemets non fermés ni les caractères spéciaux non requis par le sujet, tels que \ (barre oblique inverse) ou ; (point-virgule).
* Gérer l'apostrophe (') afin d'empêcher l'interpréteur de commandes d'interpréter les métacaractères dans la séquence entre guillemets.
* Gérer les guillemets doubles (« ») afin d'empêcher l'interpréteur de commandes d'interpréter les métacaractères dans la séquence entre guillemets, à l'exception du signe dollar ($).
* //Si tu croises $ dans "" fait l expand variable d environnement, mais pas pour $ dans ''.//
* Implémenter les redirections suivantes :
   * '<' redirige l'entrée.
   * '>' redirige la sortie.
   * '<<' reçoit un délimiteur, puis lit l'entrée jusqu'à rencontrer une ligne contenant ce délimiteur. La mise à jour de l'historique n'est pas nécessaire.
   * '>>' redirige la sortie en mode ajout.
* Implémentez les pipes (caractère |). La sortie de chaque commande du pipeline est connectée à l'entrée de la commande suivante via un pipe.
* Gérez les variables d'environnement ($ suivi d'une séquence de caractères) qui doivent être remplacées par leurs valeurs.
* Gérez $? qui doit être remplacé par le code de sortie du dernier pipeline exécuté au premier plan.
* Gérez Ctrl+C, Ctrl+D et Ctrl+\ qui doivent se comporter comme dans Bash.
* En mode interactif :
   * Ctrl+C affiche une nouvelle invite sur une nouvelle ligne.
   * Ctrl+D quitte l’interpréteur de commandes.
   * Ctrl+\ ne fait rien.
* Votre shell doit implémenter les commandes intégrées suivantes :
   * echo avec option-n
   * cd avec un chemin relatif ou absolu (PATH)
   * pwd sans options
   * export sans options
   * unset sans options
   * env sans options ni arguments
   * exit sans options

La fonction readline() peut provoquer des fuites de mémoire, mais vous n'êtes pas tenu de les corriger. Cependant, cela ne signifie pas que votre propre code, c'est-à-dire le code que vous avez écrit, peut contenir des fuites de mémoire.

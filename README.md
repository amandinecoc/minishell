# Subject to Minishell
----------
* **Program name** : minishell
* **Turn in files** : Makefile, *.h, *.c
* **Makefile** :  NAME, all, clean, fclean, re
* **Libft authorized** : Yes
* **Description** : Write a shell
* **Include** : #include <readline/readline.h>, <readline/history.h>, <stdio.h>, <string.h>, <stdlib.h>, <errno.h>, <unistd.h>, <sys/types.h>, <fcntl.h>, <sys/stat.h>, <sys/wait.h>, <signal.h>, <dirent.h>, <sys/ioctl.h>, <termios.h>, <termcap.h>, <curses.h>/<ncurses.h>, <stdlib.h> 
* **External functs** : readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## New functions

### readline : 
Elle affiche un prompt (chaîne passée en argument), lit une ligne complète depuis l’entrée standard en offrant édition basique (flèches, historique), et renvoie un pointeur vers une nouvelle chaîne allouée contenant tout ce que l’utilisateur a tapé (sans le saut de ligne). Si l’utilisateur envoie EOF (Ctrl+D) ou qu’une erreur survient, la fonction renvoie NULL. Il faut donc libérer la chaîne avec free() après usage.

**Exemple :**
```c
int main(void)
{
    char *line;
    
    while ((line = readline("minishell> ")) != NULL)
    {
        if (*line)                      // ajoute dans l’historique seulement si non vide
            add_history(line);
        printf("Vous avez tapé: %s\n", line);
        free(line);
    }
    printf("Fin de l’entrée (Ctrl+D)\n");
    return 0;
}
```

Compilation possible avec cc main.c -lreadline.

### rl_clear_history : 
efface entièrement l’historique des lignes stocké par Readline. Après l’appel, history_list() est vide et add_history() repart de zéro. Il n’y a pas de paramètre ni de valeur de retour ; c’est utile par exemple lorsqu’on souhaite “oublier” tout ce qui a été tapé (sécurité, reset du shell, etc.).

**Exemple :**
```c
int main(void)
{
    char *line;

    while ((line = readline("mini> ")) != NULL)
    {
        if (*line)
            add_history(line);

        if (!strcmp(line, "clearhist"))
        {
            rl_clear_history();
            printf("Historique effacé.\n");
        }

        free(line);
    }
    return 0;
}
```
Ici, taper clearhist supprime immédiatement tout l’historique.

### rl_on_new_line : 
informe Readline qu’on se trouve à une nouvelle ligne “propre” avant une future réaffichage. Elle ne redessine rien toute seule : elle prépare le curseur interne, ce qui est nécessaire quand le prompt/entrée est perturbé (par exemple après un signal qui écrit sur stdout). Typiquement on l’associe à rl_replace_line() (pour remplacer le contenu courant) puis rl_redisplay() (pour redessiner).

**Exemple d’usage dans un gestionnaire de signal :**
```c
static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();                // indique à Readline qu'une nouvelle ligne débute
    rl_replace_line("", 0);          // vide l'entrée courante
    rl_redisplay();                  // redessine le prompt proprement
}

int main(void)
{
    signal(SIGINT, handle_sigint);

    char *line;
    while ((line = readline("mini> ")) != NULL)
    {
        if (*line)
            add_history(line);
        printf("Commande: %s\n", line);
        free(line);
    }
    return 0;
}
```
Ici, quand l’utilisateur presse Ctrl+C, on force le retour à une nouvelle ligne, on efface l’entrée en cours et on redessine le prompt sans artefacts.

### rl_replace_line :
rl_replace_line(const char *text, int clear_undo) remplace le contenu courant de la ligne éditée par Readline (ce que l’utilisateur est en train de taper) par text. Si clear_undo vaut 1, Readline efface la pile d’annulations pour cette ligne ; si 0, l’utilisateur peut encore faire Ctrl+_ pour revenir en arrière. La fonction ne redessine pas la ligne à l’écran : il faut appeler rl_redisplay() après pour voir la mise à jour.

**Usage typique (par exemple après un signal) :**
```c
static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);      // vide la saisie en cours
    rl_redisplay();              // redessine le prompt
}

int main(void)
{
    signal(SIGINT, handle_sigint);

    char *line;
    while ((line = readline("mini> ")) != NULL)
    {
        if (*line == '!')
            rl_replace_line("echo Surprise!", 1); // injecte une commande
        if (*line)
            add_history(line);
        printf("Commande: %s\n", line);
        free(line);
    }
    return 0;
}
```
Quand l’utilisateur tape une ligne qui commence par !, on remplace dynamiquement l’entrée par echo Surprise! avant de l’exécuter.

### rl_redisplay : 
redessine la ligne gérée par Readline : prompt + contenu courant, en tenant compte des modifications internes (par exemple après rl_replace_line() ou lorsqu’un signal a imprimé quelque chose sur l’écran). Elle n’a pas d’arguments et s’utilise chaque fois qu’on change l’état de la ligne sans passer par la frappe utilisateur.

**Exemple avec gestion de SIGINT :**
```c
static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();        // repositionne l’état interne
    rl_replace_line("", 0);  // efface la saisie courante
    rl_redisplay();          // redessine prompt + ligne vide
}

int main(void)
{
    signal(SIGINT, handle_sigint);

    char *line;
    while ((line = readline("mini> ")) != NULL)
    {
        if (*line)
            add_history(line);
        printf("Commande: %s\n", line);
        free(line);
    }
    return 0;
}
```
Lorsque l’utilisateur frappe Ctrl+C, on nettoie l’écran (nouvelle ligne), on remet Readline dans un état “ligne vide” puis rl_redisplay() réaffiche le prompt proprement.

### add_history : 
add_history(const char *line) ajoute une ligne à l’historique géré par GNU Readline. La fonction dupplique la chaîne passée (elle en fait une copie interne) et l’insère à la fin de la liste d’historique, ce qui permet ensuite d’y naviguer avec ↑/↓ ou via les API d’historique. En général on n’ajoute que des lignes non vides pour éviter de polluer l’historique.

**Exemple simple :**
```c
int main(void)
{
    char *line;

    while ((line = readline("mini> ")) != NULL)
    {
        if (*line)                // évite d’ajouter les lignes vides
            add_history(line);

        printf("Commande: %s\n", line);
        free(line);
    }
    return 0;
}
```
Ici, chaque commande non vide tapée par l’utilisateur est mémorisée : la touche ↑ la fera réapparaître lors des saisies suivantes.

### signal : 
signal(int signum, void (*handler)(int)) installe un gestionnaire pour un signal POSIX : quand le processus reçoit signum (par exemple SIGINT), il exécutera la fonction handler. La fonction renvoie l’ancien gestionnaire (utile pour restauration). Si on passe SIG_IGN, on ignore le signal ; SIG_DFL remet le comportement par défaut. Attention : signal a un comportement moins portable/fiable que sigaction, mais reste accepté pour minishell.

**Exemple : ignorer Ctrl+C pendant une section critique et revenir ensuite au comportement par défaut.**
```c
void custom_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nInterruption ignorée\n", 23);
}

int main(void)
{
    struct sigaction old;
    old.sa_handler = SIG_DFL; // placeholder

    // installer gestionnaire
    signal(SIGINT, custom_sigint);

    printf("Appuyez sur Ctrl+C (pendant 5 s)...\n");
    sleep(5);

    // restaurer comportement par défaut
    signal(SIGINT, SIG_DFL);
    printf("De nouveau sensible à Ctrl+C.\n");
    for (;;)
        pause(); // attend un signal, qui cette fois terminera le programme
}
```
Ici custom_sigint reçoit SIGINT, imprime un message et retourne, ce qui évite de tuer le programme pendant la première phase.

### sigaction : 
sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) installe de manière fiable un gestionnaire pour un signal POSIX. Contrairement à signal, elle permet de configurer précisément comment le signal est masqué, quelles options s’appliquent, et elle évite les comportements non portables. act décrit le nouveau handler, oldact (optionnel) reçoit l’ancien. 

**La structure :**
```c
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
};
```
On choisit soit sa_handler (handler simple), soit sa_sigaction (si SA_SIGINFO). sa_mask définit les signaux bloqués pendant l’exécution du handler, sa_flags active des options comme SA_RESTART, SA_NODEFER, etc.

**Exemple : gérer SIGINT (Ctrl+C) dans un minishell et empêcher qu’il interrompe certaines syscalls en réactivant les appels bloquants (SA_RESTART).**
```c
static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nmini> ", 7);
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);       // aucun signal supplémentaire masqué
    sa.sa_flags = SA_RESTART;       // relance read(), etc., après le handler

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C (handler keeps shell alive)\n");
    for (;;)
        pause();                    // attend un signal, repris grâce à SA_RESTART
}
```
Ici, sigaction installe handle_sigint. Lorsqu’on presse Ctrl+C, le handler imprime un prompt propre et pause() continue d’attendre car SA_RESTART relance l’appel bloquant après le handler.

### sigemptyset : 
sigemptyset(sigset_t *set) initialise l’ensemble de signaux pointé par set à vide : après l’appel, aucun signal n’est présent dans ce masque. On l’utilise avant de configurer un masque (par exemple pour un sigaction, un sigprocmask, ou pour sigset_t utilisé par sigwait) afin de repartir d’un ensemble propre.

**Snippet :**
```c
int main(void)
{
    sigset_t mask;

    sigemptyset(&mask);          // part d’un ensemble vide
    sigaddset(&mask, SIGINT);    // ajoute SIGINT
    sigaddset(&mask, SIGQUIT);   // ajoute SIGQUIT

    // bloque ces signaux
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
    {
        perror("sigprocmask");
        return 1;
    }

    printf("SIGINT/SIGQUIT bloqués pendant 5 s\n");
    sleep(5);

    sigemptyset(&mask);          // réutilise le même sigset_t, réinitialisé
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
        perror("sigprocmask");

    puts("Signaux rétablis.");
    return 0;
}
```
Ici sigemptyset prépare le masque avant d’ajouter les signaux à bloquer, puis on le réutilise pour rétablir l’état normal.

### sigaddset : 
sigaddset(sigset_t *set, int signum) ajoute signum à l’ensemble de signaux pointé par set. On appelle d’abord sigemptyset(&set) ou sigfillset(&set), puis on ajoute ou retire les signaux voulus. Erreur si signum n’est pas un signal valide.

**Exemple : bloquer temporairement SIGINT et SIGQUIT pendant une section critique :**
```c
int main(void)
{
    sigset_t block;

    sigemptyset(&block);
    sigaddset(&block, SIGINT);
    sigaddset(&block, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &block, NULL) == -1)
    {
        perror("sigprocmask");
        return 1;
    }

    printf("Section critique: Ctrl+C / Ctrl+\\ ignorés pendant 5 s\n");
    sleep(5);

    sigemptyset(&block);
    sigprocmask(SIG_SETMASK, &block, NULL); // rétablit les signaux
    puts("Section critique terminée.");
    return 0;
}
```
Ici sigaddset construit le masque de signaux à bloquer.

### kill : 
kill(pid_t pid, int sig) envoie le signal sig à un ou plusieurs processus.

Si pid > 0, le signal va uniquement au processus portant ce PID.
Si pid == 0, il va à tous les processus du même groupe que l’appelant.
Si pid == -1, il touche tous les processus que l’utilisateur a le droit de signaler (sauf quelques cas spéciaux).
Si pid < -1, il cible le groupe de processus -pid.
En pratique, on s’en sert pour terminer un processus (SIGTERM, SIGKILL), relancer (SIGHUP), ou simplement tester son existence avec un signal nul (sig = 0).

**Exemple : envoyer SIGTERM à un processus enfant pour le fermer proprement.**
```c
int main(void)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        // Processus enfant
        printf("Child %d running...\n", getpid());
        pause();                       // attend un signal
        printf("Child terminating.\n");
        return 0;
    }

    // Processus parent
    sleep(2);                          // laisse l’enfant tourner
    if (kill(pid, SIGTERM) == -1)
        perror("kill");

    wait(NULL);                        // attend la fin de l’enfant
    puts("Child cleaned up.");
    return 0;
}
```
172 x 11
kill(pid_t pid, int sig) envoie le signal sig à un ou plusieurs processus.

Si pid > 0, le signal va uniquement au processus portant ce PID.
Si pid == 0, il va à tous les processus du même groupe que l’appelant.
Si pid == -1, il touche tous les processus que l’utilisateur a le droit de signaler (sauf quelques cas spéciaux).
Si pid < -1, il cible le groupe de processus -pid.
En pratique, on s’en sert pour terminer un processus (SIGTERM, SIGKILL), relancer (SIGHUP), ou simplement tester son existence avec un signal nul (sig = 0).

Exemple : envoyer SIGTERM à un processus enfant pour le fermer proprement.

Ici, kill envoie SIGTERM à l’enfant ; celui-ci quitte sa pause et se termine, tandis que le parent fait wait pour récupérer son statut.

### getcwd : 
getcwd(char *buf, size_t size) remplit buf avec le chemin absolu du répertoire courant et renvoie ce pointeur. Tu fournis un tampon assez grand, sinon la fonction échoue (renvoie NULL et errno vaut ERANGE). Variante pratique : passer NULL et 0, auquel cas getcwd alloue elle-même une chaîne (à libérer avec free).

**Exemple en C :**
```c
int main(void)
{
    char *cwd = getcwd(NULL, 0);  // allocation automatique
    if (!cwd)
    {
        perror("getcwd");
        return 1;
    }
    printf("Répertoire courant : %s\n", cwd);
    free(cwd);
    return 0;
}
```
Ici on laisse getcwd allouer la mémoire, on affiche le chemin courant puis on libère la chaîne.

### chdir : 
chdir(const char *path) change le répertoire courant du processus vers path. En cas de succès, la fonction renvoie 0; sinon -1 et errno décrit l’erreur (ENOENT, EACCES, etc.). Ça affecte toutes les opérations ultérieures qui utilisent des chemins relatifs (ouvrir un fichier, lancer un programme…).

**Exemple d’usage :**
```c
int main(void)
{
    if (chdir("/tmp") == -1)
    {
        perror("chdir");
        return 1;
    }
    printf("Répertoire courant déplacé vers /tmp\n");
    // Toute ouverture relative se fera maintenant depuis /tmp
    return 0;
}
```
Après chdir("/tmp"), un open("file.txt", …) ciblera /tmp/file.txt tant que le processus ne rechange pas de répertoire.

### stat : 
int stat(const char *path, struct stat *buf) récupère les métadonnées d’un fichier/répertoire/symlink (résolu) et remplit buf. On obtient taille, permissions, timestamps, type (fichier régulier, dossier, etc.). Retourne 0 si succès, -1 sinon (avec errno).

**Exemple :**
```c
int main(void)
{
    struct stat st;

    if (stat("minishell.c", &st) == -1)
    {
        perror("stat");
        return 1;
    }

    printf("Taille: %lld octets\n", (long long)st.st_size);
    if (S_ISDIR(st.st_mode))
        puts("C’est un répertoire");
    else if (S_ISREG(st.st_mode))
        puts("C’est un fichier régulier");
    return 0;
}
```
Ici on interroge minishell.c, puis on teste st.st_mode via les macros S_ISDIR, S_ISREG pour déterminer le type.

### lstat : 
lstat(const char *path, struct stat *buf) fonctionne comme stat, sauf qu’elle ne suit pas les liens symboliques : si path est un symlink, buf décrit le lien lui‑même (taille du chemin cible, permissions du lien) plutôt que la cible pointée. Pour tout autre type de fichier, le résultat est identique à stat.

**Exemple :**
```c
int main(void)
{
    struct stat info;

    if (lstat("mon_lien", &info) == -1)
    {
        perror("lstat");
        return 1;
    }

    if (S_ISLNK(info.st_mode))
        printf("mon_lien est un symlink, taille = %lld\n", (long long)info.st_size);
    else
        printf("mon_lien n’est pas un symlink\n");

    return 0;
}
```
Si mon_lien pointe vers un fichier, lstat détecte qu’il s’agit d’un lien et donne la longueur de la cible (nombre de caractères). Avec stat, on aurait obtenu les métadonnées de la cible.

### fstat : 
fstat(int fd, struct stat *buf) renseigne les métadonnées du fichier déjà ouvert correspondant au descripteur fd. Même informations que stat/lstat, mais sans re-résoudre le chemin : pratique quand on manipule un fichier anonyme (pipe, socket, fichier temporaire) ou qu’on veut éviter une seconde ouverture.

**Exemple : vérifier le type d’un descripteur déjà ouvert.**
```c
int main(void)
{
    int fd = open("minishell.c", O_RDONLY);
    if (fd == -1)
        return perror("open"), 1;

    struct stat st;
    if (fstat(fd, &st) == -1)
        return perror("fstat"), close(fd), 1;

    printf("Taille: %lld octets\n", (long long)st.st_size);
    if (S_ISREG(st.st_mode))
        puts("Descripteur sur un fichier régulier");
    else if (S_ISDIR(st.st_mode))
        puts("Descripteur sur un répertoire");
    close(fd);
    return 0;
}
```
On ouvre le fichier, fstat lit ses métadonnées via le FD, puis on les interprète avec les macros S_IS*.

### unlink : 
unlink(const char *path) supprime le lien portant path d’un système de fichiers. Si c’est le dernier lien vers l’inode (et qu’aucun processus n’a le fichier ouvert), l’espace est libéré. L’appel renvoie 0 en cas de succès, -1 et errno sinon (ENOENT, EACCES, etc.).

**Exemple :**
```c
int main(void)
{
    if (unlink("tmp.txt") == -1)
    {
        perror("unlink");
        return 1;
    }
    puts("tmp.txt supprimé.");
    return 0;
}
```
Ici on efface tmp.txt. Si un processus a encore le fichier ouvert, il pourra continuer à l’utiliser jusqu’à fermeture, mais il n’apparaît plus dans le répertoire.

### opendir : 
opendir(const char *name) ouvre un répertoire et renvoie un pointeur DIR * à utiliser avec readdir()/closedir(). En cas d’échec (pas de droits, chemin invalide…), la fonction renvoie NULL et errno explique l’erreur. Le répertoire reste ouvert jusqu’à closedir().

**Exemple : lister les entrées d’un dossier.**
```c
int main(void)
{
    DIR *dir = opendir(".");
    if (!dir)
        return perror("opendir"), 1;

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL)
        printf("%s\n", ent->d_name);

    closedir(dir);
    return 0;
}
```
Ici on ouvre le répertoire courant, on lit chaque entrée avec readdir (qui renvoie NULL à la fin), puis on ferme proprement avec closedir.

### readdir : 
readdir(DIR *dirp) lit la prochaine entrée du répertoire ouvert par opendir. Elle renvoie un pointeur vers une structure statique struct dirent décrivant l’entry (nom, type si dispo, etc.). Quand il n’y a plus d’entrées ou qu’une erreur survient, elle renvoie NULL; on vérifie errno pour distinguer fin de lecture vs erreur.

**Usage typique :**
```c
int main(void)
{
    DIR *dir = opendir(".");
    if (!dir)
        return perror("opendir"), 1;

    errno = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
        printf("• %s\n", entry->d_name);

    if (errno != 0)                // NULL causé par une erreur
        perror("readdir");

    closedir(dir);
    return 0;
}
```
On ouvre le dossier courant, on boucle avec readdir pour afficher chaque nom, puis on ferme avec closedir.

### closedir : 
closedir(DIR *dirp) ferme un flux de répertoire précédemment obtenu avec opendir. Elle libère les ressources associées et retourne 0 si tout va bien, ‑1 (avec errno) en cas d’échec. Toujours l’appeler après avoir fini d’itérer avec readdir, sinon on laisse un descripteur de répertoire ouvert.

**Exemple simple :**
```c
int main(void)
{
    DIR *dir = opendir(".");
    if (!dir)
        return perror("opendir"), 1;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
        puts(entry->d_name);

    if (closedir(dir) == -1)
        return perror("closedir"), 1;

    return 0;
}
```
On ouvre le répertoire courant, on liste les entrées, puis on appelle closedir(dir) pour fermer proprement le flux.

### isatty : 
isatty(int fd) teste si le descripteur fd est attaché à un terminal (tty). Retourne 1 si oui, 0 sinon (et errno indique l’erreur). Dans un minishell, ça sert à savoir si on est en mode interactif (entrée clavier) ou si l’entrée vient d’un pipe/fichier.

**Exemple : détecter un script vs un prompt interactif.**
```c
int main(void)
{
    if (isatty(STDIN_FILENO))
        puts("Mode interactif : l’utilisateur tape directement.");
    else
        puts("Entrée redirigée (pipe ou fichier).");

    return 0;
}
```
Lancer ce programme dans un terminal affiche “Mode interactif…”. Si tu fais echo ls | ./a.out, l’entrée n’est plus un tty et isatty renverra 0.

### ttyname : 
ttyname(int fd) renvoie le chemin (ex. 2) du terminal associé au descripteur fd, ou NULL si ce n’est pas un terminal (ou en cas d’erreur). Le résultat pointe vers une chaîne statique à ne pas modifier.

**Exemple rapide :**
```c
int main(void)
{
    if (!isatty(STDIN_FILENO))
        return puts("stdin n’est pas un TTY"), 0;

    char *tty = ttyname(STDIN_FILENO);
    if (!tty)
        return perror("ttyname"), 1;

    printf("stdin est attaché à : %s\n", tty);
    return 0;
}
```
Lancé dans un terminal interactif, le programme affiche le pseudo-terminal courant. Redirige stdin (ex. echo hi | ./a.out) et isatty échouera, montrant que ttyname n’est valable que pour des TTYs.

### ttyslot : 
ttyslot() renvoie l’indice (slot) du terminal contrôlant le processus dans la base de données /etc/ttys (ou équivalent). En pratique :

Retour > 0 : numéro du terminal (utile pour indexer des tableaux liés aux TTY).
0 ou -1 : échec (pas de terminal contrôlant, ou erreur).
On l’utilise rarement, mais dans un shell ça peut identifier l’entrée courante quand on manipule des structures historiques dérivées de /etc/utmp.

**Exemple minimal :**
```c
int main(void)
{
    int slot = ttyslot();
    if (slot <= 0)
    {
        puts("Aucun TTY contrôlant ou erreur.");
        return 0;
    }
    printf("Slot TTY courant : %d\n", slot);
    return 0;
}
```
Lance-le depuis un terminal : tu obtiendras généralement un petit entier (>0). Exécuté sans terminal (par exemple via un service ou un pipe sans TTY), le slot vaut 0/‑1, ce qui indique l’absence de terminal contrôlant.

### ioctl : 
ioctl(int fd, unsigned long request, void *argp) envoie une commande de contrôle au pilote associé au descripteur fd. Les opérations disponibles (et la structure attendue dans argp) dépendent du type d’objet : TTY, socket, bloc, etc. Chaque commande request est définie dans les en‑têtes du pilote (par ex. <sys/ioctl.h>, <termios.h>). Retour 0 si succès, ‑1 sinon (avec errno).

**Exemple classique : récupérer la taille du terminal pour ajuster l’affichage d’un minishell.**
```c
int main(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    {
        perror("ioctl TIOCGWINSZ");
        return 1;
    }

    printf("Terminal: %d colonnes x %d lignes\n", ws.ws_col, ws.ws_row);
    return 0;
}
```
TIOCGWINSZ est une requête standard pour TTYs : ioctl remplit ws avec les dimensions du terminal courant. Si STDOUT_FILENO n’est pas un terminal, l’appel échoue.

### getenv : 
getenv(const char *name) cherche une variable d’environnement appelée name et renvoie un pointeur vers la chaîne de caractères qui contient sa valeur. Si la variable n’existe pas, elle renvoie NULL. Le pointeur pointe vers une zone interne gérée par le système : ne pas la modifier ni la free. La valeur reste valable jusqu’à ce que l’environnement soit changé (ex. via setenv, putenv, unsetenv).

**Exemple :**
```c
int main(void)
{
    const char *home = getenv("HOME");
    if (!home)
    {
        puts("HOME n'est pas défini");
        return 1;
    }
    printf("Le répertoire perso est: %s\n", home);
    return 0;
}
```
Ici, getenv("HOME") récupère le chemin du dossier utilisateur et l’affiche.

### tcgetattr : 
tcgetattr(int fd, struct termios *termios_p) lit les paramètres du terminal associé à fd (généralement STDIN_FILENO) et les range dans la structure termios pointée. On obtient ainsi les flags d’entrée/sortie, les modes canonique/echo, la taille des buffers, etc. La fonction renvoie 0 si succès, ‑1 sinon (errno).

**Usage classique : sauver la configuration avant de passer en mode “raw” puis la restaurer.**
```c
int main(void)
{
    struct termios orig, raw;

    if (tcgetattr(STDIN_FILENO, &orig) == -1)
        return perror("tcgetattr"), 1;

    raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);   // désactive mode canonique et echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    printf("Tapez quelques caractères (finissez par q)\n");
    int c;
    while ((c = getchar()) != 'q')
        printf("lu: %02x\n", c);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig); // restauration
    puts("Terminé.");
    return 0;
}
```
Ici tcgetattr capture la config initiale ; on modifie les flags pour lire caractère par caractère sans echo, puis on restaure la config originale à la fin.

### tgetent : 
tgetent(char *bp, const char *term) charge la description de terminal (Termcap) correspondant à term dans la zone mémoire pointée par bp (ou dans une zone statique si bp == NULL). Elle renvoie 1 si le terminal est trouvé, 0 si l’entrée n’existe pas, ‑1 si la base termcap n’est pas accessible (/etc/termcap, TERMCAP, etc.). On appelle généralement tgetent(NULL, getenv("TERM")) avant d’utiliser les fonctions tgetstr, tgetnum, tgetflag, etc., afin de récupérer les capacités (séquences d’échappement) du terminal.

**Exemple : initialiser Termcap et obtenir les séquences “clear screen” et “move cursor”.**
```c
int main(void)
{
    char term_buffer[2048];
    const char *term = getenv("TERM");

    if (!term)
        return fprintf(stderr, "TERM non défini\n"), 1;

    if (tgetent(term_buffer, term) != 1)
        return fprintf(stderr, "Impossible de charger termcap pour %s\n", term), 1;

    char *clear = tgetstr("cl", NULL); // effacer l'écran
    char *cm = tgetstr("cm", NULL);    // positionnement curseur

    if (!clear || !cm)
        return fprintf(stderr, "Capacités manquantes\n"), 1;

    fputs(clear, stdout);              // efface l'écran
    printf(tgoto(cm, 10, 5));          // place le curseur colonne 10, ligne 5
    puts("Hello termcap!");
    return 0;
}
```
tgetent charge les données pour le terminal courant, ce qui permet ensuite de récupérer les séquences de contrôle nécessaires pour dessiner une interface texte portable.

### tgetflag : 
tgetflag(const char *id) interroge la base termcap chargée avec tgetent et renvoie 1 si la capacité booléenne identifiée par id est présente pour le terminal courant, 0 sinon. On s’en sert pour savoir si un terminal supporte une fonctionnalité (ex. am = auto‐margin, bs = backspace, mi = mouvements en mode insert) avant d’envoyer des séquences dépendantes de cette capacité.

**Exemple :**
```c
int main(void)
{
    char termbuf[2048];
    const char *term = getenv("TERM");
    if (!term)
        return fprintf(stderr, "TERM non défini\n"), 1;

    if (tgetent(termbuf, term) != 1)
        return fprintf(stderr, "Impossible de charger termcap\n"), 1;

    if (tgetflag("am"))
        puts("Ce terminal gère le retour automatique à la ligne (am).");
    else
        puts("Pas de auto-margin : attention à gérer les fins de ligne manuellement.");

    if (tgetflag("bs"))
        puts("Backspace pris en charge.");
    else
        puts("Pas de backspace natif, il faut prévoir une alternative.");

    return 0;
}
```
On initialise Termcap via tgetent, puis tgetflag("am") et tgetflag("bs") indiquent si le terminal sait revenir automatiquement en début de ligne et accepter la touche retour arrière.

### tgetnum : 
tgetnum(const char *id) interroge l’entrée termcap déjà chargée (via tgetent) et renvoie la valeur numérique associée à l’identifiant id. Si la capacité numérique n’existe pas pour ce terminal, la fonction renvoie −1. On s’en sert pour connaître, par exemple, le nombre de lignes (li) ou de colonnes (co), la vitesse du baud rate (sg), etc.

**Exemple :**
```c
int main(void)
{
    char termbuf[2048];
    const char *term = getenv("TERM");
    if (!term)
        return fprintf(stderr, "TERM non défini\n"), 1;

    if (tgetent(termbuf, term) != 1)
        return fprintf(stderr, "Impossible de charger termcap\n"), 1;

    int rows = tgetnum("li");      // nombre de lignes
    int cols = tgetnum("co");      // colonnes

    if (rows == -1 || cols == -1)
        return fprintf(stderr, "Capacités li/co indisponibles\n"), 1;

    printf("Terminal: %d lignes x %d colonnes\n", rows, cols);
    return 0;
}
```
Après avoir chargé la description du terminal, tgetnum("li") et tgetnum("co") donnent ses dimensions déclarées, utiles pour positionner proprement un affichage plein écran.

### tgetstr : 
tgetstr(const char *id, char **area) récupère dans la base termcap déjà chargée (via tgetent) la séquence de contrôle chaîne associée à l’identifiant id (ex. cl = clear screen, ce = clear to end of line, cm = cursor motion).

Si area n’est pas NULL, tgetstr y copie la chaîne (avec \0) et avance le pointeur pour la prochaine capacité.
Si area == NULL, elle renvoie un pointeur vers une zone statique interne (plus simple mais pas thread-safe).
Retourne NULL si la capacité n’existe pas.

**Exemple complet avec TGOTO/Tputs pour effacer l’écran et placer le curseur :**
```c
int main(void)
{
    char termbuf[2048];
    const char *term = getenv("TERM");
    if (!term || tgetent(termbuf, term) != 1)
        return fprintf(stderr, "Termcap introuvable\n"), 1;

    char *area = termbuf; // réutilise le buffer pour stocker les strings
    char *clear = tgetstr("cl", &area); // efface l’écran
    char *cm = tgetstr("cm", &area);    // déplacement curseur

    if (!clear || !cm)
        return fprintf(stderr, "Capacités cl/cm manquantes\n"), 1;

    tputs(clear, 1, putchar);             // efface l’écran via tputs
    tputs(tgoto(cm, 10, 5), 1, putchar);  // curseur colonne 10, ligne 5
    puts("Hello termcap!");
    return 0;
}
```
Workflow typique minishell : tgetent → tgetstr/tgetnum/tgetflag pour récupérer les séquences, tgoto pour paramétrer les mouvements (cm), puis tputs pour les envoyer au terminal.

### tgoto : 
tgoto(const char *cm, int col, int row) formate une séquence de déplacement de curseur à partir de la capacité cm récupérée via tgetstr("cm", …). Elle renvoie un pointeur vers une chaîne statique contenant la séquence d’échappement complète qui positionne le curseur à la colonne col (x) et la ligne row (y). On passe ensuite cette chaîne à tputs pour l’envoyer proprement au terminal.

**Exemple :**
```c
static int putc_wrap(int c) { return putchar(c); }

int main(void)
{
    char buf[2048];
    const char *term = getenv("TERM");
    if (!term || tgetent(buf, term) != 1)
        return fprintf(stderr, "Termcap indisponible\n"), 1;

    char *cm = tgetstr("cm", NULL);   // séquence de déplacement
    char *cl = tgetstr("cl", NULL);   // effacer l’écran
    if (!cm || !cl)
        return fprintf(stderr, "Capacités cm/cl manquantes\n"), 1;

    tputs(cl, 1, putc_wrap);          // nettoie l’écran
    const char *move = tgoto(cm, 15, 3); // colonne 15, ligne 3
    tputs(move, 1, putc_wrap);        // déplace le curseur
    puts("Hello tgoto!");
    return 0;
}
```
Ici, tgoto paramètre la séquence cm pour aller en (x=15, y=3). tputs envoie la chaîne au terminal, qui place le curseur avant d’afficher le texte.

### tputs : 
tputs(const char *str, int affcnt, int (*putc_fn)(int)) envoie proprement une séquence de contrôle (souvent issue de Termcap) vers le terminal. Elle gère les délais éventuels indiqués dans la séquence et appelle putc_fn pour chaque caractère. affcnt indique combien de lignes seront affectées (utile pour certains délais dépendant du nombre de lignes, généralement 1). Retourne 0 si tout se passe bien, ERR sinon.

**Exemple d’effacement d’écran + positionnement :**
```c
static int putc_wrap(int c) { return putchar(c); }

int main(void)
{
    char termbuf[2048];
    const char *term = getenv("TERM");
    if (!term || tgetent(termbuf, term) != 1)
        return fprintf(stderr, "Termcap indisponible\n"), 1;

    char *clear = tgetstr("cl", NULL);  // effacer l'écran
    char *cm = tgetstr("cm", NULL);     // déplacement curseur
    if (!clear || !cm)
        return fprintf(stderr, "Capacités cl/cm manquantes\n"), 1;

    tputs(clear, 1, putc_wrap);         // nettoie l'écran
    tputs(tgoto(cm, 10, 5), 1, putc_wrap);  // place le curseur en (col=10, row=5)
    puts("Hello tputs!");
    return 0;
}
```
Workflow : tgetent charge le termcap, tgetstr fournit les séquences brutes (cl, cm), tgoto paramètre cm, et tputs écrit chaque séquence en utilisant putc_wrap (souvent putchar).

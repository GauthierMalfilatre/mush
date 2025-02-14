/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Pathfinding for commands
*/
#include "mysh.h"

static char *build_path(char *base_path, char *command)
{
    char *temp = my_stradd(base_path, "/");
    char *to_return = my_stradd(temp, command);

    free(temp);
    return to_return;
}

static int exists(char *path)
{
    struct stat stats;

    if (lstat(path, &stats) == -1) {
        return 0;
    }
    return 1;
}

void pathfinder(data_t *data, char *tampon, char *command)
{
    char *path;
    char **paths = (char **) 0;
    char *to_return = (char *) 0;

    path = find_in_env(data->env, "PATH");
    if (!path)
        return;
    paths = my_strsplit(path, ':');
    for (int i = 0; paths && paths[i]; ++i) {
        to_return = build_path(paths[i], command);
        if (exists(to_return)) {
            my_strcpy(tampon, to_return);
            ifree(to_return);
            break;
        }
        free(to_return);
    }
    my_free_word_array(paths);
    free(path);
    return;
}

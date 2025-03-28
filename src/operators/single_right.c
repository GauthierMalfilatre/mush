/*
** EPITECH PROJECT, 2025
** MYSH
** File description:
** Error handling
*/
#include "mysh.h"


static int is_op(char *word)
{
    char *ops[] = {"<", "<<", ">", ">>"};

    for (int i = 0; i < 4; i++) {
        if (!my_strcmp(word, ops[i])) {
            return 1;
        }
    }
    return 0;
}

static int determine_flags(char *op)
{
    int flags = O_RDWR | O_CREAT;

    if (!my_strcmp(op, ">")) {
        flags |= O_TRUNC;
    } else if (!my_strcmp(op, ">>")) {
        flags |= O_APPEND;
    }
    return flags;
}

static int which_file(char *op)
{
    if (!my_strcmp(op, ">") || !my_strcmp(op, ">>")) {
        return STDOUT_FILENO;
    }
    if (!my_strcmp(op, "<") || !my_strcmp(op, "<<")) {
        return STDIN_FILENO;
    }
    return 0;
}

int *get_fds(char **line)
{
    int *fd = malloc(sizeof(int) * (MAXPIPE + 1));
    int index = 0;
    int flags = 0;

    fd[MAXPIPE] = 0;
    for (int i = 0; i < MAXPIPE; i++) {
        fd[i] = 0;
    }
    for (int i = 0; line[i]; i++) {
        if (is_op(line[i]) && line[i + 1]) {
            flags = determine_flags(line[i]);
            fd[index] = open(line[i + 1], flags, 0666);
            dup2(fd[index], which_file(line[i]));
            index++;
        }
    }
    return fd;
}

int is_single_right(char **line)
{
    int fd;

    if (!line[1] || !line[2] || my_strcmp(line[1], ">")) {
        return 0;
    }
    fd = open(line[2], O_TRUNC | O_WRONLY | O_CREAT, 0666);
    dup2(fd, STDOUT_FILENO);
    return fd;
}

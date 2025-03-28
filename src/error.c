/*
** EPITECH PROJECT, 2025
** MYSH
** File description:
** Error handling
*/
#include "mysh.h"

int is_line_empty(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
            return 1;
        }
    }
    return 0;
}

int handle_signal(int exitstatus)
{
    int signal = WTERMSIG(exitstatus);

    if (signal == SIGSEGV) {
        mini_fprintf(2, "Segmentation fault");
        if (WCOREDUMP(exitstatus)) {
            mini_fprintf(2, " (core dumped)");
        }
        mini_fprintf(2, "\n");
        return 139;
    }
    return WEXITSTATUS(exitstatus);
}

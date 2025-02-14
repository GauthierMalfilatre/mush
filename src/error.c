/*
** EPITECH PROJECT, 2025
** MYSH
** File description:
** Error handling
*/
#include "mysh.h"

void handle_signal(int exitstatus)
{
    int signal = WTERMSIG(exitstatus);

    if (signal == SIGSEGV) {
        mini_fprintf(2, "Segmentation fault");
        if (WCOREDUMP(exitstatus)) {
            mini_fprintf(2, " (core dumped)");
        }
        mini_fprintf(2, "\n");
    }
}

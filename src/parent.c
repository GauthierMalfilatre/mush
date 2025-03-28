/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Process when it's on clock.
*/
#include "mysh.h"

void process_parent(data_t *data, int is_pipe, int *exitstatus, int pid)
{
    if (is_pipe) {
        close(data->pipefd[data->current_pipefd][1]);
        if (data->current_pipefd > 0) {
            close(data->pipefd[data->current_pipefd - 1][0]);
        }
        data->pids[data->current_pipefd] = pid;
    } else {
        waitpid(pid, exitstatus, 0);
        data->last_code = handle_signal(*exitstatus);
    }
}

// TODO : PIPE WHEN INTERCEPT, and ulimit -n gestion.

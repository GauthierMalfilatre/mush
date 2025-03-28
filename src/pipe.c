/*
** EPITECH PROJECT, 2025
** MYSH
** File description:
** Different piping
*/
#include "mysh.h"

void pipe_before(data_t *data)
{
    close(data->pipefd[data->current_pipefd][0]);
    dup2(data->pipefd[data->current_pipefd][1], 1);
    close(data->pipefd[data->current_pipefd][1]);
}

void pipe_after(data_t *data)
{
    close(data->pipefd[data->current_pipefd - 1][1]);
    dup2(data->pipefd[data->current_pipefd - 1][0], 0);
    close(data->pipefd[data->current_pipefd - 1][0]);
}

int my_len_word_array2(char **array)
{
    int count = 0;

    for (int i = 0; array[i]; i++) {
        if (is_line_empty(array[i])) {
            count++;
        }
    }
    return count;
}

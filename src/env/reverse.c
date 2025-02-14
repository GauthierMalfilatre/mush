/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Find a value in env
*/
#include "mysh.h"

void reverse_env(env_t **head)
{
    env_t *temp = (env_t *) 0;
    env_t *current = *head;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp) {
        *head = temp->prev;
    }
}

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

static int count_without_operators(char **warray)
{
    int length = 0;

    for (int i = 0; warray[i]; i++) {
        if (is_op(warray[i]) || (i > 1 && is_op(warray[i - 1]))) {
            continue;
        }
        length++;
    }
    return length;
}

char **special_dup_warray(char **warray)
{
    int expected_length = count_without_operators(warray);
    char **new_array = malloc(sizeof(char *) * (expected_length + 1));
    int offset_of_new = 0;

    new_array[expected_length] = (char *) 0;
    for (int i = 0; warray[i]; i++) {
        if (is_op(warray[i]) || (i > 1 && is_op(warray[i - 1]))) {
            continue;
        }
        new_array[offset_of_new] = my_strdup(warray[i]);
        offset_of_new++;
    }
    return new_array;
}

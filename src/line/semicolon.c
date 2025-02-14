/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Parse line -> semicolon
*/
#include "mysh.h"

char **get_until_semicolon(char **base)
{
    int len = 0;
    char **splited = (char **) 0;

    for (; len[base] && my_strcmp(len[base], ";"); ++len);
    splited = my_ndup_word_array(base, len);
    return splited;
}

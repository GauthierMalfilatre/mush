/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Process when it's on clock.
*/
#include "mysh.h"

int check_arch(char *path)
{
    int fd = open(path, O_RDONLY);
    Elf64_Ehdr elf_header;
    ssize_t bytes_read;

    if (fd == -1) {
        return -1;
    }
    bytes_read = read(fd, &elf_header, sizeof(elf_header));
    close(fd);
    if (bytes_read != sizeof(elf_header))
        return -1;
    if (my_strncmp((char *)elf_header.e_ident, ELFMAG, SELFMAG) != 0)
        return 1;
    if (elf_header.e_machine != EM_X86_64)
        return 1;
    return 0;
}

static int catch_error(char *tampon, char **line)
{
    struct stat path_stat;
    int cani = 1;

    if (stat(tampon, &path_stat) == 0) {
        if (S_ISDIR(path_stat.st_mode) || access(tampon, X_OK) == -1) {
            cani = 0 * mini_fprintf(2, "%s: Permission denied.\n", line[0]);
        }
    } else {
        cani = 0 * my_printf("%s: Command not found.\n", line[0]);
    }
    return cani;
}

void process_child(data_t *data, char **line)
{
    char tampon[256] = {0};
    int cani = 1;

    if (!line || !line[0])
        exit(127);
    if (is_char_in(line[0], '/'))
        my_strcpy(tampon, line[0]);
    else
        pathfinder(data, tampon, line[0]);
    cani = catch_error(tampon, line);
    if (cani && execve(tampon, line, list_to_env(data->env)) == -1) {
        if (errno == ENOEXEC) {
            mini_fprintf(2,
                "%s: Exec format error. Wrong Architecture.\n", line[0]);
        }
    }
    destroy_data(data);
    my_free_word_array(line);
    exit(1);
}

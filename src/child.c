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
    if (cani && check_arch(tampon) != 0) {
        cani = 0 * mini_fprintf(2,
            "%s: Exec format error. Binary file not executable.\n", line[0]);
    }
    return cani;
}

// Think to optimize the method
static void exec_it(char *tampon, char **line, char **env)
{
    int *fd = get_fds(line);
    char **temp;

    if (fd && fd[0]) {
        temp = special_dup_warray(line);
    }
    execve(tampon, fd[0] ? temp : line, env);
    for (int i = 0; i < MAXPIPE; i++) {
        ifree(temp);
        close(fd[i]);
    }
    return;
}

void process_child(data_t *data, char **line, char **line2, int is_pipe)
{
    char tampon[256] = {0};

    if (!line || !line[0])
        exit(127);
    if (is_char_in(line[0], '/'))
        my_strcpy(tampon, line[0]);
    else
        pathfinder(data, tampon, line[0]);
    if (catch_error(tampon, line)) {
        if (is_pipe == BEFORE || is_pipe == BETWEEN)
            pipe_before(data);
        if (is_pipe == AFTER || is_pipe == BETWEEN)
            pipe_after(data);
        exec_it(tampon, line, list_to_env(data->env));
    }
    destroy_data(data);
    my_free_word_array(line);
    my_free_word_array(line2);
    exit(1);
}

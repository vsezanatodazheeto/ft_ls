#ifndef FT_LS_H
# define FT_LS_H

/* nashi */
#include <inttypes.h>
#include "../lib/include/libft.h"
#include "../lib/include/get_next_line.h"
#include "../lib/include/ft_printf.h"

#include "unistd.h"
// ◦ write

#include <dirent.h>
// ◦ opendir
// ◦ readdir
// ◦ closedir

#include <sys/stat.h>
// ◦ stat
// ◦ lstat

#include <sys/types.h>
#include <pwd.h>
// #include <uuid/uuid.h>
// ◦ getpwuid // получают запись из файла паролей

#include <grp.h>
// #include <uuid/uuid.h>
// ◦ getgrgid // получает записи файла групп

#include <sys/xattr.h>
// ◦ listxattr // выводит список названий расширенных атрибутов  
// ◦ getxattr // получает расширенное значение атрибутов

#include <time.h>
// ◦ time
// ◦ ctime

#include "unistd.h"
// ◦ readlink

#include <stdlib.h>
// ◦ malloc
// ◦ free

#include <stdio.h>
// ◦ perror

#include <string.h>
// ◦ strerror

#include <stdlib.h>
// ◦ exit

# define CH_FLAG '-'

// тип флага
// A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z.
typedef enum		t_flags
{
	fl_noex = -1,
	fl_a,
	fl_l,
	fl_r,
	fl_t,
	fl_R
}					e_flags;

// type of (dir or file)
typedef enum		t_type
{
	t_dir,
	t_fol
}					e_type;

// информация об аргументе программы
typedef struct		s_args
{
	char			*name;
	struct stat 	stat;
	e_type			t_type;
	struct s_args	*next;
}					t_args;

// основная хуйня
typedef struct		s_main
{
	uint32_t		flag;
	t_args			*args;
}					t_main;

/* PARSER */
void		parse_args(t_main *st, int ac, char *av[]);
int32_t		update_flags(const int8_t shift);

/* LIB PARSER */
char		***av_split(int ac, char *av[]);
void		av_free(char ***splited_av);
void		av_print(char ***splited_av);

/* TRASH */
void printFileProperties(struct stat stats);

#endif
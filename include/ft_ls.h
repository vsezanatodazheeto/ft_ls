#ifndef FT_LS_H
# define FT_LS_H

/* nashi */
#include <inttypes.h>
#include "../lib/include/libft.h"
#include "../lib/include/get_next_line.h"
#include "../lib/include/ft_printf.h"
#include <limits.h>

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
// ◦ getpwuid // получают запись из файла паролей

#include <grp.h>
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
# define CH_SLASH '/'
# define S_SLASH "/"

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

// type of file (dir or reg_file)
typedef enum		t_type
{
	t_dir,
	t_fl
}					e_type;

typedef enum		t_err_file
{
	fe_noer,		//no errors
	fe_noex,		// file doesn't exist
	fe_nopr			// no permissions
}					e_err_file;

// основная хуйня 2.0.
typedef struct		s_file
{
	char			*name;
	struct stat 	stat;
	e_err_file		fe_err;
	struct s_file	*next;
}					t_file;

void        ft_ls(t_file *args, char *path);
/* PARSER */
t_file		*parse_args(int ac, char *av[]);
int32_t		update_flags(const int8_t shift);
void		add_file(t_file **fls);
t_file		*create_file(void);

/* LIB PARSER */
char		***av_split(int ac, char *av[]);
void		av_free(char ***splited_av);
void		av_print(char ***splited_av);

/* TRASH */
void printFileProperties(struct stat stats);

#endif
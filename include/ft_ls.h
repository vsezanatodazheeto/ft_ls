#ifndef FT_LS_H
# define FT_LS_H

/*
** PATH_MAX, NAME_MAX
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#if defined(__linux__)
	#include <linux/limits.h>
#elif defined(__APPLE__)
	#include <limits.h>
#endif

/* nashi */
#include <inttypes.h>
#include "ft_ls_err.h"
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

# define D_CURR "."
# define D_BACK ".."

# define ERR_MSG_OPD_NOEX "could not open dir\n"
# define ERR_OPD_NOEX ({ft_fprintf(2, ERR_MSG_OPD_NOEX); return;})
// # define ERROR_EXIT do{MSG1;finish(0);}while(0)
// # define WRONG_SIZE ({MSG2;return;})
// # define NO_ARG do{MSG3;exit(0);}while(0)

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

typedef struct		s_format_output
{
	uint64_t		s_links;
	uint64_t		s_user;
	uint64_t		s_group;
	uint64_t		s_size;
}					t_format_output;

/* MAIN FUCTIONS */
void        ft_ls(t_file *args, char *path);

/* SORT OF LINKED LIST BY FLAGS */
t_file* merge_Sort(t_file* head);

/* FORMAT OUTPUT */
void				format_print_files(t_file *fls, uint64_t total);
t_format_output		*format_output_set(const struct stat *stat);

/* PARSER */
t_file		*parse_args(int ac, char *av[]);
int32_t		update_flags(const int8_t shift);
void		add_file(t_file **fls);
t_file		*create_file(void);

/* T_FILE FUNC */
void		file_add(t_file **fls);
void		file_list_free(t_file **head);

/* LIB PARSER */
char		***av_split(int ac, char *av[]);
void		av_free(char ***splited_av);
void		av_print(char ***splited_av);

/* TRASH */
void printFileProperties(struct stat stats);

#endif

// chgrp - изменить группу для файлов или директорий
// chown - владелец
#ifndef FT_LS_H
# define FT_LS_H

#if defined(__linux__)
	#include <linux/limits.h>
#elif defined(__APPLE__)
	#include <limits.h>
#endif

/* nashi */
#include <inttypes.h>
#include "ft_ls_flags.h"
#include "ft_ls_err.h"
#include "../lib/include/libft.h"
#include "../lib/include/get_next_line.h"
#include "../lib/include/ft_printf.h"

#include "unistd.h"
#include <time.h>
#include <stdlib.h>
#include <stdlib.h>

/*
** opendir, readdir, closedir
*/
#include <dirent.h>

/*
** stat, lstat
*/
#include <sys/stat.h>

/*
** getpwuid - users
*/
#include <sys/types.h>
#include <pwd.h>

/*
** getgrgid - groups
*/
#include <grp.h>

// ◦ listxattr // выводит список названий расширенных атрибутов  
// ◦ getxattr // получает расширенное значение атрибутов
#include <sys/xattr.h>

/*
** for format output [-l] flag, types of max lengths of:
** 
** link (num)
** user (str)
** group (str)
** size (num)
*/
typedef enum		e_format_type_attb
{
	fta_l,
	fta_u,
	fta_g,
	fta_s
}					t_format_type_attb;

/*
** for format output [-l] flag, max lengths of attributes from struct stat:
*/
typedef struct		s_format_out
{
	int32_t			s_links;
	int32_t			s_user;
	int32_t			s_group;
	int32_t			s_size;
}					t_format_out;

/*
** for t_file struct:
** is file exist
*/
typedef enum		e_file_exist
{
	fi_def,
	fi_noex,
}					t_file_exist;

/*
** main stuff
*/
typedef struct		s_file
{
	char			*name;
	struct stat 	stat;
	t_file_exist	is_ex;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

/* MAIN FUCTIONS */
void        		ft_ls(t_file *args, char *path);

/* SORT OF LINKED LIST BY FLAGS */
void				merge_Sort2(t_file **head);

/* FORMAT OUTPUT */
t_format_out		*set_format_attb(const struct stat *stat);
void				format_output_print(t_file *fls, uint64_t total);
void				format_file_print(t_file *fls);

/* PARSER */
t_file				*parse_args(int ac, char *av[]);
void				add_file(t_file **fls);
t_file				*create_file(void);

/* T_FILE FUNC */
void				file_add(t_file **fls);
void				file_list_free(t_file **head);

/* LIB PARSER */
char				***av_split(int ac, char *av[]);
void				av_free(char ***splited_av);
void				av_print(char ***splited_av);

#endif

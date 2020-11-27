#ifndef FT_LS_H
# define FT_LS_H

#if defined(__linux__)
	#include <linux/limits.h>
#elif defined(__APPLE__)
	#include <limits.h>
#endif

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdlib.h>

/*
** lib
*/
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "av_parse.h"

#include "ft_ls_flags.h"
#include "ft_ls_err.h"

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
** for format output [-l] flag, max lengths of cells from system struct stat:
*/
typedef struct		s_cells_len
{
	int32_t			l_links;
	int32_t			l_user;
	int32_t			l_group;
	int32_t			l_size;
}					t_cells_len;

/*
** main stuff
*/
typedef struct		s_file
{
	char			*name;
	struct stat 	stat;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

/* MAIN FUCTIONS */
void        		ft_ls(t_file *args, char *path);

/* PARSER */
t_file				*parse_args(int ac, char *av[]);
void				add_file(t_file **fls);
t_file				*create_file(void);

/* T_FILE FUNC */
void				file_add(t_file **fls);
void				file_list_free(t_file **head);

/* SORT OF LINKED LIST BY FLAGS */
void				merge_sort(t_file **head);
void				ftype_merge_sort(t_file **head);

/* FORMAT OUTPUT */
void				format_output_print(t_file *fls, uint64_t total);
void				format_file_print(t_file *fls);

/* FORMAT OUTPUT ROWS LENGTH */
t_cells_len			*update_stat_cells_len(const struct stat *stats);
int32_t				get_stat_cell_len(t_format_type_attb attb);
void				reset_stat_cells_len(void);

#endif

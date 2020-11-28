/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshawn <yshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:18:12 by yshawn            #+#    #+#             */
/*   Updated: 2020/11/28 23:29:23 by yshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# if defined(__linux__)
#  include <linux/limits.h>
# elif defined(__APPLE__)
#  include <limits.h>
# endif

# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <stdlib.h>

/*
** lib
*/
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "av_parse.h"

# include "ft_ls_flags.h"
# include "ft_ls_err.h"

/*
** opendir, readdir, closedir
*/
# include <dirent.h>

/*
** stat, lstat
*/
# include <sys/stat.h>

/*
** getpwuid - users
*/
# include <sys/types.h>
# include <pwd.h>

/*
** getgrgid - groups
*/
# include <grp.h>

# define SIX_MONTH 15768000

# define D_CURR "."
# define D_PREV ".."

# define CH_DOT '.'
# define CH_FLAG '-'
# define S_SLASH "/"

/*
** for format output [-l] flag, types of max lengths of:
**
** link (num)
** user (str)
** group (str)
** size (num)
*/
typedef enum		e_flags_cells
{
	fta_l,
	fta_u,
	fta_g,
	fta_s,
	fta_t
}					t_flags_cells;

/*
** for format output [-l] flag, max lengths of cells from system struct stat:
*/
typedef struct		s_cells_len
{
	int32_t			l_links;
	int32_t			l_user;
	int32_t			l_group;
	int32_t			l_size;
	int32_t			l_time;
}					t_cells_len;

/*
** main stuff
*/
typedef struct		s_file
{
	char			*name;
	struct stat		stat;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

/*
** MAIN FUCTIONS
*/
void				ls_base(t_file *fls, char *path);
void				ls(t_file *d_fl, char *old_path);

/*
** PARSER
*/
t_file				*parse_args(int ac, char *argv[]);
t_file				*update_files(char **splited_av);
char				**parse_check_flags(char *av[]);

/*
** T_FILE FUNC
*/
void				file_add(t_file **fls);
void				file_list_free(t_file **head);

/*
** SORT OF LINKED LIST BY FLAGS
*/
void				merge_sort(t_file **head);
int					asc_sort(t_file *f1, t_file *f2);
int					desc_sort(t_file *f1, t_file *f2);
int					time_sort(t_file *f1, t_file *f2);
int					first_sort(t_file *f1, t_file *f2);
void				ftype_merge_sort(t_file **head);

/*
** FORMAT OUTPUT
*/
void				format_output_print(t_file *fls, uint64_t total, \
										const char *path);
void				format_file_print(t_file *fls, const char *path);

/*
** FORMAT OUTPUT CELLS LENGTH
*/
t_cells_len			*update_stat_cells_len(const struct stat *stats);
int32_t				get_stat_cell_len(t_flags_cells flag_cell);
void				reset_stat_cells_len(void);
void				set_fullpath_tofile(char *fullpath, const char *path, \
										const char *fl_name);

#endif

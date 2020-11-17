#ifndef FT_LS_H
# define FT_LS_H

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
#include <uuid/uuid.h>
// ◦ getpwuid // получают запись из файла паролей

#include <grp.h>
#include <uuid/uuid.h>
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

static int flag = 0;
// тип флага
typedef enum		t_flags
{
	l,
	r,
	a,
	t,
	R
}					e_flags;

// информация о файле/директории
typedef struct		s_args
{
	char			*name;
	struct stat 	stat;
	struct s_list	*next;
}					t_args;

// основная хуйня
typedef struct		my_struct
{
	int				ac;
	char			**av;
	int				flag;
	e_flags			options;
	t_list			args;
}					t_struct;

#endif
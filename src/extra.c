#include "ft_ls.h"

void			file_list_free(t_file **head)
{
	t_file		*curr;

	if (!head)
		return ;
	while (*head)
	{
		curr = *head;
		*head = (*head)->next;
		free(curr->name);
		free(curr);
		curr = NULL;
	}
}

static t_file	*file_create(void)
{
	t_file		*fl;

	fl = (t_file *)malloc(sizeof(t_file));
	if (!fl)
		exit(1);
	fl->name = NULL;
	fl->fe_err = fe_noer;
	fl->next = NULL;
	return (fl);
}

void			file_add(t_file **fls)
{
	t_file		*new_fl;

	new_fl = file_create();
	if (*fls)
		new_fl->next = *fls;
	*fls = new_fl;
}

// struct stat {
//     dev_t         st_dev;      /* устройство */
//     ino_t         st_ino;      /* inode */
//     mode_t        st_mode;     /* режим доступа */
//     nlink_t       st_nlink;    /* количество жестких ссылок */
//     uid_t         st_uid;      /* идентификатор пользователя-владельца */
//     gid_t         st_gid;      /* идентификатор группы-владельца */
//     dev_t         st_rdev;     /* тип устройства */
//                                /* (если это устройство) */
//     off_t         st_size;     /* общий размер в байтах */
//     blksize_t     st_blksize;  /* размер блока ввода-вывода */
//                                /* в файловой системе */
//     blkcnt_t      st_blocks;   /* количество выделенных блоков */
//     time_t        st_atime;    /* время последнего доступа */
//     time_t        st_mtime;    /* время последней модификации */
//     time_t        st_ctime;    /* время последнего изменения */
// };

/**
 * Function to print file properties.
 */
// void printFileProperties(struct stat stats)
// {
//     struct tm dt;

//     // File permissions
//     printf("\nFile access: ");
//     if (stats.st_mode & R_OK)
//         printf("read ");
//     if (stats.st_mode & W_OK)
//         printf("write ");
//     if (stats.st_mode & X_OK)
//         printf("execute");

//     // File size
//     printf("\nFile size: %ld", stats.st_size);

//     // Get file creation time in seconds and 
//     // convert seconds to date and time format
//     dt = *(gmtime(&stats.st_ctime));
//     printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
//                                               dt.tm_hour, dt.tm_min, dt.tm_sec);

//     // File modification time
//     dt = *(gmtime(&stats.st_mtime));
//     printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
//                                               dt.tm_hour, dt.tm_min, dt.tm_sec);

// }
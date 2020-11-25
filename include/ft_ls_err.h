#ifndef FT_LS_ERR_H
# define FT_LS_ERR_H

/*
** perror
*/
# include <stdio.h>

/*
** strerror
*/
# include <string.h>

# define CH_DOT '.'
# define CH_FLAG '-'
# define CH_SLASH '/'
# define S_SLASH "/"

# define D_CURR "."
# define D_BACK ".."

# define EMSG_LSFLAG "ft_ls: illegal option: -"
# define ERR_LSFLAG_EXTRA(flag) ({ft_fprintf(2, "%s%c\n", EMSG_LSFLAG, flag);})
# define ERR_LSFLAG(flag)({ERR_LSFLAG_EXTRA(flag); exit(3);})

# define EMSG_OPEND "ft_ls: "
# define ERR_OPEND(f_name)({ft_fprintf(2, EMSG_OPEND); perror(f_name); return;})

# define EMSG_STATF "ft_ls: "
# define ERR_STATF(f_name)({ft_fprintf(2, EMSG_STATF); perror(f_name);})

# define EMSG_STRDUP "ft_strdup"
# define ERR_STRDUP ({perror(EMSG_STRDUP); exit(4);})

# define EMSG_AVSPLIT "av_split"
# define ERR_AVSPLIT ({perror(EMSG_AVSPLIT); exit(5);})

# define EMSG_FCREATE "file_create"
# define ERR_FCREATE ({perror(EMSG_AVSPLIT); exit(10);})

#endif

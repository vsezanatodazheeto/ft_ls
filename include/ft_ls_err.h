#ifndef FT_LS_ERR_H
# define FT_LS_ERR_H

#include <stdio.h>
// ◦ perror
#include <string.h>
// ◦ strerror

# define CH_FLAG '-'
# define CH_SLASH '/'
# define S_SLASH "/"

# define D_CURR "."
# define D_BACK ".."


# define EMSG_OPD_NOEX "could not open dir\n"
# define ERR_OPD ({ft_fprintf(2, EMSG_OPD_NOEX); return;})

# define EMSG_STRDUP "ft_strdup"
# define ERR_STRDUP ({perror(EMSG_STRDUP); exit(4);})

# define EMSG_AVSPLIT "av_split"
# define ERR_AVSPLIT ({perror(EMSG_AVSPLIT); exit(5);})

# define EMSG_FCREATE "file_create"
# define ERR_FCREATE ({perror(EMSG_AVSPLIT); exit(10);})

#endif

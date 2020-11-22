#ifndef FT_LS_ERR_H
# define FT_LS_ERR_H

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

#endif
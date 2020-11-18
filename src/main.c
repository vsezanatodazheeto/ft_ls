#include "ft_ls.h"

void		parse_set_flags(char *av)
{
	ft_printf("{red}av: %s\n{eoc}", av);
}

static void	parse_check_flags(char ***splited_av)
{
	int32_t	i;
	int32_t	j;
	uint8_t is_flags_end;

	i = 0;
	j = 0;
	is_flags_end = 0;
	while (splited_av[i] && !is_flags_end)
	{
		while (splited_av[i][j] && !is_flags_end)
		{
			if (splited_av[i][j][0] == CH_FLAG)
				parse_set_flags(splited_av[i][j]);
			else
				is_flags_end = 1;
			j++;
		}
		i++;
	}
}

void        parse_args(t_struct *st, int ac, char *av[])
{
	char	***splited_av;

	splited_av = av_split(ac, av);
	if (!splited_av)
		exit (1);
	parse_check_flags(splited_av);
	// av_print(splited_av);

	av_free(splited_av);
}

int			main(int ac, char *av[])
{
	t_struct	st[1];

	ft_bzero(st, sizeof(st));
    parse_args(st, ac, av);



	// struct stat stats;
	// char *path = ".";
	// char kek[1024];


	// DIR *dir;
    // struct dirent *entry;

    // dir = opendir(path);
    // if (!dir) {
    //     perror("diropen");
    //     exit(1);
    // };
    // while ( (entry = readdir(dir)) != NULL) {
    //     printf("%lld - %s [%d] %d\n",
    //         entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
    // };
    // closedir(dir);

	// stat(path, &stats);
	// if (stat(path, &stats) == 0)
    // {
    //     printFileProperties(stats);
    // }
    // else
    // {
    //     printf("Unable to get file properties.\n");
    //     printf("Please check whether '%s' file exists.\n", path);
    // }
	return (0);
}

// void				parse(t_frame *frame)
// {
// 	get_args(frame);
// 	get_options(frame);
// 	config_options(frame);
// }





// 9:59
// #include "ft_ls.h"
// static void			parse_options(t_frame *frame, int option)
// {
// 	char			**argv;
// 	char			**argv_options;
// 	if (!option)
// 		return ;
// 	if (!(frame->argv_options = (char **)malloc(sizeof(char *) * (option + 1))))
// 		error_exit(frame, "Malloc Failed");
// 	*frame->argv_options = *(frame->argv + 1);
// 	argv = frame->argv + 1;
// 	argv_options = frame->argv_options;
// 	while (*argv && **argv == '-' && argv[0][1])
// 	{
// 		*argv_options = *argv;
// 		argv++;
// 		argv_options++;
// 	}
// 	*argv_options = NULL;
// }
// static void			parse_args(t_frame *frame, char **argv)
// {
// 	t_args			*args;
// 	t_args			*last_args;
// 	if (*argv)
// 		argv++;
// 	if (!*argv)
// 	{
// 		if (!(frame->args = create_args()))
// 			error_exit(frame, "Malloc Failed");
// 		if (!(frame->args->data.str = ft_strdup("."))
// 				|| !(frame->args->data.path = ft_strdup(".")))
// 			error_exit(frame, "Malloc Failed");
// 	}
// 	while (*argv)
// 	{
// 		if (!(args = create_args()))
// 			error_exit(frame, "Malloc Failed");
// 		path(frame, args, ".", *argv);
// 		if (!frame->args)
// 			frame->args = args;
// 		else
// 			last_args->next = args;
// 		last_args = args;
// 		argv++;
// 	}
// }
// static int			calculate_option_strings(t_frame *frame)
// {
// 	char			**argv;
// 	int				option;
// 	option = 0;
// 	argv = frame->argv + 1;
// 	while (*argv && **argv == '-' && argv[0][1])
// 	{
// 		option++;
// 		argv++;
// 	}
// 	return (option);
// }
// void				get_args(t_frame *frame)
// {
// 	int	i;
	
// 	i = calculate_option_strings(frame);
// 	parse_options(frame, i);
// 	parse_args(frame, frame->argv + i);
// }
// 9:59
// #include "ft_ls.h"
// static void			print_bad_options(t_frame *frame)
// {
// 	int				i;
// 	int				fl;
// 	i = 0;
// 	fl = 0;
// 	while(i++ < 256)
// 	{
// 		if(frame->opt[i] && i != 'a' && i != 'l' && i != 'r' && i != 't' && i != 'R' && i != 'g' && i != 'o')
// 		{
// 			if (fl)
// 				write(2, "\n", 1);
// 			ft_putstr_fd("ft_ls: illegal option -- ", 2);
// 			write(2, &i, 1);
// 			fl = 1;
// 		}
// 	}
// // 	char			option_char;
// // 	unsigned long	one;
// // 	unsigned char	shifts;
// // 	char			correction;
// // 	one = 1;
// // 	shifts = 0;
// // 	ft_putstr_fd("ft_ls: illegal option -- ", 2);
// // 	while (shifts < 63)
// // 	{
// // 		correction = (shifts < 26) ? 97 : 39;
// // 		(shifts > 51) ? correction = -4 : 0;
// // 		(shifts > 62) ? correction = -30 : 0;
// // 		if (bad_options & one)
// // 		{
// // 			option_char = shifts + correction;
// // 			write(2, &option_char, 1);
// // 		}
// // 		shifts++;
// // 		bad_options >>= 1;
// // 	}
// 	if(fl)
// 	{
// 		ft_putstr_fd("\nusage: ./ft_ls [", 2);
// 		ft_putstr_fd(OPTIONS, 2);
// 		error_exit(frame, "] [file ...]");
// 	}
// }
// // static void			get_compliment_of_all_options(t_frame *frame,
// // 		unsigned long *compliment_of_all_options)
// // {
// // 	char			**all_options;
// // 	if (!(all_options = (char **)malloc(sizeof(char *) * 3)))
// // 		error_exit(frame, "Malloc Failed [all_options]");
// // 	all_options[0] = NULL;
// // 	all_options[2] = NULL;
// // 	if (!(all_options[1] = ft_strdup(OPTIONS)))
// // 	{
// // 		free(all_options);
// // 		error_exit(frame, "Malloc Failed [all_options]");
// // 	}
// // 	*compliment_of_all_options = ~options(all_options);
// // 	free(all_options[1]);
// // 	free(all_options);
// // }
// static void			options_error_check(t_frame *frame)
// {
// 	// char			**argv;
// 	// unsigned long	compliment_of_all_options;
// 	// argv = frame->argv;
// 	// get_compliment_of_all_options(frame, &compliment_of_all_options);
// 	// if (option_data &= compliment_of_all_options)
// 		print_bad_options(frame);
// }
// static void			fetch_options(t_frame *frame)
// {
// 	frame->option.a = frame->opt['a'];
// 	frame->option.l = frame->opt['l'];
// 	frame->option.r = frame->opt['r'];
// 	frame->option.t = frame->opt['t'];
// 	frame->option.up_r = frame->opt['R'];
// 	frame->option.o = frame->opt['o'];
// 	frame->option.g = frame->opt['g'];
// 	ft_printf("%d - opt a\n", frame->option.a);
// 	ft_printf("%d - opt l\n", frame->option.l);
// 	ft_printf("%d - opt r\n", frame->option.r);
// 	ft_printf("%d - opt t\n", frame->option.t);
// 	ft_printf("%d - opt R\n", frame->option.up_r);
// 	ft_printf("%d - opt o\n", frame->option.o);
// 	ft_printf("%d - opt g\n", frame->option.g);
// }
// void				get_options(t_frame *frame)
// {
// 	// unsigned long	option_data;
// 	char			**av;
	
// 	if (!frame->argv_options)
// 		return ;
// 	av = frame->argv_options;
// 	while(*av)
// 	{
// 		while(**av)
// 		{
// 			if(**av != '-')
// 				frame->opt[(int)**av] = 1;
// 			(*av)++;
// 		}
// 		av++;
// 	}
// 	// option_data = options(frame->argv_options);
// 	fetch_options(frame);
// 	options_error_check(frame);
// }
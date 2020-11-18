#include "ft_ls.h"

// вынести в библиотеку как мини парсер для аргументов из стандартного потока ввода

/*
** consider any cases:
** ./ft_ls -l -r ... args
** ./ft_ls "-l -r ...args"
** ./ft_ls "-l" ... "-r" ... "args_2"
*/

void		av_print(char ***splited_av)
{
	for (int j = 0; splited_av[j]; j++)
		for (int n = 0; splited_av[j][n]; n++)
			ft_printf("{green}%s\n{eoc}", splited_av[j][n]);
}

void		av_free(char ***splited_av)
{
	for (int32_t i = 0; splited_av[i]; i++)
		ft_arrdel((void ***)&splited_av[i]);
	free(splited_av);
}

char		***av_split(int ac, char *av[])
{
	int32_t	i;
	char	***splited_av;

	i = 0;
	{
		ac--;
		av++;
	}
	splited_av = (char ***)malloc(sizeof(char **) * (ac + 1));
	if (!splited_av)
		return (NULL);
	splited_av[ac] = NULL;
	while (i < ac)
	{
		splited_av[i] = ft_strsplit(av[i], ' ');
		if (!splited_av[i])
		{
			av_free(splited_av);
			return (NULL);
		}
		i++;
	}
	return (splited_av);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:37:30 by vludan            #+#    #+#             */
/*   Updated: 2018/10/19 13:38:04 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"

int			main(int argc, char **argv)
{
	int		funct;

	if (argc == 1)
		funct = ssl_get_input();
	else
	{
		funct = ssl_command_parse(argv, 0);
		ssl_flags_parse(argv, funct);
	}
	return (0);
}

int			ssl_command_parse(char **argv, char *line)
{
	int 	x;
	char	*temp;

	x = 0;
	while (line && line[x] == ' ')
		x++;
	temp = (!line ? argv[2] : line + x);
	//strcmp for line "md5 -r" ????
	if (!ft_strcmp(temp, "md5"))
		return (1);
	else if (!ft_strcmp(temp, "sha256"))
		return (2);
	else if (!ft_strcmp(temp, "sha512"))
		return (3);
	else if (!ft_strcmp(temp, "q"))
		return (4);
	else
		return (0);
}

int			ssl_flags_parse(int argc, char **argv, int funct)
{
	char	*line;

	//line = ft_strchr(argv[3], '-');
	if (funct != 0 && funct != 4 && argc == 2)
	{
		while (get_next_line(0, &line) > 0 && ft_strlen(line))
			;
	}
	else if () 
		;
	else if (funct == 4)
		return (1);
	else
	{
		error_mgmnt();
		return (2);
	}
}

int			ssl_get_input(void)
{
	char	*line;
	int 	x;
	int 	res;

	line = 0;
	res = 0;
	while (!line && !res)
	{
		ft_printf("ft_ssl> ");
		if (get_next_line(1, &line) == -1)
			res = 4;
		else
			res = ssl_command_parse(0, line);
		free(line);
	}
	return (res);
}
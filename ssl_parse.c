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

#include "ft_ssl.h"
#include "libft/libft.h"

struct s_flg 	*flg;

int			main(int argc, char **argv)
{
	flg = ft_memalloc(sizeof(struct s_flg));
	if (argc == 1)
		ssl_alg(ssl_get_input(0));
	else
	{
		ssl_command_parse(argv, 0);
		ssl_command_toflags(argc, argv);
	}
	return (0);
}

int			ssl_command_parse(char **argv, char *line)
{
	int 	x;
	char	*temp;

	x = 0;
	if (flg->cmd)
		return (0);
	while (line && line[x] == ' ')
		x++;
	temp = (!line ? argv[1] : line + x);
	if (!ft_strcmp(temp, "md5"))
		flg->cmd = 1;
	else if (!ft_strcmp(temp, "sha256"))
		flg->cmd = 2;
	else if (!ft_strcmp(temp, "sha512"))
		flg->cmd = 3;
	else if (!ft_strcmp(temp, "q"))
		flg->cmd = 4;
	else
		flg->cmd = 0;
	return (0);
}

int			ssl_command_toflags(int argc, char **argv)
{
	char	*tmp;

	if (flg->cmd != 0 && flg->cmd != 4)
	{
		if (argc > 2)
			ssl_flags_parse(argc, argv);
		else
		{
		//printf("%s\n", "HY");
		tmp = ssl_fd_read(0);
		if (!tmp)
			tmp = ssl_fd_read(1);
		ssl_alg(tmp);
		}
		//ssl_get_input(1);
		return (0);
	}
	else if (flg->cmd == 4)
		return (1);
	else
	{
		//error_mgmnt();
		return (2);
	}
}

void		ssl_flags_parse(int argc, char **argv)
{
	int 	x;

	x = 2;
	while (x < argc)
	{
		if (!ft_strcmp(argv[x], "-p"))
		{
			flg->p = 1;
			ssl_alg(ssl_fd_read(0));
		}
		else if (!ft_strcmp(argv[x], "-q"))
			flg->q = 1;
		else if (!ft_strcmp(argv[x], "-r"))
			flg->r = 1;
		else if (!ft_strcmp(argv[x], "-s"))
		{
			flg->s = 1;
			ssl_alg(argv[++x]);
		}
		else
		{
			flg->files = 1;
			while (x < argc)
			{
				ssl_alg(ssl_fd_read(open(argv[x], O_RDONLY)));
				printf("%d\n", x);
				x++;
			}
			flg->files = 0;
		}
		x++;
	}
}

char		*ssl_fd_read(int fd)
{
	char	*line;
	char	*arr;
	char	*temp;
	int 	res;

	if (fd < 0)
	{
		printf("%s\n", "EROOR");
		return (0);
	}
	arr = 0;
	res = get_next_line(fd, &line);
	if (res > 0 && flg->cmd)
		arr = ft_memalloc(sizeof(struct s_flg) + 1);
	while (res > 0 && line && flg->cmd)
	{
		temp = ft_strjoin(arr, line);
		if (arr)
			free(arr);
		arr = temp;
		free(line);
		res = get_next_line(fd, &line);
		arr = ft_strjoin(temp, "\n"); //because gnl check line by \n
		free(temp);
		//printf("MY: %s\n", arr);
	}
	if (!res && !flg->p)
	{
		printf("%s\n", "here?");
		flg->cmd = 4;
	}
	if (!flg->cmd)
		ssl_command_parse(0, line);
	arr = (!arr ? line : arr);
	return (arr);
}

char		*ssl_get_input(int x)
{
	char	*line;
	int 	res;
	char 	*ret;

	line = 0;
	res = 0;
	printf("%d\n", flg->cmd);
	while (!line && !res && flg->cmd != 4)
	{
		if (x == 0)
			ft_printf("ft_ssl> ");
		line = ssl_fd_read(1);
		if (!line || flg->cmd == 4)
			res = 4;
		else
		{
			ssl_command_parse(0, line);
			if (flg->cmd == 0)
			{
				printf("%s\n", "INVALID command");
				line = 0; //error *line is invalid command
			}
			else
				ret = ssl_fd_read(1);
		}
		free(line);
	}
	return (ret);
}

void		ssl_alg(char *arr)
{
	if (!arr)
		return ;
	printf("%s\n", arr);
}
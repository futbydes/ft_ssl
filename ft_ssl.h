/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:39:25 by vludan            #+#    #+#             */
/*   Updated: 2018/10/22 11:40:37 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# define BUFF_SIZE 1000

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef struct		s_lst
{
	char			*buff;
	int				ds;
	struct s_lst	*next;
}					t_lst;

typedef struct 		s_flg
{
	char 			p;
	char			q;
	char			r;
	char			s;
	char			files;
	char			cmd;
}					t_flags;

#include <stdio.h>

int			ssl_command_parse(char **argv, char *line);
int			ssl_command_toflags(int argc, char **argv);
void		ssl_flags_parse(int argc, char **argv);
char		*ssl_fd_read(int fd);
char		*ssl_get_input(int x);
void		ssl_alg(char *arr);
int			get_next_line(const int fd, char **line);


#endif

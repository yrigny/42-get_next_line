/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:01:14 by yrigny            #+#    #+#             */
/*   Updated: 2023/12/04 16:01:16 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	char	*line = NULL;
	
	if (argc < 2)
		return (0);
	int	fd1 = open(argv[1], O_RDONLY);
	int	fd2 = open(argv[2], O_RDONLY);
	int	fd3 = open(argv[3], O_RDONLY);
	for (int i = 0; i < 5; i++)
	{
		line = get_next_line(fd1);
		printf("fd1 - call %d: %s\n", i + 1, line);
		free(line);

		line = get_next_line(fd2);
		printf("fd2 - call %d: %s\n", i + 1, line);
		free(line);

		line = get_next_line(fd3);
		printf("fd3 - call %d: %s\n", i + 1, line);
		free(line);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

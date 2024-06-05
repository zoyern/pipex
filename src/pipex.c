/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:40:22 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex/all.h>
#include <sotypes/soprintf.h>

int	solib_pipex_openfd(char *path_in, char *path_out, int *in, int *out)
{
	*in = open(path_in, O_RDONLY, 0644);
	if (*in < 0)
	{
		perror("Open");
		*in = open("/dev/null", O_RDONLY, 0644);
		if (*in < 0)
			return (1);
	}
	*out = open(path_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out < 0)
		return (1);
	return (0);
}

int	pipex(t_solib *solib, char *infile, char **commands, char *outfile)
{
	int	fdin;
	int	fdout;

	fdin = 0;
	fdout = 0;
	if (solib_pipex_openfd(infile, outfile, &fdin, &fdout))
		return (perror("Open"), 1);
	return (strs_exec(solib, fdin, commands, fdout));
}

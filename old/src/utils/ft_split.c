/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:34:38 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	get_count_word(char const *str, char c)
{
	int	k;

	k = 0;
	while (*str)
	{
		if (str[0] != c && (str[1] == c || !str[1]))
			k++;
		str++;
	}
	return (k);
}

static int	get_word_len(char const *str, char c)
{
	int	k;

	k = 0;
	while (str[k] && str[k] != c)
		k++;
	return (k);
}

static int	free_all(t_solib *solib, char **array)
{
	int	k;

	k = 0;
	while (array[k])
		solib->free(solib, array[k++]);
	solib->free(solib, array);
	return (1);
}

char	**ft_split(t_solib *solib, char const *s, char c)
{
	char	**out;
	int		out_len;
	int		k;
	int		word_len;

	out_len = get_count_word(s, c);
	out = solib->malloc(solib, sizeof(char *) * (out_len + 1));
	if (!out)
		return (0);
	k = 0;
	while (k < out_len)
	{
		while (*s == c)
			s++;
		word_len = get_word_len(s, c);
		out[k] = ft_substr(solib, s, 0, word_len);
		if (!out[k] && free_all(solib, out))
			return (0);
		s += word_len;
		k++;
	}
	out[out_len] = 0;
	return (out);
}
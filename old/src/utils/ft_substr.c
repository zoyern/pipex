/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:41:23 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 17:41:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>


static size_t	min(size_t a, size_t b)
{
	return ((a <= b) * a + (a > b) * b);
}

static size_t	max(size_t a, size_t b)
{
	return ((a >= b) * a + (a < b) * b);
}

char	*ft_substr(t_solib *solib, char const *s, unsigned int start, size_t len)
{
	size_t	target_len;
	size_t	s_len;
	char	*out;
	size_t	k;

	s_len = ft_strlen(s);
	target_len = max(min(len, s_len - min(start, s_len)), 0);
	out = solib->malloc(solib, sizeof(char) * (target_len + 1));
	if (!out)
		return (0);
	k = -1;
	while (++k < target_len)
		out[k] = s[start + k];
	out[target_len] = 0;
	return (out);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:34:48 by marvin            #+#    #+#             */
/*   Updated: 2024/04/01 21:34:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <pipex.h>

unsigned long	ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_memalloc(size_t size);
char			*get_input();

t_solib			*sonew(void);
#endif

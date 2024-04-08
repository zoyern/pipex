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
char			*ft_strdup(t_solib *solib, const char *s);
char			*ft_strjoin(t_solib *solib, char const *s1, char const *s2);
void			*ft_memalloc(t_solib *solib, size_t size);
char			*get_input(t_solib *solib);
char			**ft_split(t_solib *solib, char const *s, char c);
t_solib			*sonew(int argc, char **argv, char **envp);
char			*ft_substr(t_solib *solib, char const *s, unsigned int start, size_t len);
void			ft_putstrs(char **strs);
void			ft_strmcat(t_solib *solib, char **dst, char *src);
char			*ft_itoa(t_solib *solib, int n);
#endif

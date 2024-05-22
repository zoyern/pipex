/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:36:54 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 02:36:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TYPE_H
# define TYPE_H

# define TRUE 1
# define FALSE 0
typedef int	t_bool;
typedef struct s_solib			t_solib;
typedef struct s_sofork_child	t_sofork_child;
typedef struct s_sofork_parent	t_sofork_parent;
typedef struct s_sofork_pid		t_sofork_pid;
typedef struct s_sopipe			t_sopipe;
typedef struct s_solib_memory	t_solib_memory;
typedef struct s_solib_new		t_solib_new;

#endif
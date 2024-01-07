/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlimous <chlimous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:20:37 by chlimous          #+#    #+#             */
/*   Updated: 2024/01/06 22:17:39 by chlimous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

// Server
void	clearstatic(t_advlist *advlst, unsigned char *c, int *received_bits);
char	*build_str(t_advlist *advlst);
void	add_to_list(t_advlist *advlst, char c);

#endif

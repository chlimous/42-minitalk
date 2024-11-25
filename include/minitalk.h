/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/16 15:20:37 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/11/25 02:44:19 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_current_char
{
	char	c;
	int		received_bits;
}	t_current_char;

typedef struct s_node
{
	char			c;
	struct s_node	*next;
}	t_node;

typedef struct s_buffer
{
	t_node					*head;
	t_node					*tail;
	size_t					size;
	struct s_current_char	current_char;
	pid_t					sender_pid;
}	t_buffer;

// Server
char	*buffer_to_string(t_buffer *buffer);
void	clear_buffer(t_buffer *buffer);
void	add_node(t_buffer *buffer, char c);

// Client
void	init_signal_client(struct sigaction *sig_hook, int sig, \
		void (*handler)(int));

#endif

/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/29 03:25:11 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/29 03:32:05 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "minitalk.h"

/******************************************************************************
 * @brief Initializes sigaction structure
 * 
******************************************************************************/
void	init_signal_client(struct sigaction *sig_hook, int sig, \
		void (*handler)(int))
{
	ft_bzero(sig_hook, sizeof(struct sigaction));
	sig_hook->sa_handler = handler;
	sigaction(sig, sig_hook, NULL);
}

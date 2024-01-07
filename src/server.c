/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/08 20:12:22 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/01/06 22:18:54 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

/******************************************************************************/
/*
* @file server.c
* @brief Server's source file.
*/
/******************************************************************************/

#include "minitalk.h"

/******************************************************************************/
/*
* @brief Converts bits to characters and print the string once all characters\
	are received.
*
* @param bit Bit received.
* @param sender_pid Client that send the signal.
*/
/******************************************************************************/
static void	print_characters(int bit, pid_t sender_pid)
{
	static t_advlist		advlst;
	static unsigned char	c;
	static int				received_bits;
	static pid_t			current_sender_pid;
	char					*str;

	if (sender_pid != current_sender_pid)
	{
		clearstatic(&advlst, &c, &received_bits);
		current_sender_pid = sender_pid;
	}
	c = c * 2 + bit;
	if (++received_bits == 8)
	{
		received_bits = 0;
		add_to_list(&advlst, c);
		if (c == '\0')
		{
			str = build_str(&advlst);
			ft_printf("%s\n", str);
			free(str);
			clearstatic(&advlst, &c, &received_bits);
		}
	}
	kill(current_sender_pid, SIGUSR1);
}

/******************************************************************************/
/*
* @brief SIGUSR1 signal handler. Bit 0.
*
* @param signum SIGUSR1.
* @param info To capture client's PID.
* @param context Void.
*/
/******************************************************************************/
static void	handle_sigusr1(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	print_characters(0, info->si_pid);
}

/******************************************************************************/
/*
* @brief SIGURS2 signal handler. Bit 1. 
*
* @param signum SIGUSR1. Bit 1.
* @param info To capture client's PID.
* @param context Void.
*/
/******************************************************************************/
static void	handle_sigusr2(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	print_characters(1, info->si_pid);
}

int	main(void)
{
	struct sigaction	handler1;
	struct sigaction	handler2;

	ft_bzero(&handler1, sizeof(struct sigaction));
	sigaddset(&handler1.sa_mask, SIGUSR1);
	sigaddset(&handler1.sa_mask, SIGUSR2);
	handler1.sa_flags = SA_SIGINFO;
	handler1.sa_sigaction = &handle_sigusr1;
	sigaction(SIGUSR1, &handler1, NULL);
	ft_bzero(&handler2, sizeof(struct sigaction));
	sigaddset(&handler2.sa_mask, SIGUSR1);
	sigaddset(&handler2.sa_mask, SIGUSR2);
	handler2.sa_flags = SA_SIGINFO;
	handler2.sa_sigaction = &handle_sigusr2;
	sigaction(SIGUSR2, &handler2, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
	}
}

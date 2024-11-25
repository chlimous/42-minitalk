/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/08 20:12:22 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/11/25 02:36:33 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "minitalk.h"

/******************************************************************************/
/*
* @brief Converts bits to characters and print the string once all characters \
	are received
*
* @param bit Bit received
* @param sender_pid Client that sends the signal
*/
/******************************************************************************/
static void	print_characters(int bit, pid_t sender_pid)
{
	static t_buffer	buffer;
	char			*str;

	if (sender_pid != buffer.sender_pid)
	{
		clear_buffer(&buffer);
		buffer.sender_pid = sender_pid;
	}
	buffer.current_char.c = (buffer.current_char.c << 1) | bit;
	++buffer.current_char.received_bits;
	if (buffer.current_char.received_bits == 8)
	{
		buffer.current_char.received_bits = 0;
		add_node(&buffer, buffer.current_char.c);
		if (buffer.current_char.c == '\0')
		{
			str = buffer_to_string(&buffer);
			ft_printf("%s\n", str);
			free(str);
		}
	}
	kill(buffer.sender_pid, SIGUSR1);
}

/******************************************************************************/
/*
* @brief SIGUSR1 signal handler (bit 0)
*
* @param signum SIGUSR1
* @param info Contains PID of client
* @param context Void
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
* @brief SIGURS2 signal handler (bit 1)
*
* @param signum SIGUSR2
* @param info Contains PID of client
* @param context Void
*/
/******************************************************************************/
static void	handle_sigusr2(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	print_characters(1, info->si_pid);
}

/******************************************************************************
 * @brief Initializes sigaction structure
 * 
******************************************************************************/
static void	init_signal_server(struct sigaction *sig_hook, int sig, \
		void (*handler)(int, siginfo_t *, void *))
{
	ft_bzero(sig_hook, sizeof(struct sigaction));
	sigaddset(&sig_hook->sa_mask, SIGUSR1);
	sigaddset(&sig_hook->sa_mask, SIGUSR2);
	sig_hook->sa_flags = SA_SIGINFO;
	sig_hook->sa_sigaction = handler;
	sigaction(sig, sig_hook, NULL);
}

int	main(void)
{
	struct sigaction	sig_hook1;
	struct sigaction	sig_hook2;

	init_signal_server(&sig_hook1, SIGUSR1, &handle_sigusr1);
	init_signal_server(&sig_hook2, SIGUSR2, &handle_sigusr2);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
	}
}

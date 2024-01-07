/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/08 23:49:03 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/01/06 22:45:28 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

/******************************************************************************/
/*
* @file client.c
* @brief Client's source file.
*/
/******************************************************************************/

#include "minitalk.h"

bool	g_signal_received; ///< Acknowledgment of receipt

/******************************************************************************/
/*
* @brief Sends a bit to the server and waits for response.
*
* @param bit Bit to send.
* @param pid Server PID.
*/
/******************************************************************************/
static void	send_bit(int bit, pid_t pid)
{
	g_signal_received = 0;
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			exit(EXIT_FAILURE);
	}
	else
		if (kill(pid, SIGUSR1) == -1)
			exit(EXIT_FAILURE);
	while (!g_signal_received)
	{
	}
}

/******************************************************************************/
/*
* @brief Sends a chararacter to the server, one bit at a time, MSB to LSB.
*
* @param c Character to send.
* @param sent_bits Stop condition (recursion).
* @param pid Server PID.
*/
/******************************************************************************/
static void	send_char(int c, int sent_bits, pid_t pid)
{
	sent_bits++;
	if (sent_bits < 8)
		send_char(c / 2, sent_bits, pid);
	if (c % 2 == 1)
		send_bit(1, pid);
	else
		send_bit(0, pid);
}

/******************************************************************************/
/*
* @brief SIGUSR1 signal handler. Handling receipt acknowledgment.
*
* @param signum SIGUSR1.
*/
/******************************************************************************/
static void	receipt_acknowledgment(int signum)
{
	(void)signum;
	g_signal_received = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	handler1;

	ft_bzero(&handler1, sizeof(struct sigaction));
	handler1.sa_handler = &receipt_acknowledgment;
	sigaction(SIGUSR1, &handler1, NULL);
	if (!(argc == 3 && ft_atoi(argv[1]) > 0))
		return (EXIT_FAILURE);
	while (*argv[2])
	{
		send_char((unsigned char)*argv[2], 0, ft_atoi(argv[1]));
		argv[2]++;
	}
	send_char((unsigned char)0, 0, ft_atoi(argv[1]));
	ft_printf("Successful.\n");
	return (EXIT_SUCCESS);
}

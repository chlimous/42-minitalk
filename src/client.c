/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/08 23:49:03 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/04/29 03:34:02 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_signal_received; ///< Acknowledgment of receipt

/******************************************************************************/
/*
* @brief SIGUSR1 signal handle, handling receipt acknowledgment
*
* @param signum SIGUSR1
*/
/******************************************************************************/
static void	receipt_acknowledgment(int signum)
{
	(void)signum;
	g_signal_received = 1;
}

/******************************************************************************/
/*
* @brief Sends a bit to the server and waits for response
*
* @param bit Bit to send
* @param pid Server PID
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
* @brief Sends chararacter to the server, one bit at a time, MSB to LSB
*
* @param c Character to send
* @param sent_bits Stop condition (recursion)
* @param pid Server PID
*/
/******************************************************************************/
static void	send_char(int c, int sent_bits, pid_t pid)
{
	++sent_bits;
	if (sent_bits < 8)
		send_char(c >> 1, sent_bits, pid);
	if ((c & 1) == 1)
		send_bit(1, pid);
	else
		send_bit(0, pid);
}

/******************************************************************************
 * @brief Sends string to the server, one character at a time
 * 
 * @param str String
 * @param pid Server PID
******************************************************************************/
static void	send_string(char *str, int pid)
{
	while (*str)
	{
		send_char(*str, 0, pid);
		++str;
	}
	send_char(0, 0, pid);
	ft_printf("Successful.\n");
}

int	main(int argc, char **argv)
{
	struct sigaction	sig_hook;

	if (argc != 3 || ft_atoi(argv[1]) < 0)
		return (EXIT_FAILURE);
	init_signal_client(&sig_hook, SIGUSR1, &receipt_acknowledgment);
	send_string(argv[2], ft_atoi(argv[1]));
	return (EXIT_SUCCESS);
}

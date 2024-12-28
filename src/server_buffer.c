/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   server_buffer.c                                    :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/04/29 00:08:58 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/11/25 02:36:57 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "minitalk.h"

/******************************************************************************
 * @brief Creates a new node
 * 
 * @param c Node content (character)
 * @return t_node* New node
******************************************************************************/
static t_node	*new_node(char c)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

/******************************************************************************
 * @brief Adds node to the end of buffer
 * 
 * @param buffer Buffer pointer
 * @param new New node
******************************************************************************/
static void	add_back(t_buffer *buffer, t_node *new)
{
	if (buffer->size)
	{
		buffer->tail->next = new;
		buffer->tail = new;
		++buffer->size;
	}
	else
	{
		buffer->head = new;
		buffer->tail = new;
		++buffer->size;
	}
}

/******************************************************************************
 * @brief Converts buffer to string
 * 
 * @param buffer Buffer pointer
 * @return char* String
******************************************************************************/
char	*buffer_to_string(t_buffer *buffer)
{
	char	*str;
	t_node	*current;
	size_t	i;

	str = malloc(sizeof(char) * buffer->size + 1);
	if (!str)
	{
		clear_buffer(buffer);
		exit(EXIT_FAILURE);
	}
	i = 0;
	current = buffer->head;
	while (current)
	{
		str[i] = current->c;
		++i;
		current = current->next;
	}
	str[i] = '\0';
	clear_buffer(buffer);
	return (str);
}

/******************************************************************************
 * @brief Clears buffer
 * 
 * @param buffer Buffer pointer
******************************************************************************/
void	clear_buffer(t_buffer *buffer)
{
	t_node	*next;

	buffer->current_char.c = 0;
	buffer->current_char.received_bits = 0;
	while (buffer->head)
	{
		next = buffer->head->next;
		free(buffer->head);
		buffer->head = next;
	}
	buffer->tail = NULL;
	buffer->size = 0;
}

/******************************************************************************
 * @brief Adds node to buffer
 * 
 * @param buffer Buffer pointer
 * @param c Node content (character)
******************************************************************************/
void	add_node(t_buffer *buffer, char c)
{
	t_node	*new;

	new = new_node(c);
	if (!new)
	{
		clear_buffer(buffer);
		exit(EXIT_FAILURE);
	}
	add_back(buffer, new);
}

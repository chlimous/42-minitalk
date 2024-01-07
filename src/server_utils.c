/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/16 15:15:59 by chlimous	       #+#    #+#	      */
/*   Updated: 2024/01/06 22:15:09 by chlimous         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

/******************************************************************************/
/*
* @file server_utils.c
* @brief Additional server functions.
*/
/******************************************************************************/

#include "minitalk.h"

/******************************************************************************/
/*
* @brief Resets all static variables.
*
* @param advlst Advanced list containing characters.
* @param c Character.
* @param received_bits Received bits.
*/
/******************************************************************************/
void	clearstatic(t_advlist *advlst, unsigned char *c, int *received_bits)
{
	*c = 0;
	*received_bits = 0;
	ft_advlstclear(advlst);
}

/******************************************************************************/
/*
* @brief Converts the list to a string.
*
* @param advlst Advanced list containing characters.
*
* @return String built.
*/
/******************************************************************************/
char	*build_str(t_advlist *advlst)
{
	char	*str;
	t_list	*current;
	size_t	i;

	str = malloc(sizeof(char) * advlst->size);
	if (!str)
	{
		ft_advlstclear(advlst);
		exit(EXIT_FAILURE);
	}
	i = 0;
	current = advlst->head;
	while (current)
	{
		str[i] = ((char *)(current->content))[0];
		i++;
		current = current->next;
	}
	return (str);
}

/******************************************************************************/
/*
* @brief Adds a character to the list.
*
* @param advlst Advanced list to add the character to.
* @param c Character to add.
*/
/******************************************************************************/
void	add_to_list(t_advlist *advlst, char c)
{
	void	*content;

	content = malloc(sizeof(char) * 1);
	((char *)content)[0] = c;
	if (ft_advlstadd_back(advlst, ft_lstnew(content)))
	{
		ft_advlstclear(advlst);
		exit(EXIT_FAILURE);
	}
}

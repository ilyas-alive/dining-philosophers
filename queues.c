/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queues.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 10:45:51 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/07/13 10:45:56 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

t_node	*ft_new_node(int content)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

int ft_pop_node(t_node **queue)
{
    t_node *popped_node;
	int content;

    popped_node = *queue;
    *queue = popped_node->next;
	content = popped_node->content;	

    return (content);
}

void	ft_add_back(t_node **queue, t_node *new)
{
	t_node	*i;

	if (!*queue)
	{
		*queue = new;
		return ;
	}
	i = *queue;
	while (i->next)
		i = i->next;
	i->next = new;
}

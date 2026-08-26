/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queues.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 10:45:51 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:35:49 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

t_node	*ft_new_node(t_coder *coder)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->coder = coder;
	node->priority = 0;
	node->next = NULL;
	return (node);
}

t_coder	*ft_pop_node(t_node **queue)
{
	t_node	*first;
	t_coder	*coder;

	if (!queue || !*queue)
		return (NULL);
	first = *queue;
	coder = first->coder;
	*queue = first->next;
	free(first);
	return (coder);
}

void	ft_add_back(t_node **queue, t_node *new)
{
	t_node	*curr;

	if (!queue || !new)
		return ;
	if (!*queue)
	{
		*queue = new;
		return ;
	}
	curr = *queue;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

void	ft_add_sorted(t_node **queue, t_node *new)
{
	t_node	*curr;

	if (!queue || !new)
		return ;
	if (!*queue || new->priority < (*queue)->priority
		|| (new->priority == (*queue)->priority
			&& new->coder->id < (*queue)->coder->id))
	{
		new->next = *queue;
		*queue = new;
		return ;
	}
	curr = *queue;
	while (curr->next && (curr->next->priority < new->priority
			|| (curr->next->priority == new->priority
				&& curr->next->coder->id < new->coder->id)))
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

void	ft_remove_node(t_node **queue, t_coder *coder)
{
	t_node	*curr;
	t_node	*target;

	if (!queue || !*queue)
		return ;
	if ((*queue)->coder == coder)
	{
		target = *queue;
		*queue = target->next;
		free(target);
		return ;
	}
	curr = *queue;
	while (curr->next && curr->next->coder != coder)
		curr = curr->next;
	if (curr->next)
	{
		target = curr->next;
		curr->next = target->next;
		free(target);
	}
}


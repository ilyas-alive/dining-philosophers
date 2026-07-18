/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:32:32 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/04/10 12:32:43 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef CODEXION_H
# define CODEXION_H

typedef	struct	config
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			number_of_compiles_required;
	long			dongle_cooldown;
	int				is_edf;
	t_dongle	 	*dongles;
	t_coder			*coders;
	t_thread 		*threads;
	int				coders_finished;
	int				is_over;
	pthread_mutex_t finished_lock;
	pthread_mutex_t over_lock;

}	tcodex;

typedef	struct	dongle
{
	long			cooldown_time;
	pthread_mutex_t	mutex;
	t_node			*queue;
	pthread_cond_t	cond;
}	t_dongle;

typedef	struct	coder
{
	t_codex		config;
	t_dongle	*rdongle;
	t_dongle	*ldongle;
	int			id;
	int			count;
	pthread_t	thread;
}	t_coder;


//queue
typedef	struct	s_node
{
	t_coder			*coder;
	struct s_node	*next;
}				t_node;

t_node	*ft_new_node(int content);
int		ft_pop_node(t_node **queue);
void	ft_add_back(t_node **queue, t_node *new);




int	digit_check(char **str);
int	check_input(int argc, char **ar);
int	fifo_or_edf(char **ar);
int	last_check(t_codex *config);

void make_config(t_codex *config, char **ar);


#endif

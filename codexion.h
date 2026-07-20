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
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef CODEXION_H
# define CODEXION_H


typedef struct s_dongle t_dongle;
typedef	struct	s_coder t_coder;
typedef	struct	s_node t_node;
typedef	struct	s_config t_codex;

struct	s_config
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
	pthread_t 		*threads;
	int				coders_finished;
	int				is_over;
	pthread_mutex_t finished_lock;
	pthread_mutex_t over_lock;

};

struct	s_dongle
{
	long			cooldown_time;
	pthread_mutex_t	mutex;
	t_node			*queue;
	pthread_cond_t	cond;
};

struct	s_coder
{
	t_codex		*config;
	t_dongle	*rdongle;
	t_dongle	*ldongle;
	int			id;
	int			count;
	pthread_t	thread;
};


//queue
struct	s_node
{
	t_coder			*coder;
	struct s_node	*next;
};

t_node	*ft_new_node(t_coder *coder);
t_coder	*ft_pop_node(t_node **queue);
void	ft_add_back(t_node **queue, t_node *new);
//

//parsing
int	digit_check(char **str);
int	check_input(int argc, char **ar);
int	fifo_or_edf(char **ar);
int	last_check(t_codex *config);
void make_config(t_codex *config, char **ar);
//


//init
void dongle_init(t_dongle *dongle, long cooldown_time);
void init_dongles(t_codex *config);
void init_config(t_codex *config);

void init_coders(t_codex *config);
void coder_init(t_coder *coder, t_codex *config, int position);
//



#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:32:32 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:34:29 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CODEXION_H
# define CODEXION_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

typedef struct s_dongle	t_dongle;
typedef struct s_coder	t_coder;
typedef struct s_node	t_node;
typedef struct s_config	t_config;

struct	s_config
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			compiles_needed;
	long			dongle_cooldown;
	int				is_edf;
	long			start_time;
	int				coders_finished;
	int				is_over;
	pthread_mutex_t	over_lock;
	pthread_mutex_t	print_lock;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_t		monitor;
};

struct	s_dongle
{
	int				available;
	long			cooldown_time;
	long			cooldown_end;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_node			*queue;
};

struct	s_coder
{
	int				id;
	int				count;
	long			time_compiled;
	pthread_mutex_t	time_mutex;
	pthread_t		thread;
	t_dongle		*rdongle;
	t_dongle		*ldongle;
	t_config		*config;
};

struct	s_node
{
	t_coder			*coder;
	long			priority;
	struct s_node	*next;
};

//parsing
int		digit_check(char **str);
int		fifo_or_edf(char **ar);
int		check_input(int argc, char **ar);
int		last_check(t_config *config);
void	make_config(t_config *config, char **ar);

//init
void	dongle_init(t_dongle *dongle, long cooldown_time);
void	init_dongles(t_config *config);
void	coder_init(t_coder *coder, t_config *config, int position);
void	init_coders(t_config *config);
void	init_config(t_config *config);

//queue
t_node	*ft_new_node(t_coder *coder);
t_coder	*ft_pop_node(t_node **queue);
void	ft_add_back(t_node **queue, t_node *new);
void	ft_add_sorted(t_node **queue, t_node *new);
void	ft_remove_node(t_node **queue, t_coder *coder);

//time
long	get_time(void);
void	ft_sleep(long ms, t_config *config);
void	ms_to_timespec(t_dongle *dongle, struct timespec *ts);

//routine
int		take_dongle(t_coder *coder, t_dongle *dongle);
int		get_dongles(t_coder *coder);
int		compiling(t_coder *coder);
void	*coder_routine(void *data);
void	*monitor_routine(void *data);

//utils
int		end_simulation(t_config *config);
int		safe_count(t_coder *coder);
void	ft_log(char *message, t_coder *coder);
void	release_dongle(t_dongle *dongle, t_config *config);
void	release_dongles(t_coder *coder);
void	wake_dongles(t_config *config);

//threads
int		start_threads(t_config *config);
void	wait_threads(t_config *config);

//cleanup
void	free_config(t_config *config);

#endif


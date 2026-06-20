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
#ifndef CODEXION_H
# define CODEXION_H

typedef struct config
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_codex;

/*
typedef struct coder_conf
{
	t_dongle fi_dongle;
	t_dongle se_dongle;
}
*/

int	digit_check(char **str);
int	check_input(int argc, char **ar);
int	fifo_or_edf(char **ar);
int	last_check(t_codex *config);

void make_config(t_codex *config, char **ar);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:55:41 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/04/11 11:56:19 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "codexion.h"

int	digit_check(char **str)
{
	int	par;
	int	i;

	par = 1;
	while (par < 8)
	{
		i = 0;
		while (str[par][i] == ' ')
			i++;
		if (str[par][i] == '+')
			i++;
		if (!(str[par][i] >= '0' && str[par][i] <= '9'))
			return (0);
		while (str[par][i] >= '0' && str[par][i] <= '9')
			i++;
		while (str[par][i] == ' ')
			i++;
		if (str[par][i] != '\0')
			return (0);
		par++;
	}
	return (1);
}

int	fifo_or_edf(char **ar)
{
	return (strcmp(ar[8], "fifo") == 0 || strcmp(ar[8], "edf") == 0);
}

int	check_input(int argc, char **ar)
{
	int	result;
	int	number;
	int	scheduler;

	result = 0;
	if (argc != 9)
		return (0);
	number = digit_check(ar);
	scheduler = fifo_or_edf(ar);
	result += number + scheduler;
	return (result == 2);
}


int	last_check(t_codex *config)
{
	if (config->number_of_coders <= 0)
		return (0);
	if (config->time_to_burnout <= 0)
		return (0);
	if (config->time_to_compile <= 0)
		return (0);
	if (config->time_to_debug <= 0)
		return (0);
	if (config->time_to_refactor <= 0)
		return (0);
	if (config->number_of_compiles_required <= 0)
		return (0);
	if (config->dongle_cooldown < 0)
		return (0);
	return (1);
}

void	make_config(t_codex *config, char **ar)
{
	config->number_of_coders = atoi(ar[1]);
	config->time_to_burnout = atoi(ar[2]);
	config->time_to_compile = atoi(ar[3]);
	config->time_to_debug = atoi(ar[4]);
	config->time_to_refactor = atoi(ar[5]);
	config->number_of_compiles_required = atoi(ar[6]);
	config->dongle_cooldown = atoi(ar[7]);
	if (ar[8][0] == 'f')
		config->is_edf = 0;
	else
		config->is_edf = 1;
}

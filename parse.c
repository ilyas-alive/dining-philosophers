/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghan <iel-ghan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:55:41 by iel-ghan          #+#    #+#             */
/*   Updated: 2026/08/26 17:51:53 by iel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	digit_check(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (i < 8)
	{
		j = 0;
		while (str[i][j] == ' '
			|| (str[i][j] >= 9 && str[i][j] <= 13))
			j++;
		if (str[i][j] == '+')
			j++;
		if (str[i][j] < '0' || str[i][j] > '9')
			return (0);
		while (str[i][j] >= '0' && str[i][j] <= '9')
			j++;
		while (str[i][j] == ' '
			|| (str[i][j] >= 9 && str[i][j] <= 13))
			j++;
		if (str[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	fifo_or_edf(char **ar)
{
	if (strcmp(ar[8], "fifo") == 0)
		return (1);
	if (strcmp(ar[8], "edf") == 0)
		return (1);
	return (0);
}

int	check_input(int argc, char **ar)
{
	if (argc != 9)
		return (0);
	if (!digit_check(ar))
		return (0);
	if (!fifo_or_edf(ar))
		return (0);
	return (1);
}

int	last_check(t_config *config)
{
	if (config->number_of_coders <= 0
		|| config->time_to_burnout <= 0
		|| config->time_to_compile <= 0
		|| config->time_to_debug <= 0
		|| config->time_to_refactor <= 0
		|| config->compiles_needed <= 0
		|| config->dongle_cooldown < 0)
		return (0);
	return (1);
}

void	make_config(t_config *config, char **ar)
{
	config->number_of_coders = (int)atoi(ar[1]);
	config->time_to_burnout = (long)atoi(ar[2]);
	config->time_to_compile = (long)atoi(ar[3]);
	config->time_to_debug = (long)atoi(ar[4]);
	config->time_to_refactor = (long)atoi(ar[5]);
	config->compiles_needed = (long)atoi(ar[6]);
	config->dongle_cooldown = (long)atoi(ar[7]);
	config->is_edf = (strcmp(ar[8], "edf") == 0);
}

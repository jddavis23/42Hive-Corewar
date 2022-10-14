/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:11:44 by molesen           #+#    #+#             */
/*   Updated: 2022/10/14 12:11:46 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	set_flag_minus(t_info *info)
{
	int	i;

	i = 0;
	while (i < FLAG_COUNT)
	{
		info->flag[i] = -1;
		++i;
	}
}

static int	set_flag_true(t_info *info, int type)
{
	info->flag[type] = TRUE;
	return (TRUE);
}

static int	check_int_flag(char *str, t_info *info)
{
	if (!ft_strcmp(str, "-dump"))
		return (set_flag_true(info, D_FLAG));
	else if (!ft_strcmp(str, "-dc"))
		return (set_flag_true(info, DC_FLAG));
	else if (!ft_strcmp(str, "-di"))
		return (set_flag_true(info, DI_FLAG));
	else if (!ft_strcmp(str, "-c"))
		return (set_flag_true(info, C_FLAG));
	else if (!ft_strcmp(str, "-s"))//if we don't create this we need to delete
		return (set_flag_true(info, S_FLAG));
	else if (!ft_strcmp(str, "-v"))
		return (set_flag_true(info, V_FLAG));
	return (FALSE);
}

int	init_flags(int argc, char **argv, t_info *info)
{
	int	i;

	set_flag_minus(info);
	if (!ft_strcmp(argv[1], "-a"))
		return (set_flag_true(info, A_FLAG));
	else if (!ft_strcmp(argv[1], "-i"))
		return (set_flag_true(info, I_FLAG));
	else if (check_int_flag(argv[1], info))
	{
		if (argc > 3 && str_digit(argv[2]))
		{
			i = 0;
			while (i < FLAG_COUNT)
			{
				if (info->flag[i] == 1)
					info->flag[i] = ft_atoi(argv[2]);
				++i;
			}
			return (2);//figure out how strict to be with this flag
		}
		else
			return (ERROR);
	}
	info->flag[NO_FLAG] = TRUE;
	return (0);
}

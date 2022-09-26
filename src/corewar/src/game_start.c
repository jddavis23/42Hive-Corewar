/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:40:48 by molesen           #+#    #+#             */
/*   Updated: 2022/09/23 12:33:18 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	one_carriage_left(t_info *info)
{
	t_carriage	*carriage;
	int			count;

	carriage = info->head_carriage;
	count = 0;
	while (carriage)
	{
		++count;
		carriage = carriage->next;
	}
	if (count == 1)
		return (TRUE);
	return (FALSE);
}

static void	kill_carriages(t_info *info)
{
	//FUNCTION
	//function that checks all of the carriages and when their last live_call was and if it is within the limit
	if (info->live_statement >= NBR_LIVE)
	{
		info->cycle_of_death = info->cycle_of_death - CYCLE_DELTA;
		info->checks_count = 1;//unsure about corellation of max_checks and checks_count....
	}
	else
	{
		//unsure if this is how it is supposed to be
		info->checks_count += 1;//unsure about corellation of max_checks and checks_count....
		if (info->checks_count >= MAX_CHECKS)
			info->cycle_of_death = info->cycle_of_death - CYCLE_DELTA;
	}
	info->death_count = info->cycle_of_death;
}

static void	check(t_info *info)
{
	info->death_count -= 1;
	if (info->death_count <= 0)
		kill_carriages(info);
	info->total_cycles += 1;
	info->live_statement = 0;
}

static void	introduce_contestants(t_profile **champ)//add player struct
{
	ft_printf("Introducing contestants...\n");
	while (*champ)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", (*champ)->i, (*champ)->exec_cd_sz, (*champ)->name, (*champ)->comment);
		*champ = (*champ)->next;
	}
}

static int	declare_operations(t_op **op)
{
	*op = {
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
	};
}

int	game_start(uint32_t core[MEM_SIZE], t_info *info, t_profile **champ)//add player struct
{
	t_op	op[17];

	//declare operation tabs if malloc error return ERROR
	op = NULL;
	if (declare_operations(&op) == ERROR)
		return (ERROR);
	ft_printf("op %s\n", op[0][0]);
	introduce_contestants(champ);//add player struct
	while (!one_carriage_left(info))
	{
		if (update_carriages(info) == ERROR)
			return (ERROR);
		check(info);
	}
	while (*champ)
	{
		if (info->winner == (*champ)->i + 1)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", info->winner, (*champ)->name);
			break ;
		}
		(*champ)->next;
	}
	if (core)
		print_core(core);
	return (0);
}

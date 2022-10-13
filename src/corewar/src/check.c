#include "vm.h"

int	print_cycle_count(t_info *info)
{
	if (info->flag[V_FLAG] == 2 || info->flag[V_FLAG] == 3 || info->flag[V_FLAG] == 6)
		return (TRUE);
	if (info->flag[V_FLAG] == 7 || info->flag[V_FLAG] == 11 || info->flag[V_FLAG] == 14)
		return (TRUE);
	if (info->flag[V_FLAG] == 10 || (info->flag[V_FLAG] >= 18 && info->flag[V_FLAG] <= 19))
		return (TRUE);
	if (info->flag[V_FLAG] == 15 || (info->flag[V_FLAG] >= 22 && info->flag[V_FLAG] <= 23))
		return (TRUE);
	return (FALSE);
}

static void	delete_carriage(t_info *info, int id)
{
	t_carriage	*carriage;
	t_carriage	*prev;

	carriage = info->head_carriage;
	prev = NULL;
	while (carriage)
	{
		if (carriage->id == id)
		{
			if (!carriage->next && !prev)
				info->head_carriage = NULL;
			else if (!carriage->next)
				prev->next = NULL;
			else if (!prev)
				info->head_carriage = carriage->next;
			else
				prev->next = carriage->next;
			free(carriage);
			return ;
		}
		prev = carriage;
		carriage = carriage->next;
	}
}

static void	check_carriage_live_call(t_info *info)
{
	t_carriage	*carriage;
	t_carriage	*next;
	int			limit;
	
	carriage = info->head_carriage;
	if (info->cycles_to_die < 0)
		limit = info->total_cycles - 1;
	else
		limit = info->total_cycles - info->cycles_to_die - 1;
	//int found = FALSE;
	//ft_printf("limit %d == %d - %d\n", limit, info->total_cycles, info->cycles_to_die);
	while (carriage)
	{
		// if (info->cycles_to_die == 836 && carriage->id == 1968)
		// {
		// 	ft_printf("carriage id: %d\n", carriage->id);
		// 	ft_printf("limit %d == %d - %d	carriage : %d in regards to limit: %d\n", limit, info->total_cycles, info->cycles_to_die, carriage->last_live_call, info->total_cycles - carriage->last_live_call);
		// 	found = TRUE;
		// }
		// if (carriage->id == 1966)
		// {
		// 	ft_printf("carriage id: %d\n", carriage->id);
		// 	ft_printf("limit %d == %d - %d	carriage : %d in regards to limit: %d\n", limit, info->total_cycles, info->cycles_to_die, carriage->last_live_call, info->total_cycles - carriage->last_live_call);
		// }

		//if (carriage->id == 1)
		//ft_printf("limit %d == %d - %d	carriage : %d in regards to limit: %d\n", limit, info->total_cycles, info->cycles_to_die, carriage->last_live_call, info->total_cycles - carriage->last_live_call);
		if (carriage->last_live_call <= limit)
		{
			next = carriage->next;
			if ((info->flag[V_FLAG] >= 8 && info->flag[V_FLAG] <= 15) || info->flag[V_FLAG] == 24)
			{
				if (info->cycles_to_die < 0)
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", carriage->id, info->total_cycles - carriage->last_live_call - 1, info->cycles_to_die);
				else
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", carriage->id, info->total_cycles - carriage->last_live_call - 1, info->cycles_to_die);
			}
			// if (carriage->id == 1093)
			// 	found = TRUE;
			delete_carriage(info, carriage->id);
			carriage = next;
		}
		else
			carriage = carriage->next;
	}
}

static void	kill_carriages(t_info *info)
{
	check_carriage_live_call(info);
	if (info->live_statement >= NBR_LIVE)
	{
		info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
		info->checks_count = 0;//unsure about corellation of max_checks and checks_count....
		if (print_cycle_count(info) == TRUE)
			ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
	}
	else
	{
		//unsure if this is how it is supposed to be
		// info->checks_count += 1;//unsure about corellation of max_checks and checks_count....
		if (info->checks_count >= MAX_CHECKS)
		{
			info->cycles_to_die = info->cycles_to_die - CYCLE_DELTA;
			if (print_cycle_count(info) == TRUE)
			{
				ft_printf("Cycle to die is now %d\n", info->cycles_to_die);
			}
			info->checks_count = 0;
		}
	}
	info->checks_count += 1;
	info->cycle_count = info->cycles_to_die;
	//ft_printf("live statement: %d\n", info->live_statement);
	info->live_statement = 0;
}

void	check(t_info *info)
{
	info->cycle_count -= 1;
	info->total_cycles += 1;
	if (info->cycle_count <= 0)
		kill_carriages(info);
}

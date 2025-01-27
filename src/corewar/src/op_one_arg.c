/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_one_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:57:05 by molesen           #+#    #+#             */
/*   Updated: 2022/10/19 11:23:53 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
makes carriage able to jump to different positions on the
board with the limitations of IDX_MOD (-512 to 512)
*/
void	op_zjmp(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int			pos;
	static int	found = FALSE;

	if ((*carriage)->carry && core && info)
	{
		if ((int16_t)(*carriage)->args_found[ARG1] < 0)
			pos = (*carriage)->pos - (((int16_t)(*carriage)->args_found[ARG1] \
			* -1) % IDX_MOD);
		else
			pos = (*carriage)->pos + ((int16_t)(*carriage)->args_found[ARG1] \
			% IDX_MOD);
		limit_jump(&pos);
		(*carriage)->pos = pos;
	}
	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0)
		v_flag4_one_arg(carriage, "zjmp");
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
calls a player to be alive if the number read from the first argument is
equal to a player ex. if we read the first argument to be -2
then we will call player 2 to be alive
*/
void	op_live(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	static int	found = FALSE;

	if ((info->flag[V_FLAG] & 4) == 4 && info->flag[V_FLAG] > 0)
		v_flag4_one_arg(carriage, "live");
	(*carriage)->last_live_call = info->total_cycles;
	info->live_statement += 1;
	if ((*carriage)->args_found[ARG1] >= (info->champ_total * -1) && core \
		&& info && (*carriage)->args_found[ARG1] <= -1)
	{
		info->winner = (*carriage)->args_found[ARG1] * -1;
		if (info->flag[NO_FLAG] == TRUE)
			ft_printf("A process shows that player %d (%s) is alive\n", \
			info->winner, info->champ_names[info->winner - 1]);
		else if ((info->flag[V_FLAG] & 1) == 1 && info->flag[V_FLAG] > 0)
			ft_printf("Player %d (%s) is said to be alive\n", \
			info->winner, info->champ_names[info->winner - 1]);
	}
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

/*
prints the correlating number to standard output in the form of a char
this operand only shows if flag -a is active
*/
void	op_aff(uint8_t core[MEM_SIZE], t_carriage **carriage, t_info *info)
{
	int32_t		nbr;
	static int	found = FALSE;

	if (info->flag[A_FLAG] == TRUE && core && info)
	{
		nbr = (int32_t)(*carriage)->registry[(int32_t)(*carriage)->\
		args_found[ARG1] - 1];
		ft_printf("Aff: %c\n", (char)nbr % 256);
	}
	if (info->flag[O_FLAG] == TRUE && found == FALSE)
		found = v_flag5(carriage);
}

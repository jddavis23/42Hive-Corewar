/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_indirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:18:46 by cchen             #+#    #+#             */
/*   Updated: 2022/10/03 22:00:43 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse_indirect(t_statement *statement, t_lexer *lexer, t_symbols *sym,
		uint8_t index)
{
	statement->arguments[index].ind = (uint16_t) sym->num;
	if (sym->argtype & T_LAB)
		return (parse_reference(statement, lexer, sym, index));
	if (lexer_next(lexer, sym) == ERROR)
		return (ERROR);
	return (parse_numeric(statement, lexer, sym, index));
}

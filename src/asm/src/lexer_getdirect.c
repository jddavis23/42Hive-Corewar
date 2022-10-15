/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getdirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:50:14 by cchen             #+#    #+#             */
/*   Updated: 2022/09/27 09:50:15 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "lexer.h"

int	lexer_getdirect(t_source *source, t_symbols *sym)
{
	char	*next;

	sym->argtype |= T_DIR;
	next = source_next(source);
	if (next && *next == LABEL_CHAR)
		return (lexer_getreference(source, sym));
	if (next && (ft_isdigit(*next) || is_operator(*next)))
		return (lexer_getnumber(source, sym));
	return (lexer_getcomment(source, sym));
}
